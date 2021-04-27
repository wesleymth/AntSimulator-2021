/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"

/*!
 * @class Animal
 *
 * @brief Represents and manages the aspects of an abstract animal
 *
 * @note abstract class
 *
 * @inherits Positionable, Drawable, Updatable
 */

enum State {Idle,Attack,Defend,Escape};
class Ant;
class Termite;

class Animal : public Positionable, public Drawable, public Updatable
{
public:
    /*!
     *  @brief default constructor
     */
    Animal();

    /*!
     *  @brief constructor using a ToricPosition and specific HP and LT
     *
     *  @param pos position
     *  @param HP health points
     *  @param LT lifetime
     *
     *  @note sets the direction angle using a uniform distribution uniform(0.0, TAU) from Random.hpp/cpp
     *  @note sets the time it last spun and the fightTime to 0 seconds using sf::Time::Zero
     *  @note sets state to idle
     *  @note sets last lastFaught to nullptr
     */
    Animal(const ToricPosition& TP, double HP, double LT);

    /*!
     *  @brief constructor using given position, life points, and lifetime
     *
     *  @param pos position
     *  @param HP health points
     *  @param LT lifetime
     *
     *  @note calls constructor using a ToricPosition with ToricPosition(pos), HP and LT
     */
    Animal(const Vec2d& pos, double HP, double LT);

    /*!
     *  @brief constructor using a ToricPosition
     *
     *  @param TP ToricPosition
     *
     *  @note calls constructor using a TP, DEFAULT_ANIMAL_HP as HP and DEFAULT_ANIMAL_LIFE as LT
     */
    Animal(const ToricPosition& TP);

    /*!
     *  @brief constructor using Vec2d
     *
     *  @param pos position
     *
     *  @note calls other constructor using ToricPosition(pos)
     */
    Animal(const Vec2d& pos);

    /*!
     *  @brief gets speed of animal
     */
    virtual double getSpeed() const = 0;

    /*!
     *  @brief gets direction angle
     *
     *  @return direction angle
     */
    Angle getDirection() const;

    /*!
     *  @brief returns the health points of the animal
     *
     *  @return health points in double form
     */
    double getHP() const;

    /*!
     *  @brief checks if animal is dead
     *
     *  @return true if dead
     *
     *  @note animal is considered dead if HP or LT <= 0
     */
    bool isDead() const;

    /*!
     *  @brief makes animal move
     *
     *  @note gives the angle of direction a chance to change periodically based on RotationProbs
     */
    virtual void move(sf::Time dt);

    /*!
     *  @brief updates the animal by making it move, decrements its lifetime, adds dt to the time it last spun, and manages fights between animals
     */
    virtual void update(sf::Time dt) override;

    /*!
     *  @brief gives back the probalities of rotation
     *
     *  @return rotation probabilities
     */
    virtual RotationProbs computeRotationProbs() const;

    /*!
     *  @brief gets the strength of the animal
     *
     *  @return strength of the animal int form
     *
     *  @note dynamic resolution of links to avoid duplication of code
     */
    virtual int getStrength() const = 0;

    /*!
     *  @brief gets the attack delay of the animal
     *
     *  @return attack delay of the animal double form
     *
     *  @note dynamic resolution of links to avoid duplication of code
     */
    virtual double getAttackDelay() const = 0;

    /*!
     *  @brief draw elements that are common to all animals
     *
     *  @note if debug on you can see a line representing the direction vector and HP value in red
     *  and the ant's perception distance reprenseted by a blue ring
     */
    virtual void drawOn(sf::RenderTarget& target) const override;

    /*!
     *  @brief gets sprite of an animal
     *
     *  @return sf::Sprite
     *
     *  @note to be defined for specific animal sub-classes
     */
    virtual sf::Sprite getSprite() const = 0;

    /*!
     *  @brief takes away healthpoints depending on the strength of the animal attacked
     */
    void receiveDamage(double damageReceived);

    /*!
     *  @brief makes animal turn around
    */
    void turnAround();

    /*!
     *  @brief returns true if animal is ennemy
     *
     *  @param other Animal*
     *
     *  @return bool
     *
     *  @note to be defined for specific animal sub-classes
     */
    virtual bool isEnemy(Animal const* entity) const = 0;
    virtual bool isEnemyDispatch(Termite const* other) const = 0;
    virtual bool isEnemyDispatch(Ant const* other) const = 0;
protected:
    /*!
     *  @brief sets direction angle
     *
     *  @note in protected to restrict access only to sub-classes
     *  @note ensures that angle is between 0 and 2pi using fmod to avoid having huge angles
     */
    void setDirection(Angle setAngle);

    /*!
     *  @brief changes the state of the animal
     */
    void setState(State S);

    /*!
     *  @brief changes the fight time of the animal
     *
     *  @note uses the function sf::seconds to convert it to an sf::Time
     */
    void setFightTime(double time);

private:
    Angle dirAngle;
    double healthPoints;
    double lifetime;
    sf::Time timeLastRot;
    State state;
    sf::Time fightTime;
    Animal* lastFought;

};

#endif // ANIMAL_HPP
