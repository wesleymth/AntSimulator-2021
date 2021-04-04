#include "AntWorker.hpp"
#include "../Application.hpp"


AntWorker::AntWorker(const Vec2d& pos, Uid id)
    :Ant::Ant(pos, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan, id)
{
    //Done
}

AntWorker::AntWorker()
    :AntWorker(Vec2d(), Uid())
{
    //Done
}
