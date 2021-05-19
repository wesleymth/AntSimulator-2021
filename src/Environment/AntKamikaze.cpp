#include "AntKamikaze.hpp"
#include "../Utility/Constants.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

int AntKamikaze::count = 0;

AntKamikaze::AntKamikaze()
    :AntKamikaze(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2), DEFAULT_UID)
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
      targetAngle(),
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
                       getAppTexture(getAppConfig().ant_soldier_texture), ///////// <<<<<<<<<< probleme
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
        auto dx = (getSpeed()*Vec2d::fromAngle(targetAngle)) * dt.asSeconds();
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
    target = anthill;
    targetPosition = position;
    targetAngle = calculateAngle(Positionable(targetPosition));
    condition = KillTarget;
}

void AntKamikaze::explode()
{
    target->takeDamage(ANT_KAMAIKAZE_BLOW_UP_DAMAGE);
    receiveDamage(getHP());
}

void AntKamikaze::update(sf::Time dt)
{
    if ((condition == KillTarget) and (targetInPerceptionDistance()))
    {
        if(getAppEnv().anthillStillAlive(target))
        {
            explode();
        }
        else
        {
            target = nullptr;
            condition = Wander;
        }
    }
    Animal::update(dt);
}
