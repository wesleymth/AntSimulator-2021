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
                       getAppTexture(ANT_KAMAIKAZE_SPRITE),
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
    targetAngle = calculateAngle(Positionable(targetPosition)); //clalculates the angle it has to follow to go straigth towrds it
    condition = KillTarget; //changes its condition so that the update can manage it differently
}

void AntKamikaze::explode(Anthill *victim)
{
    victim->receiveDamage(ANT_KAMAIKAZE_BLOW_UP_DAMAGE);
    kill();
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
        //Pheromone* closestPheromone (getAppEnv().getClosestPheromoneForAnt(this));
        if (getAppEnv().getClosestPheromoneForAnt(this) != nullptr)
        {
            if (interactWithPheromoneDispatch(getAppEnv().getClosestPheromoneForAnt(this)))
            {
                condition = KillTarget;
            }
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
        if (foundTarget())
        {
            auto const targetText = buildText("TARGET UID: " + to_nice_string(target->getUid()), getPosition().toVec2d()+Vec2d(0,20), getAppFont(), 15, sf::Color::Red);
            Target.draw(targetText);
        }
        auto const uidText = buildText(to_nice_string(getAnthillUid()), getPosition().toVec2d()+Vec2d(0,40), getAppFont(), 15, sf::Color::Magenta);
        Target.draw(uidText); //shows anthill uid via a text
        Target.draw(buildAnnulus(getPosition().toVec2d(), getAppConfig().ant_smell_max_distance, sf::Color::Blue, 5)); //draws a ring around animal representing the perception distance
        auto const targetPos = buildText("TARGET POS ("+ to_nice_string(targetPosition.x()) +"," + to_nice_string(targetPosition.y()) + ")",
                                          getPosition().toVec2d()+Vec2d(0,60), getAppFont(), 15, sf::Color::Magenta);
        Target.draw(targetPos); //shows anthill uid via a text
    }
     //if debug on you can see the uid in magenta
}

bool AntKamikaze::interactWithPheromoneDispatch(Pheromone const* other)
{
    return false;
}

bool AntKamikaze::interactWithPheromoneDispatch(InformationPheromone const* other)
{
    bool res(false);
    //if(other->getAllowedReading() == getAnthillUid())
    //{
        receiveTargetInformation(other->getEnemy(),other->getEnemeyPosition());
    //}
    return res;
}
