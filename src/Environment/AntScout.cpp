#include "AntScout.hpp"
#include "../Utility/Constants.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

int AntScout::count = 0;

int AntScout::getCount()
{
    return count;
}

AntScout::AntScout()
    :AntScout(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2), DEFAULT_UID)
{
    //Done
}

AntScout::~AntScout()
{
    --count;
    target = nullptr;
}

AntScout::AntScout(const ToricPosition& TP, Uid uid)
    :Ant::Ant(TP, ANT_SCOUT_HP, ANT_SCOUT_LIFE, uid),
      target(nullptr),
      targetPosition(getAppConfig().world_size/2,getAppConfig().world_size/2)
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
                       DEFAULT_ANT_SIZE,
                       getAppTexture(getAppConfig().ant_soldier_texture), ///////// <<<<<<<<<< probleme
                       getDirection()/DEG_TO_RAD);
}

int AntScout::getStrength() const
{
    return ANT_SCOUT_STRENGTH;
}

bool AntScout::foundTarget() const
{
    return (target != nullptr);
}

void AntScout::saveTargetInfo(Anthill *victim)
{
    target = victim;
    targetPosition = victim->getPosition();
}

/*void AntScout::update(sf::Time dt)
{
    AntKamikaze* closestKamikaze (getAppEnv().getClosestKamikazeForScout(this));
    Anthill* closestAnthill(getAppEnv().getClosestAnthillForAnt(this));
    if (not foundTarget())
    {
        if ((closestAnthill != nullptr and closestAnthill->getUid() != getAnthillUid()))
        {
            saveTargetInfo(closestAnthill);
            turnAround();
        }
    }
    else
    {
        if (closestKamikaze != nullptr and not closestKamikaze->isEnemy(this))
        {
            closestKamikaze->receiveTargetInformation(target,targetPosition);
            target = nullptr;
        }
    }
    Animal::update(dt);
}*/

