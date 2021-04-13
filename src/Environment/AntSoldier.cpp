#include "AntSoldier.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

AntSoldier::AntSoldier()
{
    //Done
}

AntSoldier::AntSoldier(const Vec2d& pos, Uid uid)
    :Ant::Ant(pos, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan, uid)
{
    //Done
}

AntSoldier::AntSoldier(const ToricPosition& TP, Uid uid)
    :AntSoldier(TP.toVec2d(),uid)
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
