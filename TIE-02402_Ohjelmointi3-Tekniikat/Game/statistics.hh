#ifndef STATISTICS_HH
#define STATISTICS_HH

#include <../Course/CourseLib/interfaces/istatistics.hh>

/**
 * @brief Statistics class is used to keep a record of points, destroyed nysses and destroyed enemies.
 */

class Statistics : public Interface::IStatistics
{
public:
    /**
     * @brief Statistics constructor.
     */
    Statistics();

    /**
     * @brief ~Statistics destructor.
     */
    virtual ~Statistics();

    // IStatistics-rajapinta, eivät käytössä
    /**
     * @brief morePassengers notifies, that more passangers are added to the game.
     * @param num how many new passangers are added.
     * @pre num > 0
     * @post Exception guarantee: strong
     */
    virtual void morePassengers(int num) override;

    /**
     * @brief nysseRemoved notifies, that the nysse is removed ingame.
     * @pre -
     * @post Exception guarantee: strong
     */
    virtual void nysseRemoved() override;

    /**
     * @brief newNysse notifies, that a new nysse is added to the game.
     * @pre -
     * @post Exception guarantee: strong
     */
    virtual void newNysse() override;

    /**
     * @brief nysseLeft notifies, that a nysse has left the game.
     * @pre -
     * @post Exception guarantee: strong
     */
    virtual void nysseLeft() override;


    // Omat
    /**
     * @brief givePoints gives the points.
     * @pre -
     * @post Returns points.
     * @return Points.
     */
    int givePoints() const;

    /**
     * @brief passengerDied adds points according to amount of dead pasengers.
     * @param num Amount of dead passengers.
     * @pre num >= 0
     * @post Points are added and the number of passengers is decreased, passengers >= 0.
     */
    void passengerDied(int num);

    /**
     * @brief enemyDestroyed increases the amount of destroyed enemies by one.
     * @pre -
     * @post Amount of destroyed enemies is increased.
     */
    void enemyDestroyed();

    /**
     * @brief getDestroyedEnemys gives the number of destroyed enemies.
     * @pre -
     * @post Returns the number of destroyed enemies.
     * @return Number of destroyed enemies.
     */
    int getDestroyedEnemys() const;

    /**
     * @brief nysseDestroyed increases the amount of destroyed nysses by one.
     * @pre -
     * @post The number of destroyed nysses is increased.
     */
    void nysseDestroyed();

    /**
     * @brief getDestroyedNysses gives the number of destroyed nysses.
     * @pre -
     * @post Returns the number of destroyed nysses.
     * @return Number of destroyed nysses.
     */
    int getDestroyedNysses() const;


    // Yksikkötestejä vartem
    /**
     * @brief setPassengers sets the amount of passengers.
     * @param passengers Amount of passengers to set.
     * @pre -
     * @post The amount of passengers is set and passengers >= 0.
     */
    void setPassengers(int passengers);

    /**
     * @brief setNysses sets the amount of nysses.
     * @param passengers Amount of nysses to set.
     * @pre -
     * @post The amount of nysses is set and nysses >= 0.
     */
    void setNysses(int nysses);

    /**
     * @brief getPassengers gives the number of passengers.
     * @pre -
     * @post Returns the number of passengers.
     * @return The number of passengers.
     */
    int getPassengers() const;

    /**
     * @brief getNysses gives the number of nysses.
     * @pre -
     * @post Returns the number of nysses.
     * @return The number of nysses.
     */
    int getNysses() const;

private:
    int const START_VALUE = 0;
    int score_;
    int nyssesDestroyed_;
    int enemysDestroyed_;

    //Vain rajapinnan funktioita varten, eivät käytössä varsinaisessa pelissä.
    int passengers_;
    int nysses_;
};

#endif // STATISTICS_HH
