#ifndef FOODGENERATOR_HPP
#define FOODGENERATOR_HPP
#include <SFML/Graphics.hpp>


class FoodGenerator
{
public:
    FoodGenerator();

    void update(sf::Time dt);

private:
    sf::Time timeLastFood;
};

#endif // FOODGENERATOR_HPP
