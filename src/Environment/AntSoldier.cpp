#include "AntSoldier.hpp"
#include "../Application.hpp"


AntSoldier::AntSoldier(const Vec2d& pos, Uid id)
    :Ant::Ant(pos, getAppConfig().ant_worker_hp, getAppConfig().ant_worker_lifespan, id)
{
    //Done
}

AntSoldier::AntSoldier()
    :AntSoldier(Vec2d(), Uid()) //calls constructor above using default Vec2d and default Uid
{
    //Done
}
