#include "Pheromone.hpp"
#include "./Application.hpp"
#include "./Utility/Utility.hpp"

Pheromone::Pheromone()
{
    //Done
}

Pheromone::Pheromone(const Vec2d& vect, Quantity quant)
    :Positionable(vect), quantity(quant)
{
    //Done
}

void Pheromone::update(sf::Time dt)
{
    quantity*=getAppConfig().pheromone_evaporation_rate;
}

void Pheromone::drawOn(sf::RenderTarget &target) const
{
    sf::Color couleur(sf::Color::Green);
    couleur.a/=4;
    auto const pheroCircle = buildCircle((getPosition()).toVec2d(), 5, couleur);
    target.draw(pheroCircle);
    /*
    if (isDebugOn()) //if debug on you can see the quantity of pheromones
    {
        auto const text = buildText(to_nice_string(quantity), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black);
        target.draw(text); //shows quantity via a text
    }
    */
}

bool Pheromone::isNegligeable()
{
    return quantity<getAppConfig().pheromone_threshold;
}
