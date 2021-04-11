#include "AntWorker.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"


AntWorker::AntWorker(const Vec2d& pos, Uid id)
    :Ant::Ant(pos, getAppConfig().ant_worker_hp, getAppConfig().ant_worker_lifespan, id), carriedFood(0)
{
    //Done
}

AntWorker::AntWorker()
    :AntWorker(Vec2d(), Uid())
{
    //Done
}

sf::Sprite AntWorker::getSprite() const
{
    return buildSprite((getPosition()).toVec2d(),
                       DEFAULT_ANT_SIZE,
                       getAppTexture(getAppConfig().ant_worker_texture),
                       getDirection()/DEG_TO_RAD);
}

void AntWorker::turnAround()
{
    if (getAppEnv().getAnthillForAnt(getPosition(),anthillID) == nullptr)
    {
        setDirection(getDirection()+PI); //adds PI in radians to the direction angle
    }
}

void AntWorker::update(sf::Time dt)
{
    Animal::update(dt);
    turnAround();


}
