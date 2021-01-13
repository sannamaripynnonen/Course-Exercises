#include "actoritem.hh"


ActorItem::ActorItem(int x, int y, int type): x_(x), y_(y), type_(type)
{
    setPos(mapToParent(x_, y_));
    setFlag(QGraphicsItem::ItemIsMovable);
}

ActorItem::~ActorItem()
{
}

QRectF ActorItem::boundingRect() const
{
    return QRectF(0, 0, WIDTH, HEIGHT);
}

QRectF ActorItem::ownBoundingRect(int width, int height) const
{
    return QRectF(0, 0, width, height);
}


void ActorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (type_ == PLAYER_TYPE)
    {
        painter->setBrush(Qt::black);
        QRectF bounds = ownBoundingRect(50, 20);
        painter->drawRoundedRect(bounds, 30, 20);

    }
    else if(type_ == BUS_TYPE)
    {
        QRectF bounds = boundingRect();
        painter->setBrush(Qt::blue);
        painter->drawRoundedRect(bounds, 2, 2);

    }
    else if(type_ == STOP_TYPE)
    {
        painter->setBrush(Qt::red);
        painter->drawEllipse(0,0, 10, 10);
    }
    else
    {
        QRectF bounds = ownBoundingRect(30, 30);
        painter->setBrush(Qt::green);
        painter->drawRoundedRect(bounds, 4, 4);
    }
}

void ActorItem::setCoord(int x, int y)
{
    x_ = x;
    y_ = y;
    setPos(x, y);
}

void ActorItem::setActor(std::shared_ptr<Interface::IActor> actor)
{
    actor_ = actor;
}

std::shared_ptr<Interface::IActor> ActorItem::getActor() const
{
    return actor_;
}

int ActorItem::getType() const
{
    return type_;
}

void ActorItem::setText(QGraphicsSimpleTextItem* text)
{
    text_ = text;
}

QGraphicsSimpleTextItem* ActorItem::getText() const
{
    return text_;
}

void ActorItem::setStop(std::shared_ptr<Interface::IStop> stop)
{
    stop_ = stop;
}

std::shared_ptr<Interface::IStop> ActorItem::getStop() const
{
    return stop_;
}

int ActorItem::getX() const
{
    return x_;
}

int ActorItem::getY() const
{
    return y_;
}

