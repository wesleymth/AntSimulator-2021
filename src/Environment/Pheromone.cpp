#include "Pheromone.hpp"
#include "./Application.hpp"
#include "./Utility/Utility.hpp"

Pheromone::Pheromone()
{

}

void Pheromone::drawOn(sf::RenderTarget &target) const
{
    auto const foodSprite = buildCircle((getPosition()).toVec2d(), 5, sf::Color::Green);
    if (isDebugOn()) //if debug on you can see the quantity of pheromones
    {
        auto const text = buildText(to_nice_string(quantity), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black);
        target.draw(text); //shows quantity via a text
    }
}

bool Pheromone::isNegligeable()
{
    return quantity<getAppConfig().pheromone_threshold;
}
