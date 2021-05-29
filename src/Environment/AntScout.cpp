#include "AntScout.hpp"
#include "../Utility/Constants.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "InformationPheromone.hpp"
#include "RegularPheromone.hpp"

int AntScout::count = 0;

int AntScout::getCount()
{
    return count;
}

AntScout::AntScout()
    :AntScout(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2), getAppConfig().DEFAULT_UID)
{
    //Done
}

AntScout::~AntScout()
{
    --count;
    target = nullptr;
}

AntScout::AntScout(const ToricPosition& TP, Uid uid)
    :Ant::Ant(TP, getAppConfig().ANT_SCOUT_HP, getAppConfig().ANT_SCOUT_LIFE, uid),
      target(nullptr),
      targetPosition(getAppConfig().world_size/2,getAppConfig().world_size/2),
      condition(Roam),
      timeSpreadInpho(sf::Time::Zero)
{
    ++count;
}

AntScout::AntScout(const Vec2d& pos, Uid uid)
    :AntScout(ToricPosition(pos),uid)
{
    //Done
}

sf::Sprite AntScout::getSprite() const
{
    return buildSprite((getPosition()).toVec2d(),
                       getAppConfig().DEFAULT_ANT_SIZE,
                       getAppTexture(getAppConfig().ANT_SCOUT_SPRITE),
                       getDirection()/DEG_TO_RAD);
}

int AntScout::getStrength() const
{
    return getAppConfig().ANT_SCOUT_STRENGTH;
}

bool AntScout::foundTarget() const
{
    return (target != nullptr);
}

bool AntScout::roaming() const
{
    return (condition == Roam);
}

void AntScout::saveTargetInfo(Anthill *victim)
{
    target = victim;
    targetPosition = victim->getPosition();
}

void AntScout::update(sf::Time dt)
{
    Anthill* closestAnthill(getAppEnv().getClosestAnthillForAnt(this));
    if (roaming())
    {
        if ((closestAnthill != nullptr and closestAnthill->getUid() != getAnthillUid()))
        {
            saveTargetInfo(closestAnthill);
            turnAround();
            timeSpreadInpho = sf::seconds(getAppConfig().ANT_SCOUT_SPREAD_INPHO_TIME); //spreads information pheromones for kamikaze
            condition = TargetAcquiered;
        }
    }
    else //if target has been acquired
    {
        if (timeSpreadInpho > sf::Time::Zero)
        {
            timeSpreadInpho -= dt;
        }
        else
        {
            condition = Roam;
        }

        if (closestAnthill != nullptr and closestAnthill->getUid() == getAnthillUid()
                and toricDistance(closestAnthill->getPosition(),targetPosition) <= getAppConfig().DEFAULT_ANTHILL_TERRITORY)
            //if it goes back to it's anthill having just discovered an enemy, within its territory
        {
            closestAnthill->receiveEnemyInfo(target,targetPosition); //it gives all information needed to start a war
        }
    }
    Animal::update(dt); //updates the animal to be able to fight normally
}

void AntScout::spreadPheromones()
{
    double dist(toricDistance(getPosition(),getLastPheromone()));
    Vec2d vect(getLastPheromone().toricVector(getPosition()));
    if(dist*getAppConfig().ant_pheromone_density>=1) {
        for(int i(1); i<=dist*getAppConfig().ant_pheromone_density; ++i) {
            setLastPheromone(getLastPheromone()+(i*vect/(dist*getAppConfig().ant_pheromone_density)));
            if (roaming())
            {
                getAppEnv().addPheromone(new RegularPheromone(getLastPheromone(),
                                    getAppConfig().ant_pheromone_energy));
            }
            else
            {
                getAppEnv().addPheromone(new InformationPheromone(getLastPheromone(),
                                                                  getAppConfig().ant_pheromone_energy,
                                                                  getAnthillUid(),
                                                                  target,
                                                                  targetPosition));
                //if it has a target in mind it drops behing special pheromones with enemy information in them for kamikazes to pick up on
            }

        }
    }


}

void AntScout::drawOn(sf::RenderTarget& Target) const
{
    Ant::drawOn(Target);
    if (isDebugOn() and foundTarget())
    {
        if(getAppEnv().anthillStillAlive(target))
        {
            auto const targetText = buildText("TARGET: " + to_nice_string(target->getUid()), getPosition().toVec2d()+Vec2d(0,40), getAppFont(), 15, sf::Color::Red);
            Target.draw(targetText);
        }
        else //if the target is dead but it does'nt know it yet
        {
            auto const targetText = buildText("TARGET: DEAD", getPosition().toVec2d()+Vec2d(0,40), getAppFont(), 15, sf::Color::Red);
            Target.draw(targetText);
        }
    }
}

