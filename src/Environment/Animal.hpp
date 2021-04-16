#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"

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
     *  @note sets the time it last spun to 0 seconds using sf::Time::Zero
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
     *  @brief
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
     *  @brief updates the animal by making it move, decrements its lifetime and adds dt to the time it last spun
     */
    virtual void update(sf::Time dt) override;

    /*!
     *  @brief gives back the probalities of rotation
     *
     *  @return rotation probabilities
     */
    virtual RotationProbs computeRotationProbs() const;

protected:
    /*!
     *  @brief sets direction angle
     *
     *  @note in protected to restrict access only to sub-classes
     *  @note ensures that angle is between 0 and 2pi using fmod to avoid having huge angles
     */
    void setDirection(Angle setAngle);

private:
    Angle dirAngle;
    double healthPoints;
    double lifetime;
    sf::Time timeLastRot;
};

#endif // ANIMAL_HPP
