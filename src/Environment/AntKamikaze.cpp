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
    :AntKamikaze(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2), DEFAULT_UID) //sets position to middle of the world
{
    //Done
}

AntKamikaze::~AntKamikaze()
{
    --count;
    target = nullptr;
}

AntKamikaze::AntKamikaze(const ToricPosition& TP, Uid uid)
    :Ant::Ant(TP, ANT_KAMAIKAZE_HP, ANT_KAMAIKAZE_LIFE, uid),
      target(nullptr),
      targetPosition(getAppConfig().world_size/2,getAppConfig().world_size/2),
      targetAngle(0),
      condition(Wander)
{
    ++count;
}

AntKamikaze::AntKamikaze(const Vec2d& pos, Uid uid)
    :AntKamikaze(ToricPosition(pos),uid)
{
    //Done
}

sf::Sprite AntKamikaze::getSprite() const
{
    return buildSprite((getPosition()).toVec2d(),
                       DEFAULT_ANT_SIZE,
                       getAppTexture(ANT_KAMAIKAZE_SPRITE), ///////// <<<<<<<<<< probleme
                       getDirection()/DEG_TO_RAD);
}

int AntKamikaze::getStrength() const
{
    return ANT_KAMAIKAZE_STRENGTH;
}

bool AntKamikaze::foundTarget() const
{
    return (target != nullptr);
}

void AntKamikaze::move(sf::Time dt)
{
    if (condition == KillTarget)
    {
        auto dx = (getSpeed()*Vec2d::fromAngle(targetAngle)) * dt.asSeconds(); //targetAngle doesn't change
        setPosition(getPosition().toVec2d() + dx); //makes animal move by dx
    }
    else
    {
        Animal::move(dt);
    }
}

bool AntKamikaze::targetInPerceptionDistance() const
{
    return (toricDistance(getPosition(), target->getPosition()) <= getAppConfig().ant_max_perception_distance);
}

void AntKamikaze::receiveTargetInformation(Anthill* anthill, const ToricPosition& position)
{
    target = anthill; //gets the target
    targetPosition = position; //it's position
    targetAngle = calculateAngle(Positionable(targetPosition)); //clalculates the angle it has to follow to go straigth towrds it
    condition = KillTarget; //changes its condition so that the update can manage it differently
}

void AntKamikaze::explode(Anthill *victim)
{
    victim->takeDamage(ANT_KAMAIKAZE_BLOW_UP_DAMAGE);
    receiveDamage(getHP());
}

void AntKamikaze::update(sf::Time dt)
{
    if ((condition == KillTarget) and (targetInPerceptionDistance()))
    {
        if(not target->isDead())
        {
            explode(target);
        }
        else
        {
            target = nullptr;
            condition = Wander;
        }
    }
    else
    {
        Anthill* closestAnthill(getAppEnv().getClosestAnthillForAnt(this));
        Pheromone* closestPheromone (getAppEnv().getClosestPheromoneForAnt(this));
        if (closestPheromone != nullptr)
        {
            if (interactWithPheromoneDispatch(closestPheromone))
            {
                condition = KillTarget;
            }
        }

        if(closestAnthill != nullptr)
        {
            if(closestAnthill->getUid() != getAnthillUid())
            {
                explode(closestAnthill);
            }
        }
    }
    Animal::update(dt);
}

void AntKamikaze::drawOn(sf::RenderTarget& Target) const
{
    Ant::drawOn(Target);
    if (isDebugOn() and foundTarget())
    { //if debug on and foundTarget true you can see the target's uid in red
        auto const targetText = buildText(to_nice_string(target->getUid()), getPosition().toVec2d()+Vec2d(0,20), getAppFont(), 15, sf::Color::Red);
        Target.draw(targetText);
    }
}

bool AntKamikaze::interactWithPheromoneDispatch(Pheromone const* other)
{
    return false;
}

bool AntKamikaze::interactWithPheromoneDispatch(InformationPheromone const* other)
{
    bool res(false);
    if(other->getAllowedReading() == getAnthillUid())
    {
        receiveTargetInformation(other->getEnemy(),other->getEnemeyPosition());
    }
    return res;
}
