#include "../CourseLib/core/location.hh"
#include "../CourseLib/errors/initerror.hh"
#include "../CourseLib/errors/gameerror.hh"
#include "../CourseLib/actors/nysse.hh"
#include "../CourseLib/actors/passenger.hh"
#include <QTime>
#include <QDebug>
#include <QTimer>
#include <iostream>
#include "city.hh"
#include "gamewindow.hh"

City::City(std::shared_ptr<GameWindow> window) :
    state_(INIT_STATE),
    mainWindow_(window)
{

}

City::~City()
{

}

void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    try
    {
        mainWindow_->setPicture(basicbackground);
    }
    catch(...)
    {
        throw Interface::InitError("Setting the picture failed or invalid picture");
    }
}

void City::setClock(QTime clock)
{
    std::shared_ptr<QTime> clockPointer = std::make_shared<QTime>(clock);
    clock_ = clockPointer;
}

void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    //addStop-funktion pitäisi heittää InitError, jos stopin paikka ei ole validi? Miten tämä
    //määritellään? Koska logic-luokassa ei ole minkäänlaista poikkeuskäsittelyä, poikkeus vuotaa
    //enginelle. Engine ei kuitenkaan oikein kykene ilmoittamaan, logiikalle, että ohita poikkeuksen
    //aiheuttanut stoppi ja lisää kaikki muut kartalle, joten peli ei tämän jälkeen käytännössä toimi.
    //Stoppien tiedot ovat peräisin tiedostosta, joten niiden paikat ovat aina samat. Näin ollen
    //addStop ei käytännössä saa heittää poikkeusta, jos pelin halutaan toimivan. Tällöin ei oikeastaan
    //jää muuta vaihtoehtoa kuin heittää hatusta jotkin raja-arvot, jotka eivät koskaan aiheuta poikkeusta,
    //koska rajapinnan dokumentaatio poikkeusta vaatii.

    Interface::Location location = stop->getLocation();
    int x = location.giveX();
    int y = COORD_SCALING-location.giveY();
    int width = mainWindow_->getWidth();
    int height = mainWindow_->getHeight();
    int minWidth = 0;
    int minHeight = 0;
    int maxLoc = 50000;
    int minLoc = -50000;

    if (x > maxLoc || x < minLoc || y > maxLoc || y < minLoc)
    {
        throw Interface::InitError("Invalid stop position");
    }
    //Vähennetään käsiteltävien stoppien määrää
    else if ((x >= minWidth && x <= width) && (y >= minHeight && y <= height))
    {
        stops_.push_back(stop);
        int passengers = stop->getPassengers().size();
        mainWindow_->addStop(x, y, stop, passengers);
    }
}

void City::startGame()
{
    state_ = GAME_STATE;
}

void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    if (findActor(newactor))
    {
        throw Interface::GameError("Actor already in the city");
    }
    else
    {
        if (dynamic_cast<CourseSide::Passenger*>(newactor.get()) == 0)
        {
            CourseSide::Nysse* bus = dynamic_cast<CourseSide::Nysse*>(newactor.get());
            std::vector<std::shared_ptr<Interface::IPassenger>> passengers = bus->getPassengers();
            int count = passengers.size();

            Interface::Location location = newactor->giveLocation();
            int x = location.giveX();
            int y = COORD_SCALING-location.giveY();
            mainWindow_->addNysse(x,y, newactor, count);
        }
        else
        {
            mainWindow_->updateStops();
        }
        actors_.push_back(newactor);
    }
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    if (!findActor(actor))
    {
        throw Interface::GameError("Actor not found in the city");
    }
    else
    {
        for (unsigned int i = 0; i < actors_.size(); i++)
        {
            if (actors_.at(i) == actor)
            {
                actors_.erase(actors_.begin() + i);
                break;
            }
        }
    }
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    // Miten tämäm pitäisi erota funktiosta removeActor?
    removeActor(actor);
}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    for (unsigned int i = 0; i < actors_.size(); i++)
    {
        if (actors_.at(i) == actor)
        {
            return true;
        }
    }
    return false;
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    int x = actor->giveLocation().giveX();
    int y = actor->giveLocation().giveY();
    if (dynamic_cast<CourseSide::Passenger*>(actor.get()) == 0)
    {
        CourseSide::Nysse* bus = dynamic_cast<CourseSide::Nysse*>(actor.get());
        std::vector<std::shared_ptr<Interface::IPassenger>> passengers = bus->getPassengers();
        int count = passengers.size();

        mainWindow_->moveNysse(x, COORD_SCALING-y, actor, count);
    }
    else
    {
        mainWindow_->updateStops();
    }
}

std::vector<std::shared_ptr<Interface::IActor>> City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor>> actors;
    try
    {
        for (unsigned int i = 0; i < actors_.size(); i++)
        {
            if (actors_.at(i)->giveLocation().isClose(loc))
            {
                actors.push_back(actors_.at(i));
            }
        }
    }
    catch(...)
    {
        actors.clear();
    }

    return actors;
}

bool City::isGameOver() const
{
    if (state_ == END_STATE)
    {
        return true;
    }
    return false;
}

void City::endGame()
{
    state_ = END_STATE;
}
