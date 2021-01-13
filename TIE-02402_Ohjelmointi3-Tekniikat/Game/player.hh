#ifndef PLAYER_HH
#define PLAYER_HH

#include <QString>
#include <QObject>
#include <memory>
#include <interfaces/iactor.hh>
#include <core/location.hh>

/**
 * @brief Defines class for the plaer.
 */

class Player : public Interface::IActor
{

public:
    /**
     * @brief Player constructor.
     */
    Player();

    /**
     * @brief ~Player destructor.
     */
    virtual ~Player();

    // IActor-rajapinta
    // Ei käytössä
    /**
     * @brief giveLocation returns the location of the actor.
     * @pre -
     * @return Actors location.
     * @post Exception guarantee: strong.
     * @exception GameError - actor wasn't given a location.
     */
    virtual Interface::Location giveLocation() const override;

    // Ei käytössä
    /**
     * @brief move-method moves the actor to given location.
     * @param loc Actors new location.
     * @pre -
     * @post Actors location is sij. Excaption guarantee: strong.
     * @exception GameError Location is not possible.
     */
    virtual void move(Interface::Location loc) override;

    /**
     * @brief isRemoved tells if the actor is removed ingame.
     * @pre -
     * @return `true`, if actor is removed ingame, otherwise `false`.
     * @post Exception guarantee: nothrow.
     */
    virtual bool isRemoved() const override;

    /**
     * @brief remove marks the actor as removed.
     * @pre Actor is not removed already.
     * @post Actor is removed, after this isRemoved() returns `true`. Exception guarantee: basic.
     */
    virtual void remove() override;
    

    // Omat
    /**
     * @brief getName returns player's name.
     * @pre setName has been called.
     * @post Returns player's name.
     * @return Player's name.
     */
    QString getName() const;

    /**
     * @brief setName sets player's name.
     * @param name Name to give.
     * @pre -
     * @post Player's name is set.
     */
    void setName(QString name);

    /**
     * @brief addMoney adds money for player.
     * @param sum Amount of money.
     * @pre sum >= 0
     * @post Money is added.
     */
    void addMoney(int sum);

    /**
     * @brief useMoney tells if player has enough money to buy and reduces money.
     * @param sum Amount of money.
     * @pre sum >= 0
     * @post Player's money is reduced, if player has enough money to buy.
     * @return Has player enough money to buy.
     */
    bool useMoney(int sum);

    /**
     * @brief takeDamage reduces player's hp.
     * @param damage Damage taken.
     * @pre damage >= 0
     * @post Hp is reduced.
     */
    void takeDamage(int damage);

    /**
     * @brief buyMaxHp increases player's maxHp if player has enough money.
     * @param amount Amount of hp to buy.
     * @pre amount >= 0
     * @post Player's maxHp is increased if player has enough money.
     */
    void buyMaxHp(int amount, int cost);

    /**
     * @brief buyHp increases player's hp if player has enough money.
     * @param amount Amount of hp to buy.
     * @pre amount >= 0
     * @post Player's hp is increased if player has enough money.
     */
    void buyHp(int amount, int cost);

    /**
     * @brief getMoney returns player's money.
     * @pre -
     * @post Returns player's money.
     * @return Player's money.
     */
    int getMoney() const;

    /**
     * @brief getHp returns player's hp.
     * @pre -
     * @post Returns player's hp.
     * @return Player's hp.
     */
    int getHp() const;

    /**
     * @brief getMaxHp returns player's maxHp.
     * @pre -
     * @post Returns player's maxHp.
     * @return Player's maxHp.
     */
    int getMaxHp() const;

    /**
     * @brief getDamage gives player's damage.
     * @pre -
     * @post Returns player's damage.
     * @return Player's damage.
     */
    int getDamage() const;

    /**
     * @brief getMovementSpeed gives player's speed.
     * @pre -
     * @post Returns player's speed.
     * @return Player's speed.
     */
    int getMovementSpeed() const;

    /**
     * @brief hasCar tells if player has a car.
     * @pre -
     * @post Return's if player has a car.
     * @return If player has a car.
     */
    bool hasCar() const;

    /**
     * @brief hasDrone tells if player has a drone.
     * @pre -
     * @post Return's if player has a drone.
     * @return If player has a drone.
     */
    bool hasDrone() const;

    /**
     * @brief buyCar adds a car for player to use.
     * @pre -
     * @post Player has a car.
     */
    void buyCar();

    /**
     * @brief buyDrone adds a drone for player to use.
     * @pre -
     * @post Player has a drone.
     */
    void buyDrone();

    /**
     * @brief setCar sets player to use car.
     * @pre hasCar() == true.
     * @post Player is using car.
     */
    void setCar();

    /**
     * @brief setCar sets player to use bike.
     * @pre -
     * @post Player is using bike.
     */
    void setBike();

    /**
     * @brief setCar sets player to use drone.
     * @pre hasDrone() == true.
     * @post Player is using drone.
     */
    void setDrone();

    /**
     * @brief isUsingCar tells if player is using car.
     * @pre -
     * @post Returns if player is using car.
     * @return If player is using car
     */
    bool isUsingCar() const;

    // Kulkuvälinevaihtoehdot
    const int BIKE = 1;
    const int DRONE = 2;
    const int CAR = 3;

private:
    const int START_SPEED = 5;
    const int START_HP = 200;
    const int START_MONEY = 0;
    const int START_DAMAGE = 1;
    const int VECHICLE_COST = 100;

    std::shared_ptr<Interface::Location> location_ = nullptr;
    QString name_ = "";
    int hp_;
    int maxHp_;
    int money_;
    int movementSpeed_;
    int damage_;
    int vehicle_;
    bool hasDrone_ = false;
    bool hasCar_ = false;
};

#endif // PLAYER_HH
