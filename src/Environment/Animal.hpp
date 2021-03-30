#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>

class Animal : public Positionable
{
public:

    Animal(const Vec2d& pos, double LP, double LT);

    Animal();

    double getSpeed() const;

    Angle getDirection() const;

    void setDirection(Angle setAngle);

    bool isDead() const;

    void drawOn(sf::RenderTarget& target) const;

    void move(sf::Time dt);

private:
    Angle directionAngle;
    double lifePoints;
    double lifetime;
};

#endif // ANIMAL_HPP
