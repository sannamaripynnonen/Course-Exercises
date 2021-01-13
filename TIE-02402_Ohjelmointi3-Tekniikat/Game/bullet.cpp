#include <QTimer>
#include <QList>
#include "bullet.hh"
#include "actoritem.hh"


Bullet::Bullet()
{
    QTimer* timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    int tick = 50;
    timer->start(tick);
}

Bullet::~Bullet()
{
}

void Bullet::move()
{
    auto collItems = collidingItems();
    foreach (QGraphicsItem* i, collItems)
    {
        auto actor = dynamic_cast<ActorItem*>(i);
        if (actor != 0)
        {
            if (actor->getType() == BUS_TYPE)
            {
                emit nysseShot(actor);
                scene()->removeItem(this);
                delete this;
                return;
            }

            if (actor->getType() == ENEMY_TYPE)
            {
                emit enemyShot(actor);
                scene()->removeItem(this);
                delete this;
                return;
            }
        }
    }
    int bulletMovement = 10;
    setPos(x(), y()+bulletMovement);
}

QRectF Bullet::boundingRect() const
{
    return QRectF(0, 0, 5, 50);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF bounds = boundingRect();
    painter->setBrush(Qt::red);
    painter->drawRect(bounds);
}
