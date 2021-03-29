#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>

class Animal
{
public:

    Animal(const Positionable& pos, double LP, double LT);

    Animal(const Vec2d& pos, double LP, double LT);

    Animal();

    double getSpeed() const;

    Angle getDirection() const;

    void setDirection(Angle setAngle);

    bool isDead() const;

    void drawOn(sf::RenderTarget& target) const;

private:
    Positionable position;
    Angle direction;
    double lifePoints;
    double lifetime;
};

#endif // ANIMAL_HPP
