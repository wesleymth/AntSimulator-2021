#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>

class Animal
{
public:

    double getSpeed() const;

    Angle getDirection() const;

    void setDirection(Angle setAngle);

    bool isDead() const;

    void drawOn(sf::RenderTarget& target) const;

    Animal(const Positionable& pos, double LP, int LT);

    Animal();

private:
    Positionable position;
    Angle direction;
    double lifePoints;
    int lifetime;
};

#endif // ANIMAL_HPP
