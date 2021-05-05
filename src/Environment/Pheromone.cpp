/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#include "Pheromone.hpp"
#include "./Application.hpp"
#include "./Utility/Utility.hpp"

Pheromone::Pheromone()
    :Pheromone(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2), DEFAULT_PHEROMONE_QUANTITY)
{
    //Done
}

Pheromone::Pheromone(const Vec2d& vect, Quantity quant)
    :Pheromone(ToricPosition(vect), quant)
{
    //Done
}

Pheromone::Pheromone( const ToricPosition& TP, Quantity quant)
    :Positionable(TP), quantity(quant)
{
//Done
}

void Pheromone::update(sf::Time dt)
{
    quantity-=dt.asSeconds()*getAppConfig().pheromone_evaporation_rate;
}

void Pheromone::drawOn(sf::RenderTarget &target) const
{
    sf::Color couleur(sf::Color::Green);
    couleur.a=couleur.a/4;
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

bool Pheromone::isNegligeable() const
{
    return quantity<getAppConfig().pheromone_threshold;
}

Quantity Pheromone::getQuantity() const
{
    return quantity;
}
