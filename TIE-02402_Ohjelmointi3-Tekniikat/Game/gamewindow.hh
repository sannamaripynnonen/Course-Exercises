#ifndef GAMEWINDOW_HH
#define GAMEWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QWidget>
#include <QTimer>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>
#include <QPainter>
#include <../CourseLib/actors/stop.hh>

#include "ui_gamewindow.h"
#include "actoritem.hh"
#include "player.hh"
#include "bullet.hh"
#include "keypresseater.hh"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief GameWindow constructor.
     * @param parent Parent widget.
     */
    explicit GameWindow(QWidget *parent = nullptr);

    /**
     * @brief ~GameWindow destructor.
     */
    virtual ~GameWindow();

    // Peli-ikkuna
    /**
     * @brief keyPressEvent handles key events.
     * @param event pressed key.
     */
    virtual void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief setPicture sets background image to game window.
     * @pre -
     * @post background image is set.
     */
    void setPicture(QImage);

    /**
     * @brief getWidth return width of the view.
     * @return QGraphicsView width.
     * @pre -
     * @post width is returned.
     */
    int getWidth();

    /**
     * @brief getHeightreturn height of the view.
     * @return QGraphicsView height.
     * @pre -
     * @post height is returned.
     */
    int getHeight();

    /**
     * @brief stopTimer stops GameWindow timer.
     * @pre -
     * @post timer is stopped.
     */
    void stopTimer();


    // Ikkunan tietojen päivitys
    /**
     * @brief updateVehicle updates game window's text label showing what vehicle player is using.
     * @param text vechicle used.
     * @pre -
     * @post text label is updated.
     */
    void updateVehicle(QString& text);

    /**
     * @brief updateDestroyedEnemys updates game window's text label showing how many enemys are destroyed.
     * @param enemys number of destroyed enemys.
     * @pre -
     * @post text label is updated.
     */
    void updateDestroyedEnemys(int enemys);

    /**
     * @brief updateDestroyedNysses updates game winodw's text label showing how many nysses are destroyed.
     * @param nysses number of destroyed nysses.
     * @pre -
     * @post text label is updated.
     */
    void updateDestroyedNysses(int nysses);

    /**
     * @brief updateScore updates game window's score label.
     * @param points player's current score.
     * @pre -
     * @post label is updated.
     */
    void updateScore(int points);

    /**
     * @brief updateTime updates game window's time label.
     * @param seconds how many seconds left on the game.
     * @pre -
     * @post label is updated.
     */
    void updateTime(int seconds);

    /**
     * @brief updateHp updates game winodw's HP label.
     * @param hp how much hp left.
     * @pre -
     * @post label is updated.
     */
    void updateHp(int hp);

    /**
     * @brief updateMaxHp updates game window's Max HP label.
     * @param hp how much is the max hp.
     * @pre -
     * @post label is updated.
     */
    void updateMaxHp(int hp);
    /**
     * @brief updateMoney updates game window's money label.
     * @param money how much money the player has.
     * @pre -
     * @post label is updated.
     */
    void updateMoney(int money);


    // Pelihahmojen lisäys
    /**
     * @brief addStop adds stops as ActorItems to the game view and adds passenger count as a text.
     * @param locX x coordinate for the stop.
     * @param locY y coordinate for the stop.
     * @param stop pointer to IStop.
     * @param passengers number of passengers at the stop.
     * @pre -
     * @post stops are added to the game view and passenger count is shown.
     */

    void addStop(int locX, int locY, std::shared_ptr<Interface::IStop> stop, int passengers);
    /**
     * @brief addNysse adds nysses as ActorItems to the game view and adds passenger count as a text.
     * @param locX x coordinate for the nysse.
     * @param locY y coordinate for the nysse.
     * @param actor pointer to IActor.
     * @param passengers number of passengers on the nysse.
     * @pre -
     * @post nysses are added to the game view and passenger count is shown.
     */
    void addNysse(int locX, int locY, std::shared_ptr<Interface::IActor> actor, int passengers);

    /**
     * @brief addEnemyItem adds enemys as ActorItems to the game view.
     * @param locX x coordinate for the enemy.
     * @param locY y coordinate for the enemy.
     * @param enemy pointer to IActor.
     * @pre -
     * @post enemys are added to the game view.
     */
    void addEnemyItem(int locX, int locY, std::shared_ptr<Interface::IActor> enemy);

    /**
     * @brief addPlayerItem adds player as Actor Item in the game view.
     * @param locX x coordinate for the player.
     * @param locY y coordinate for the player.
     * @pre -
     * @post player is added to the game view.
     */
    void addPlayerItem(int locX, int locY);


    // Pelihahmojen päivitys
    /**
     * @brief movePlayer moves player in the game view.
     * @param speed how fast player moves.
     * @param direction direction of movement.
     * @pre addPlayerItem has been called.
     * @post All actions are completed.
     */
    void movePlayer(int speed, int direction);

    /**
     * @brief moveNysse moves nysse in the game view and updates passanger count as a text.
     * @param nX new x coordinate.
     * @param nY new y coordinate.
     * @param actor pointer to iActor.
     * @param passengers number of passengers on the nysse.
     * @pre -
     * @post Nysses is moved and passanger count is shown.
     */
    void moveNysse(int nX, int nY, std::shared_ptr<Interface::IActor> actor, int passengers);

    /**
     * @brief handlePlayerCollision checks if player collides with enemys.
     * @pre addPlayerItem has been called.
     * @post sends signal when player hits enemy.
     */
    void handlePlayerCollision();

    /**
     * @brief deleteEnemy deletes enemy from the game.
     * @param enemy pointer to enemy to be deleted.
     * @pre -
     * @post enemy is deleted.
     */
    void deleteEnemy(std::shared_ptr<Interface::IActor> enemy);

    /**
     * @brief updateStops updates stops' textItem which shows how many passengers are at the stop.
     * @pre -
     * @post textItem is updated.
     */
    void updateStops();


signals:
    /**
     * @brief gameStarted sends signal that game is started.
     */
    void gameStarted();

    /**
     * @brief playerCollisionWithEnemy sends signal that player collides with enemy.
     */
    void playerCollisionWithEnemy();

    /**
     * @brief buyMaxHp sends signal that player wants to buy Max Hp.
     */
    void buyMaxHp();

    /**
     * @brief buyHp sends signal that player wnats to buy Hp.
     */
    void buyHp();

    /**
     * @brief buyOrUseDrone sends signal that player wants to buy or use a drone.
     */
    void buyOrUseDrone();

    /**
     * @brief buyOrUseCar sends signal that player wants to buy or use a car.
     */
    void buyOrUseCar();

    /**
     * @brief useBike sends signal that player wants to use a bike.
     */
    void useBike();

    /**
     * @brief playerMoved sends signal that player item is to be moved in a certain direction.
     * @param direction where player item is moved.
     */
    void playerMoved(int direction);

    /**
     * @brief nysseDestroyed sends signal that the nysse is destroyed.
     * @param deletedNysse pointer to IActor that is destroyed.
     */
    void nysseDestroyed(std::shared_ptr<Interface::IActor> deletedNysse);

    /**
     * @brief enemyShot sends signal that the enemy is shot.
     * @param enemy pointer to IActor that is shot.
     */
    void enemyShot(std::shared_ptr<Interface::IActor> enemy);

private slots:
    /**
     * @brief on_startButton_clicked starts the game.
     * @pre -
     * @post signal gameStarted is sent.
     */
    void on_startButton_clicked();

    /**
     * @brief updateMap updates gameView
     * @pre -
     * @post scene is updated.
     */
    void updateMap();

    /**
     * @brief moveEnemy moves enemy item randomly.
     * @pre -
     * @post enemy item has a new location.
     */
    void moveEnemy();

    /**
     * @brief deleteNysse deletes nysse from the game and sends a signal thay nysse is destroyed.
     * @param actor pointer to nysse item.
     * @pre -
     * @post nysse is deleted and signal is send.
     */
    void deleteNysse(ActorItem* actor);

    /**
     * @brief enemyHit sends a signal that enemy is hit.
     * @param actor pointer to enemy item
     * @pre -
     * @post signal enemyShot is sent.
     */
    void enemyHit(ActorItem* actor);

private:
    Ui::GameWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    QVector<ActorItem*> actors_;
    QVector<ActorItem*> stops_;
    QVector<ActorItem*> enemys_;
    ActorItem *player_;
    QTimer *enemyMoveTimer;

    int width_ = 500;
    int height_ = 500;
    int tick_ = 500;
};

#endif // GAMEWINDOW_HH
