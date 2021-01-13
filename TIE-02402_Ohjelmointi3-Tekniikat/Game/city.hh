#ifndef CITY_HH
#define CITY_HH

#include <QTime>
#include <../CourseLib/interfaces/icity.hh>
#include <../CourseLib/interfaces/iactor.hh>
#include <../CourseLib/interfaces/istop.hh>
#include "gamewindow.hh"

class City : public Interface::ICity
{
public:
    /**
     * @brief City constructor.
     * @param window Game window.
     */
    City(std::shared_ptr<GameWindow> window);

    /**
     * @brief ~City destructor.
     */
    virtual ~City();

    // ICity-rajapinta
    /**
     * @brief setBackground sets the bitmap picture of the game area.
     * @param basicbackground  Normal sized picture used as the game area. Bottom left position of the picture in pixelcoordinates can be found out using the offset()-method.
     * @param bigbackground  Background of the game that is bigger than normal. Used only if doing Scrolling map-expansion. Bottom left position of the picture in pixelcoordinates can be found out using the offset()-method.
     * @pre City is in init state.
     * @post Picture for the game area is set. Exception guarantee: basic.
     * @exception InitError Setting the picture was unsuccesful or the picture was invalid.
     */
    virtual void setBackground(QImage& basicbackground, QImage& bigbackground) override;

    /**
     * @brief setClock sets the time of the game clock.
     * @param clock Game clock time at the function call.
     * @pre `kello.isValid() == true`.
     * @post Time is set. Exception guarantee: nothrow.
     */
    virtual void setClock(QTime clock) override;

    /**
     * @brief addStop adds a stop to the city.
     * @param stop pointer to a stop object.
     * @pre City is in init state.
     * @post Stop is added to the city. Exception guarantee: basic
     * @exception InitError Stops position is not valid.
     */
    virtual void addStop(std::shared_ptr<Interface::IStop> stop) override;

    /**
     * @brief startGame shofts city from init state to the gamestate.
     * @pre City is in init state. setBackground() and setClock() have been called.
     * @post City is in gamestate. Exception guarantee: nothrow.
     */
    virtual void startGame() override;

    /**
     * @brief addActor adds a new actor to the city.
     * @param newactor actor to be added to the city that fulfills ActorIF.
     * @pre -
     * @post Actor is added to the city. Exception guarantee: basic.
     * @exception GameError Actor is already in the city.
     */
    virtual void addActor(std::shared_ptr<Interface::IActor> newactor) override;

    /**
     * @brief removeActor removes the actor from the city.
     * @param actor Actor to be removed.
     * @pre City is in gamestate.
     * @post Actor is removed from the city. Exception guarantee: strong.
     * @exception GameError Actor not found in the city
     */
    virtual void removeActor(std::shared_ptr<Interface::IActor> actor) override;

    /**
     * @brief actorRemoved tells the city that actor is removed ingame.
     * @param actor Actor that is set removed ingame.
     * @pre City is in gamestate. Given actor is found in the city. Actor has `actor.isRemoved() == true`.
     * @post Exception guarantee: strong.
     */
    virtual void actorRemoved(std::shared_ptr<Interface::IActor> actor) override;

    /**
     * @brief findActor checks if the given actor is in the city.
     * @param actor Actor that that is looked for in the city.
     * @pre -
     * @return Boolean that tells wether the actor is in the city.
     * @post Exception guarantee: nothrow.
     */
    virtual bool findActor(std::shared_ptr<Interface::IActor> actor) const override;

    /**
     * @brief actorMoved is an operation that is used to tell wether certain actor has moved.
     * @param actor Actor that has moved.
     * @pre City is in gamestate. Given actor is found in the city.
     * @post Exception guarantee: basic.
     */
    virtual void actorMoved(std::shared_ptr<Interface::IActor> actor) override;

    /**
     * @brief getNearbyActors returns actors that are close to given position.
     * @param loc Location for getting the actors close to it.
     * @pre City is in gamestate.
     * @return Vector containing actors close to the location, that pass `getLocation().isClose(loc) == true`.
     * @post Exception guarantee: strong.
     */
    virtual std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const override;

    /**
     * @brief isGameOver tells wether the game is overor not.
     * @pre City is in gamestate.
     * @return `true`, if game is over, else ´false´
     * @post Exception guarantee: nothrow.
     */
    virtual bool isGameOver() const override;


    // Omat
    /**
     * @brief endGame ends the game, sets the city in gameover state.
     * @pre City is in game state.
     * @post City is in gameover state.
     */
    void endGame();

private:
    const int COORD_SCALING = 500;
    const int INIT_STATE = 0;
    const int GAME_STATE = 1;
    const int END_STATE = 2;

    std::shared_ptr<QTime> clock_;
    std::vector<std::shared_ptr<Interface::IStop>> stops_;
    int state_;
    std::vector<std::shared_ptr<Interface::IActor>> actors_;
    std::shared_ptr<GameWindow> mainWindow_;
};

#endif // CITY_HH
