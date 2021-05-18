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
    :Ant::Ant(TP, ANT_KAMAIKAZE_HP, ANT_KAMAIKAZE_LIFE, uid), target(nullptr), foundTarget(false)
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

void AntKamikaze::setTarget(Anthill*& anthill)
{
    target = anthill;
}

bool AntKamikaze::foundTarget() const
{
    return (target != nullptr);
}



void AntKamikaze::move(sf::Time dt)
{
    if (foundTarget())
    {

        //setDirection();
    }
    else
    {
        Animal::move(dt);
    }
}

