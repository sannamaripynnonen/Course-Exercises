#include <../CourseLib/errors/gameerror.hh>
#include "player.hh"

Player::Player():
    hp_(START_HP),
    maxHp_(START_HP),
    money_(START_MONEY),
    movementSpeed_(START_SPEED),
    damage_(START_DAMAGE),
    vehicle_(BIKE)
{
}

Player::~Player()
{
}

Interface::Location Player::giveLocation() const
{
    if (location_ == nullptr)
    {
        throw Interface::GameError("Actor wasn't given a location");
    }
    return *location_.get();
}

void Player::move(Interface::Location loc)
{
    int limit = 500;
    if (loc.giveX() > limit || loc.giveY() > limit)
    {
        throw Interface::GameError("Invalid location");
    }
    location_ = std::make_shared<Interface::Location>(loc);
}

bool Player::isRemoved() const
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

void Player::remove()
{
    hp_ = 0;
}

QString Player::getName() const
{
    return name_;
}

void Player::setName(QString name)
{
    name_ = name;
}

void Player::addMoney(int sum)
{
    money_ = money_ + sum;
}

bool Player::useMoney(int sum)
{
    if (sum <= money_)
    {
        money_ = money_ - sum;
        return true;
    }
    else
    {
        return false;
    }
}

void Player::takeDamage(int damage)
{
    hp_ = hp_ - damage;
}

void Player::buyMaxHp(int amount, int cost)
{
    if (useMoney(cost))
    {
        maxHp_ = maxHp_ + amount;
    }
}

void Player::buyHp(int amount, int cost)
{
    if (useMoney(cost))
    {
        int newHp = hp_ + amount;
        if (newHp >= maxHp_)
        {
            hp_ = maxHp_;
        }
        else
        {
            hp_ = newHp;
        }
    }
}

int Player::getMoney() const
{
    return money_;
}

int Player::getHp() const
{
    return hp_;
}

int Player::getMaxHp() const
{
    return maxHp_;
}

int Player::getDamage() const
{
    return damage_;
}

int Player::getMovementSpeed() const
{
    return movementSpeed_;
}

bool Player::hasCar() const
{
    return hasCar_;
}

bool Player::hasDrone() const
{
    return hasDrone_;
}

void Player::buyCar()
{
    if (useMoney(VECHICLE_COST))
    {
        setDrone();
        hasDrone_ = true;
    }
}

void Player::buyDrone()
{
    if (useMoney(VECHICLE_COST))
    {
        setCar();
        hasCar_ = true;
    }
}

void Player::setCar()
{
    vehicle_ = CAR;
    movementSpeed_ = START_SPEED;
    damage_ = START_DAMAGE;
}

void Player::setBike()
{
    vehicle_ = BIKE;
    movementSpeed_ = START_SPEED;
    damage_ = START_DAMAGE;
}

void Player::setDrone()
{
    vehicle_ = DRONE;
    movementSpeed_ = 10;
    damage_ = 2;
}

bool Player::isUsingCar() const
{
    if (vehicle_ == CAR)
    {
        return true;
    }
    return false;
}
