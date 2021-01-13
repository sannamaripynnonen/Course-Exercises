#ifndef BULLET_HH
#define BULLET_HH

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <../CourseLib/interfaces/iactor.hh>
#include <actoritem.hh>


class Bullet : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:

    /**
     * @brief Bullet constructor.
     */
    Bullet();

    /**
     * @brief Bullet destructor.
     */
    virtual ~Bullet();

    // QGraphicsItem
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


public slots:
    /**
     * @brief move moves the bullet forward and destroys it if it collides with an actor.
     * @pre -
     * @post bullet is moved or destroyed.
     */
    void move();

signals:
    /**
     * @brief enemyShot sends signal that bullet collided with an enemy actor.
     * @param enemy pointer to collided enemy.
     */
    void enemyShot(ActorItem* enemy);

    /**
     * @brief nysseShot sends signal that bullet collided with a nysse actor.
     * @param nysse pointer to collided nysse.
     */
    void nysseShot(ActorItem* nysse);
};

#endif // BULLET_HH
