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
     *  @brief constructor using given position, life points, and lifetime
     *
     *  @param pos position
     *  @param HP health points
     *  @param LT lifetime
     *
     *  @note sets the direction angle using a uniform distribution uniform(0.0, TAU) from Random.hpp/cpp
     *  @note sets the time it last spun to 0 seconds using sf::Time::Zero
     */
    Animal(const Vec2d& pos, double HP, double LT);

    /*!
     *  @brief constructor using only given position
     *
     *  @param pos position
     *
     *  @note calls constructor using 1.0 as LP and LT
     */
    Animal(const Vec2d& pos);

    /*!
     *  @brief default constructor
     *
     *  @note calls constructor using Vec2d() as pos, 1.0 as HP and LT
     */
    Animal();

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
    virtual sf::Sprite getSprite() const = 0;

    /*!
     *  @brief
     */
    double getHP() const;

    /*!
     *  @brief checks if animal is dead
     *
     *  @return true if dead
     *
     *  @note animal is considered dead if HP and LT <= 0
     */
    bool isDead() const;

    /*!
     *  @brief makes animal move
     *
     *  @note gives the angle of direction a chance to change periodically based on RotationProbs
     */
    void move(sf::Time dt);

    /*!
     *  @brief
     */
    void update(sf::Time dt);

    /*!
     *  @brief gives back the probalities of rotation
     *
     *  @return rotation probabilities
     */
    RotationProbs computeRotationProbs();

    /*!
     *  @brief draws animals
     *
     *  @note if debug on might have special features
     */
    virtual void drawOn(sf::RenderTarget& target) const = 0;

protected:
    /*!
     *  @brief sets direction angle
     *
     *  @note in protected to restrict access only to sub-classes
     *  @note ensures that angle is between 0 and 2pi using fmod
     */
    void setDirection(Angle setAngle);

private:
    Angle dirAngle;
    double healthPoints;
    double lifetime;
    sf::Time timeLastRot;
};

#endif // ANIMAL_HPP
