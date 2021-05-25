#include "InformationPheromone.hpp"
#include "../Application.hpp"
#include "../Utility/Constants.hpp"
#include "./Utility/Utility.hpp"

InformationPheromone::InformationPheromone()
    :InformationPheromone(ToricPosition(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2)),
                          DEFAULT_PHEROMONE_QUANTITY,
                          DEFAULT_UID,
                          nullptr,
                          ToricPosition(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2)))
{
    //Done
}

InformationPheromone::InformationPheromone(const Vec2d& vect, Quantity quant, Uid antUid, Anthill* victim, const ToricPosition& victimPosition)
    :InformationPheromone(ToricPosition(vect),quant, antUid, victim, victimPosition)
{
    //Done
}

InformationPheromone::InformationPheromone( const ToricPosition& TP, Quantity quant, Uid antUid, Anthill* victim, const ToricPosition& victimPosition)
    :Pheromone(TP,quant), allowedReading(antUid), enemy(victim), enemyPosition(victimPosition)
{
    //Done
}

void InformationPheromone::update(sf::Time dt)
{
    evaporate(dt.asSeconds()*getAppConfig().pheromone_evaporation_rate/4);
}

void InformationPheromone::drawOn(sf::RenderTarget &target) const
{
    sf::Color couleur(sf::Color::Red);
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

Anthill* InformationPheromone::getEnemy() const
{
    return enemy;
}

ToricPosition InformationPheromone::getEnemeyPosition() const
{
    return enemyPosition;
}

Uid InformationPheromone::getAllowedReading() const
{
    return allowedReading;
}
