#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"

class Animal : public Positionable //, public Drawable, public Updatable
{
public:
    /*!
     *  @brief constructor using given position, life points, and lifetime
     *
     *  @param pos position
     *  @param LP life points
     *  @param LT lifetime
     *
     *  @note sets the direction angle using a uniform distribution uniform(0.0, TAU) from Random.hpp/cpp
     *  @note sets the time it last spun to 0 seconds using sf::Time::Zero
     */
    Animal(const Vec2d& pos, double LP, double LT);

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
     *  @note calls constructor using Vec2d() as pos, 1.0 as LP and LT
     */
    Animal();

    /*!
     *  @brief gets speed of animal
     *
     *  @note uses getAppConfig().animal_default_speed
     */
    double getSpeed() const;

    /*!
     *  @brief gets direction angle
     *
     *  @return direction angle
     */
    Angle getDirection() const;

    /*!
     *  @brief checks if animal is dead
     *
     *  @return true if dead
     *
     *  @note animal is considered dead if LP and LT <= 0
     */
    bool isDead() const;

    /*!
     *  @brief draws animal
     *
     *  @note if debug on you can see a line representing the direction vector
     */
    void drawOn(sf::RenderTarget& target) const;

    /*!
     *  @brief makes animal move
     *
     *  @note gives the angle of direction a chance to change periodically based on RotationProbs
     */
    void move(sf::Time dt);

    /*!
     *  @brief gives back the probalities of rotation
     *
     *  @return rotation probabilities
     */
    RotationProbs computeRotationProbs();

protected:
    /*!
     *  @brief sets directionAngle
     *
     *  @note in protected for use of specific animals which inherit the class
     */
    void setDirection(Angle setAngle);

private:
    Angle directionAngle;
    double lifePoints;
    double lifetime;
    sf::Time timeLastRot;
};

#endif // ANIMAL_HPP
