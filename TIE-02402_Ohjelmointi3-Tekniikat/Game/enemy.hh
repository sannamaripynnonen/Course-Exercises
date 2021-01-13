#ifndef ENEMY_HH
#define ENEMY_HH

#include <memory>
#include <interfaces/iactor.hh>
#include <core/location.hh>


class Enemy : public Interface::IActor
{
public:
    /**
     * @brief Enemy constructor.
     */
    Enemy();

    /**
     * @brief ~Enemy destructor.
     */
    virtual ~Enemy();

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
     * @brief takeDamage reduces enemy's hp.
     * @param damage Damage taken.
     * @pre -
     * @post Hp is reduced.
     */
    void takeDamage(int damage);

private:
    const int START_HP = 2;
    std::shared_ptr<Interface::Location> location_ = nullptr;
    int hp_;
};

#endif // ENEMY_HH
