#include "enemy.hh"
#include <QDebug>
#include <../CourseLib/errors/gameerror.hh>

Enemy::Enemy():
    hp_(START_HP)
{
}

Enemy::~Enemy()
{
}

Interface::Location Enemy::giveLocation() const
{
    if (location_ == nullptr)
    {
        throw Interface::GameError("Actor wasn't given a location");
    }
    return *location_.get();
}

void Enemy::move(Interface::Location loc)
{
    int limit = 500;
    if (loc.giveX() > limit || loc.giveY() > limit)
    {
        throw Interface::GameError("Invalid location");
    }
    location_ = std::make_shared<Interface::Location>(loc);
}

bool Enemy::isRemoved() const
{

    if (hp_ <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Enemy::remove()
{
    hp_ = 0;
}

void Enemy::takeDamage(int damage)
{
    hp_ = hp_ - damage;
}
