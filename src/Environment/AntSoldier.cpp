/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#include "AntSoldier.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

int AntSoldier::count = 0;

int AntSoldier::getCount()
{
    return count;
}

AntSoldier::AntSoldier()
    :AntSoldier(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2), DEFAULT_UID)
{
    //Done
}

AntSoldier::~AntSoldier()
{
    --count;
}

AntSoldier::AntSoldier(const ToricPosition& TP, Uid uid)
    :Ant::Ant(TP, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan, uid)
{
    ++count;
}

AntSoldier::AntSoldier(const ToricPosition& TP, Uid uid, Angle notRandomAngle)
    :AntSoldier(TP,uid)
{
    setDirection(notRandomAngle);
}

AntSoldier::AntSoldier(const Vec2d& pos, Uid uid)
    :AntSoldier(ToricPosition(pos),uid)
{
    //Done
}

sf::Sprite AntSoldier::getSprite() const
{
    return buildSprite((getPosition()).toVec2d(),
                       DEFAULT_ANT_SIZE,
                       getAppTexture(getAppConfig().ant_soldier_texture),
                       getDirection()/DEG_TO_RAD);
}

int AntSoldier::getStrength() const
{
    return getAppConfig().ant_soldier_strength;
}
