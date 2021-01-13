#ifndef ACTORITEM_HH
#define ACTORITEM_HH

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <../CourseLib/interfaces/iactor.hh>
#include <../CourseLib/interfaces/istop.hh>

const int WIDTH = 25;
const int HEIGHT = 15;
const int ENEMY_TYPE = 100;
const int PLAYER_TYPE = 200;
const int BUS_TYPE = 1;
const int STOP_TYPE = 150;

class ActorItem : public QGraphicsItem
{
public:
    /**
     * @brief ActorItem constructor.
     * @param x ActorItem's x coordinate.
     * @param y ActorItem's y coordinate.
     * @param type ActorItem's type (player, enemy, bus or stop).
     */
    ActorItem(int x, int y, int type = 0);

    /**
     * @brief ~ActorItem descructor
     */
    virtual ~ActorItem();

    // QGraphicsItem
    virtual QRectF boundingRect() const override;
    QRectF ownBoundingRect(int width, int height) const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


    /**
     * @brief setCoord sets given coordinates to actorItem.
     * @param x ActorItem's new x coordinate.
     * @param y ActorItem's new y coordinate.
     * @pre -
     * @post ActorItem has new coordinates.
     */
    void setCoord(int x, int y);

    /**
     * @brief setActor sets pointer to IActor
     * @param actor pointer to IActor
     * @pre -
     * @post pointer to IActor has been set to ActorItem.
     */
    void setActor(std::shared_ptr<Interface::IActor> actor);

    /**
     * @brief getActor returns pointer to IActor.
     * @return pointer to IActor.
     * @pre setActor has been called.
     * @post pointer is returned.
     */
    std::shared_ptr<Interface::IActor> getActor() const;

    /**
     * @brief getType returns ActorItem's type.
     * @return ActorItem's type.
     * @pre -
     * @post type is returned.
     */
    int getType() const;

    /**
     * @brief setText sets textItem to ActorItem.
     * @param text to be set.
     * @pre -
     * @post textItem is set to ActorItem.
     */
    void setText(QGraphicsSimpleTextItem* text);

    /**
     * @brief getText returns textItem set to ActorItem.
     * @return textItem set for ActorItem.
     * @pre setText has been called.
     * @post textItem is returned.
     */
    QGraphicsSimpleTextItem* getText() const;

    /**
     * @brief setStop sets pointer to IStop.
     * @param actor pointer to IActor.
     * @pre -
     * @post pointer to IStop is set to ActorItem.
     */
    void setStop(std::shared_ptr<Interface::IStop> actor);

    /**
     * @brief getStop returns pointer to IStop.
     * @return pointer to IStop.
     * @pre setStop has been called.
     * @post pointer to IStop is returned.
     */
    std::shared_ptr<Interface::IStop> getStop() const;

    /**
     * @brief getX returns ActorItem's x coordinate.
     * @return x coordinate.
     * @pre -
     * @post x coordinate is returned.
     */
    int getX() const;

    /**
     * @brief getY return ActorItem's y coordinate.
     * @return y coordinate.
     * @pre -
     * @post y coordinate is returned.
     */
    int getY() const;

private:
    int x_;
    int y_;
    int type_;
    std::shared_ptr<Interface::IActor> actor_;
    std::shared_ptr<Interface::IStop> stop_;
    QGraphicsSimpleTextItem* text_;
};

#endif // ACTORITEM_HH
