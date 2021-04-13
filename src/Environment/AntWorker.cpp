#include "AntWorker.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"


AntWorker::AntWorker(const Vec2d& pos, Uid id)
    :Ant::Ant(pos, getAppConfig().ant_worker_hp, getAppConfig().ant_worker_lifespan, id), carriedFood(0.0)
{
    //Done
}

AntWorker::AntWorker(const ToricPosition& pos, Uid id)
    :AntWorker(pos.toVec2d(),id)
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
    if ( (getAppEnv().getClosestFoodForAnt(getPosition()) != nullptr) and (carriedFood == 0.0) )
    {
        carriedFood += getAppEnv().getClosestFoodForAnt(getPosition())->takeQuantity(getAppConfig().ant_max_food); //###### PEUT FAIRE CRASHER
        //if the ant can see a food close to itself and if the ant doesn't carry anything...
        //...then the ant takes a quantity ant_max_food from the food
        if (getAppEnv().getAnthillForAnt(getPosition(),anthillID) == nullptr)
        {
            turnAround();
            //once it carries food, if the ant doesn't see it's anthill, it will turn around
        }
    }
//##########################


    //### NE FAIT PAS CRASHER


    //### NE FAIT PAS CRASHER
    if (getAppEnv().getAnthillForAnt(getPosition(),anthillID) != nullptr)
    {
        getAppEnv().getAnthillForAnt(getPosition(),anthillID)->receiveFood(carriedFood);
        carriedFood = 0.0;
        //if the ant can see the anthill and the position of the ant is the same as the anthill
        //then it drops its carried food to the anthill
    }

}

void AntWorker::drawOn(sf::RenderTarget& target) const
{
    Ant::drawOn(target);
    if (isDebugOn()) //if debug on you can see the current foodStock in black and the uid in magenta
    {
        auto const food = buildText(to_nice_string(carriedFood), getPosition().toVec2d()+Vec2d(0,20), getAppFont(), 15, sf::Color::Black);
        target.draw(food); //shows quantity of carried food via a text

        auto const id = buildText(to_nice_string(anthillID), getPosition().toVec2d()+Vec2d(0,40), getAppFont(), 15, sf::Color::Magenta);
        target.draw(id); //shows anthill uid via a text
    }
}
