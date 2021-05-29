/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#include "InformationPheromone.hpp"
#include "../Application.hpp"
#include "../Utility/Constants.hpp"
#include "./Utility/Utility.hpp"

InformationPheromone::InformationPheromone()
    :InformationPheromone(ToricPosition(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2)),
                          getAppConfig().DEFAULT_PHEROMONE_QUANTITY,
                          getAppConfig().DEFAULT_UID,
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

    if (isDebugOn()) //if debug on you can see the target's uid
    {
        if(getAppEnv().anthillStillAlive(enemy))
        {
            auto const targetText = buildText(to_nice_string(enemy->getUid()), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Red);
            target.draw(targetText);
        }
        else
        {
            auto const targetText = buildText("DEAD", getPosition().toVec2d(), getAppFont(), 5, sf::Color::Red);
            target.draw(targetText);
        }
    }

}

Anthill* InformationPheromone::getEnemy() const
{
    return enemy;
}

ToricPosition InformationPheromone::getEnemyPosition() const
{
    return enemyPosition;
}

Uid InformationPheromone::getAllowedReading() const
{
    return allowedReading;
}

bool InformationPheromone::interact() const
{
    return true;
}
