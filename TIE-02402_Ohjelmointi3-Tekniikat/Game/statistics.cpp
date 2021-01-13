#include "statistics.hh"

Statistics::Statistics()
    : score_(START_VALUE),
      nyssesDestroyed_(START_VALUE),
      enemysDestroyed_(START_VALUE),
      passengers_(START_VALUE),
      nysses_(START_VALUE)
{
}

Statistics::~Statistics()
{
}

void Statistics::morePassengers(int num)
{
    passengers_ = passengers_ + num;
}

void Statistics::nysseRemoved()
{
    int newCount = nysses_ - 1;
    if (newCount < 0)
    {
        nysses_ = 0;
    }
    else
    {
        nysses_ = newCount;
    }
}

void Statistics::newNysse()
{
    nysses_++;
}

void Statistics::nysseLeft()
{
    nysseRemoved();
}

int Statistics::givePoints() const
{
    return score_;
}

void Statistics::passengerDied(int num)
{
    int newCount = passengers_ - num;
    if (newCount < 0)
    {
        passengers_ = 0;
    }
    else
    {
        passengers_ = newCount;
    }
    score_ = score_ + num;
}

void Statistics::enemyDestroyed()
{
    enemysDestroyed_++;
}

int Statistics::getDestroyedEnemys() const
{
    return enemysDestroyed_;
}

void Statistics::nysseDestroyed()
{
    nyssesDestroyed_++;
}

int Statistics::getDestroyedNysses() const
{
    return nyssesDestroyed_;
}

void Statistics::setPassengers(int passengers)
{
    if (passengers < 0)
    {
        passengers_ = 0;
    }
    else
    {
        passengers_ = passengers;
    }
}

void Statistics::setNysses(int nysses)
{
    if (nysses < 0)
    {
        nysses_ = 0;
    }
    else
    {
        nysses_ = nysses;
    }
}

int Statistics::getPassengers() const
{
    return passengers_;
}

int Statistics::getNysses() const
{
    return nysses_;
}
