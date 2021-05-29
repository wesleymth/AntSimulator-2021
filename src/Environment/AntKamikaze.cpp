/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#include "AntKamikaze.hpp"
#include "../Utility/Constants.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

int AntKamikaze::count = 0;

int AntKamikaze::getCount()
{
    return count;
}

AntKamikaze::AntKamikaze()
    :AntKamikaze(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2), getAppConfig().DEFAULT_UID) //sets position to middle of the world
{
    //Done
}

AntKamikaze::~AntKamikaze()
{
    --count;
    target = nullptr;
}

AntKamikaze::AntKamikaze(const ToricPosition& TP, Uid uid)
    :Ant::Ant(TP, getAppConfig().ANT_KAMAIKAZE_HP, getAppConfig().ANT_KAMAIKAZE_LIFE, uid),
      target(nullptr),
      targetPosition(getAppConfig().world_size/2,getAppConfig().world_size/2),
      condition(Wander)
{
    ++count;
}

AntKamikaze::AntKamikaze(const ToricPosition& TP, Uid uid, Anthill* enemy, const ToricPosition& enemyPosition)
    :Ant::Ant(TP, getAppConfig().ANT_KAMAIKAZE_HP, getAppConfig().ANT_KAMAIKAZE_LIFE, uid),
      target(enemy),
      targetPosition(enemyPosition),
      condition(KillTarget)
{
    setDirection(calculateAngle(Positionable(targetPosition)));
}

AntKamikaze::AntKamikaze(const Vec2d& pos, Uid uid)
    :AntKamikaze(ToricPosition(pos),uid)
{
    //Done
}

sf::Sprite AntKamikaze::getSprite() const
{
    return buildSprite((getPosition()).toVec2d(),
                       getAppConfig().DEFAULT_ANT_SIZE,
                       getAppTexture(getAppConfig().ANT_KAMAIKAZE_SPRITE),
                       getDirection()/DEG_TO_RAD);
}

int AntKamikaze::getStrength() const
{
    return getAppConfig().ANT_KAMAIKAZE_STRENGTH;
}

Anthill* AntKamikaze::getTarget() const
{
    return target;
}

bool AntKamikaze::foundTarget() const
{
    return (target != nullptr);
}

void AntKamikaze::move(sf::Time dt)
{
    if (condition == KillTarget)
    {
        auto dx = (getSpeed()*Vec2d::fromAngle(getDirection()) * dt.asSeconds()); //targetAngle doesn't change
        setPosition(getPosition().toVec2d() + dx); //makes animal move by dx
        spreadPheromones();
    }
    else
    {
        Ant::move(dt);
    }
}

bool AntKamikaze::targetInPerceptionDistance() const
{
    return (toricDistance(getPosition(), targetPosition) <= getAppConfig().ant_max_perception_distance);
}

void AntKamikaze::receiveTargetInformation(Anthill* anthill, const ToricPosition& position)
{
    target = anthill; //gets the target
    targetPosition = position; //it's position
    setDirection(calculateAngle(Positionable(targetPosition))); //clalculates the angle it has to follow to go straigth towards it
    condition = KillTarget; //changes its condition so that the update can manage it differently

}

void AntKamikaze::explode(Anthill *victim)
{
    victim->receiveDamage(getAppConfig().ANT_KAMAIKAZE_BLOW_UP_DAMAGE);
    kill();
}

void AntKamikaze::update(sf::Time dt)
{
    //std::cerr << getPosition() << std::endl;
    if (condition == KillTarget)
    {
        if (targetInPerceptionDistance())
        {
            if(getAppEnv().anthillStillAlive(target))
            {
                explode(target); //inflicts explosion damage upon target
            }
            else
            {
                condition = Wander; //once it is at the reported target's position, if it is dead it goes back to wandering
            }
        }
    }
    else //if wandering
    {
        Anthill* closestAnthill(getAppEnv().getClosestAnthillForAnt(this));
        if (getAppEnv().getPheromoneInfo(this)) //if it can take information from the information pheromone
        {
            condition = KillTarget;
        }

        if(closestAnthill != nullptr)
        {
            if(closestAnthill->getUid() != getAnthillUid())
            {
                explode(closestAnthill); //if it stumbles upon an anthill it will explode on it
            }
        }
    }
    Animal::update(dt);

}

void AntKamikaze::drawOn(sf::RenderTarget& Target) const
{
    Ant::drawOn(Target);
    if (isDebugOn())
    {
        if (condition == KillTarget) //shows target's uid
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
}

