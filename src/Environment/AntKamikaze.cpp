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
      condition(Wander)
{
    ++count;
}

AntKamikaze::AntKamikaze(const ToricPosition& TP, Uid uid, Anthill* enemy, const ToricPosition& enemyPosition)
    :Ant::Ant(TP, ANT_KAMAIKAZE_HP, ANT_KAMAIKAZE_LIFE, uid),
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
                       DEFAULT_ANT_SIZE,
                       getAppTexture(ANT_KAMAIKAZE_SPRITE),
                       getDirection()/DEG_TO_RAD);
}

int AntKamikaze::getStrength() const
{
    return ANT_KAMAIKAZE_STRENGTH;
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
    return (toricDistance(getPosition(), target->getPosition()) <= getAppConfig().ant_max_perception_distance);
}

void AntKamikaze::receiveTargetInformation(Anthill* anthill, const ToricPosition& position)
{
    target = anthill; //gets the target
    targetPosition = position; //it's position
    setDirection(calculateAngle(Positionable(targetPosition))); //clalculates the angle it has to follow to go straigth towrds it
    condition = KillTarget; //changes its condition so that the update can manage it differently

}

void AntKamikaze::explode(Anthill *victim)
{
    victim->receiveDamage(ANT_KAMAIKAZE_BLOW_UP_DAMAGE);
    kill();
}

void AntKamikaze::update(sf::Time dt)
{
    //std::cerr << getPosition() << std::endl;
    if (condition == KillTarget)
    {
        if (targetInPerceptionDistance())
        {
            if(getAppEnv().anthi)
            {
                explode(target);
            }
            else
            {
                condition = Wander;
            }
        }
    }
    else //if wandering
    {
        Anthill* closestAnthill(getAppEnv().getClosestAnthillForAnt(this));
        if (getAppEnv().getPheromoneInfo(this))
        {
            condition = KillTarget;
        }

        if(closestAnthill != nullptr)
        {
            if((closestAnthill->getUid() != getAnthillUid()) and(not closestAnthill->isDead()))
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
    if (isDebugOn())
    {
        if (condition == KillTarget)
        {
            auto const targetText = buildText("TARGET UID: " + to_nice_string(target->getUid()), getPosition().toVec2d()+Vec2d(0,40), getAppFont(), 15, sf::Color::Red);
            Target.draw(targetText);
            auto const targetPos = buildText("TARGET POS ("+ to_nice_string(targetPosition.x()) +"," + to_nice_string(targetPosition.y()) + ")",
                                              getPosition().toVec2d()+Vec2d(0,60), getAppFont(), 15, sf::Color::Magenta);
            Target.draw(targetPos); //shows target anthill's uid via a text
        }
    }
}

