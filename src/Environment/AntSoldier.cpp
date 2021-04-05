#include "AntSoldier.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"


AntSoldier::AntSoldier(const Vec2d& pos, Uid id)
    :Ant::Ant(pos, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan, id)
{
    //Done
}

AntSoldier::AntSoldier()
    :AntSoldier(Vec2d(), Uid()) //calls constructor above using default Vec2d and default Uid
{
    //Done
}

sf::Sprite AntSoldier::getSprite() const
{
    return buildSprite((getPosition()).toVec2d(), (DEFAULT_ANT_SIZE), getAppTexture(getAppConfig().ant_soldier_texture), getDirection()/DEG_TO_RAD);
}
