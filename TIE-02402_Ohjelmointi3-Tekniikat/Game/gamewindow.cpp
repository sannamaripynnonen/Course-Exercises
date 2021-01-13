#include <QImage>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QVectorIterator>

#include "gamewindow.hh"
#include "ui_gamewindow.h"
#include "startdialog.hh"
#include "bullet.hh"
#include "keypresseater.hh"

const int PADDING = 5;
const int TEXT_MARGIN = 15;

const int UP = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int DOWN = 4;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    ui->gameView->setFixedSize(width_ + PADDING, height_ + PADDING);
    ui->timeNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->scoreNumber->setSegmentStyle(QLCDNumber::Flat);

    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0, width_, height_);

    resize(minimumSizeHint());
    ui->gameView->setRenderHint(QPainter::Antialiasing);

    addPlayerItem(0, 0);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateMap);
    timer->start(tick_);

    enemyMoveTimer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::moveEnemy);
    int enemyTick = 1000;
    enemyMoveTimer->start(enemyTick);

    KeyPressEater *keyPressEater = new KeyPressEater(this);
    connect(keyPressEater, &KeyPressEater::sendKeyEvent, this, &GameWindow::keyPressEvent);
    ui->gameView->installEventFilter(keyPressEater);
    ui->startButton->installEventFilter(keyPressEater);
}

GameWindow::~GameWindow()
{
    delete ui;
}

// Peli-ikkuna

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W) {
        emit playerMoved(UP);
    }

    if (event->key() == Qt::Key_S)
    {
        emit playerMoved(DOWN);
    }

    if (event->key() == Qt::Key_D)
    {
        emit playerMoved(RIGHT);
    }

    if (event->key() == Qt::Key_A)
    {
        emit playerMoved(LEFT);
    }
    if (event->key() == Qt::Key_Space) {
        Bullet* bullet = new Bullet();
        bullet->setPos(player_->x()+25, player_->y()+20);
        map->addItem(bullet);
        connect(bullet, &Bullet::nysseShot, this, &GameWindow::deleteNysse);
        connect(bullet, &Bullet::enemyShot, this, &GameWindow::enemyHit);
    }
    if (event->key() == Qt::Key_1)
    {
        emit buyOrUseDrone();
    }
    if (event->key() == Qt::Key_2)
    {
        emit buyOrUseCar();
    }
    if (event->key() == Qt::Key_3)
    {
        emit buyMaxHp();
    }
    if (event->key() == Qt::Key_4)
    {
        emit buyHp();
    }
    if (event->key() == Qt::Key_5)
    {
        emit useBike();
    }
}

void GameWindow::setPicture(QImage(mapImage))
{
    ui->gameView->setBackgroundBrush(mapImage);
}

int GameWindow::getWidth()
{
    return width_;
}

int GameWindow::getHeight()
{
    return height_;
}

void GameWindow::stopTimer()
{
    timer->stop();
}


// Ikkunan tietojen päivitys

void GameWindow::updateVehicle(QString& text)
{
    ui->vehicleLabel->setText(text);
}

void GameWindow::updateDestroyedEnemys(int enemys)
{
    ui->enemyLabel->setNum(enemys);
}

void GameWindow::updateDestroyedNysses(int nysses)
{
    ui->nysseLabel->setNum(nysses);
}

void GameWindow::updateScore(int points)
{
    ui->scoreNumber->display(points);
}

void GameWindow::updateTime(int seconds)
{
    ui->timeNumber->display(seconds);
}

void GameWindow::updateHp(int hp)
{
    ui->hpLabel->setNum(hp);
}

void GameWindow::updateMaxHp(int hp)
{
    ui->maxHpLabel->setNum(hp);
}

void GameWindow::updateMoney(int money)
{
    ui->moneyLabel->setNum(money);
}


// Pelihahmojen lisäys

void GameWindow::addStop(int locX, int locY, std::shared_ptr<Interface::IStop> stop, int passengers)
{
    if ((locX >= 0 && locX <= width_) && (locY >= 0 && locY <= height_))
    {
        QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(QString::number(passengers));
        text->setPos(locX, locY-TEXT_MARGIN);
        ActorItem* nActor = new ActorItem(locX, locY, STOP_TYPE);
        nActor->setStop(stop);
        nActor->setText(text);
        stops_.push_back(nActor);
        map->addItem(nActor);
        map->addItem(text);
    }
}

void GameWindow::addNysse(int locX, int locY, std::shared_ptr<Interface::IActor> actor, int passengers)
{
    QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(QString::number(passengers));
    text->setPos(locX, locY-TEXT_MARGIN);

    ActorItem* nActor = new ActorItem(locX, locY, BUS_TYPE);
    nActor->setText(text);
    nActor->setActor(actor);
    actors_.push_back(nActor);
    map->addItem(nActor);
    map->addItem(text);
}

void GameWindow::addEnemyItem(int locX, int locY, std::shared_ptr<Interface::IActor> enemy)
{
    ActorItem* nEnemy = new ActorItem(locX, locY, ENEMY_TYPE);
    nEnemy->setActor(enemy);
    enemys_.push_back(nEnemy);
    map->addItem(nEnemy);
}

void GameWindow::addPlayerItem(int locX, int locY)
{
    player_ = new ActorItem(locX, locY, PLAYER_TYPE);
    map->addItem(player_);
}


// Pelihahmojen päivitys

void GameWindow::movePlayer(int speed, int direction)
{
    int xChange = 0;
    int yChange = 0;
    if (direction == UP)
    {
        yChange = -1*speed;
    }

    else if (direction == DOWN)
    {
        yChange = speed;
    }
    else if (direction == RIGHT)
    {
        xChange = speed;
    }
    else
    {
        xChange = -1*speed;
    }
    int newX = player_->getX()+xChange;
    int newY = player_->getY()+yChange;
    if ((newX <= width_ && newX >= 0) && (newY <= height_ && newY >= 0))
    {
        player_->setCoord(newX, newY);
        handlePlayerCollision();
        map->update();
    }
}

void GameWindow::moveNysse(int nX, int nY, std::shared_ptr<Interface::IActor> actor, int passengers)
{
    for (int i = 0; i < actors_.size(); i++)
    {
        auto actorItem = actors_.at(i);
        auto iActor = actorItem->getActor();
        // Tämä sitä varten, että bussit eivät pysähdy kartan reunoille.
        int margin = 25;
        if (iActor == actor)
        {
            if ((nX >= 0-margin && nX <= width_+margin) && (nY >= 0-margin && nY <= height_+margin))
            {
                actorItem->setCoord(nX, nY);
                auto text = actorItem->getText();
                text->setText(QString::number(passengers));
                text->setPos(nX, nY-TEXT_MARGIN);
            }
            break;
        }
    }
}

void GameWindow::handlePlayerCollision()
{
    auto collItems = map->collidingItems(player_);
    foreach (QGraphicsItem* i, collItems)
    {
        auto actor = dynamic_cast<ActorItem*>(i);
        if (actor != 0)
        {
            if (actor->getType() == ENEMY_TYPE)
            {
                auto enemy = actor->getActor();
                deleteEnemy(enemy);
                emit playerCollisionWithEnemy();
            }
        }
    }
}

void GameWindow::deleteEnemy(std::shared_ptr<Interface::IActor> enemy)
{
    for(int i = 0; i <enemys_.length(); i++){
        if(enemy == enemys_.at(i)->getActor()){
            map->removeItem(enemys_.at(i));
            delete enemys_.at(i);
            enemys_.remove(i);
        }
    }
}

void GameWindow::updateStops()
{
    // Ei mikään fiksuin tapa päivittää aina kaikkia stoppeja, kun vain yksi muuttuu kerralla,
    // mutta jos matkustaja poistuu stopilta, en ainakaan keksinyt tapaa, jolla kaivaa
    // esiin tieto siitä, miltä stopilta matkustaja lähti. Logic-luokalla tämä tieto on, mutta
    // se ei anna sitä citylle, eikä kurssin koodia ilmeisesti saanut muokata.
    for (int i = 0; i < stops_.size(); i++)
    {
        auto stopItem = stops_.at(i);
        auto iStop = stopItem->getStop();
        int count = iStop->getPassengers().size();
        auto text = stopItem->getText();
        text->setText(QString::number(count));
    }
}


// Slots

void GameWindow::on_startButton_clicked()
{
    emit gameStarted();
}

void GameWindow::updateMap()
{
    map->update();
}

void GameWindow::moveEnemy()
{
    int margin = 20;
    int randNegativeScale = 20;
    int randPositiveScale = 40;
    int min = 0;
    int changeSign = -1;
    for (int i = 0; i < enemys_.size(); i++)
    {
        int x = (rand() % randPositiveScale + min) - randNegativeScale;
        int y = (rand() % randPositiveScale + min) - randNegativeScale;
        auto enemy = enemys_.at(i);

        int newX = enemy->getX()+x;
        int newY = enemy->getY()+y;

        if (newX > width_ || newX < min-margin)
        {
            x = changeSign * x;
            newX = enemy->getX()+x;
        }
        if (newY > height_ || newY < min-margin)
        {
            y = changeSign * y;
            newY = enemy->getY()+y;
        }
        enemy->setCoord(newX, newY);
    }
}

void GameWindow::deleteNysse(ActorItem* nysse)
{
    for(int i = 0; i <actors_.length(); i++)
    {
        auto actor = actors_.at(i);
        if(nysse == actor)
        {
            std::shared_ptr<Interface::IActor> deletedNysse = actor->getActor();
            auto text = actor->getText();
            map->removeItem(text);
            delete text;
            map->removeItem(actor);
            delete actor;
            actors_.remove(i);
            emit nysseDestroyed(deletedNysse);
        }
    }
}

void GameWindow::enemyHit(ActorItem* actor)
{
    std::shared_ptr<Interface::IActor> enemy = actor->getActor();
    emit enemyShot(enemy);
}
