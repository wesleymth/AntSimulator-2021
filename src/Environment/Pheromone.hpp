#ifndef PHEROMONE_HPP
#define PHEROMONE_HPP
#include "Positionable.hpp"
#include "./Interface/Updatable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>
#include "../Interface/Drawable.hpp"

//Cette façon simple de modéliser la phéromone sera potentiellement gourmande en ressources.
//Vous pourrez proposer des alternatives plus efficaces dans la partie « extensions » du projet.
class Pheromone: public Positionable, public Drawable
{
public:
    Pheromone();
    Pheromone(double quant, const Vec2d& vect);
    void drawOn(sf::RenderTarget &target) const override;
    bool isNegligeable();
private:
    Quantity quantity;
};

#endif // PHEROMONE_HPP
