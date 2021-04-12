#include "AntWorker.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"


AntWorker::AntWorker(const Vec2d& pos, Uid id)
    :Ant::Ant(pos, getAppConfig().ant_worker_hp, getAppConfig().ant_worker_lifespan, id), carriedFood(0.0)
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
        setDirection(getDirection()+PI); //adds PI in radians to the direction angle
}

void AntWorker::update(sf::Time dt)
{
    Animal::update(dt); //###NE FAIT PAS CRASHER


//##########################
    /*if ( (getAppEnv().getClosestFoodForAnt(getPosition()) != nullptr)  and (carriedFood == 0.0) )
    {
        carriedFood += getAppEnv().getClosestFoodForAnt(getPosition())->takeQuantity(getAppConfig().ant_max_food);
        //if the ant can see a food close to itself and if the ant doesn't carry anything...
        //...then the ant takes a quantity ant_max_food from the food
    }*/
//##########################


    //### NE FAIT PAS CRASHER:
    if ( (getAppEnv().getAnthillForAnt(getPosition(),anthillID) == nullptr) and (carriedFood != 0.0) )
    {
        turnAround();
        //once it carries food, if the ant doesn't see it's anthill, it will turn around
    }

    //### NE FAIT PAS CRASHER:
    if (getAppEnv().getAnthillForAnt(getPosition(),anthillID) != nullptr)
    {
        getAppEnv().getAnthillForAnt(getPosition(),anthillID)->receiveFood(carriedFood);
        carriedFood = 0.0;
        //if the ant can see the anthill and the position of the ant is the same as the anthill
        //then it drops its carried food to the anthill
    }

}
