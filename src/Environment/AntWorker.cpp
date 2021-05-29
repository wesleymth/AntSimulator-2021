/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#include "AntWorker.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "Random/Random.hpp"

int AntWorker::count = 0;

int AntWorker::getCount()
{
    return count;
}

AntWorker::AntWorker()
    :AntWorker(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2), getAppConfig().DEFAULT_UID)
{
    //Done
}

AntWorker::~AntWorker()
{
    --count;
}

AntWorker::AntWorker(const ToricPosition& TP, Uid uid)
    :Ant::Ant(TP, getAppConfig().ant_worker_hp, getAppConfig().ant_worker_lifespan, uid), carriedFood(0.0)
{
    ++count;
}

AntWorker::AntWorker(const Vec2d& pos, Uid id)
    :AntWorker(ToricPosition(pos),id)
{
    //Done
}

sf::Sprite AntWorker::getSprite() const
{
    return buildSprite((getPosition()).toVec2d(),
                       getAppConfig().DEFAULT_ANT_SIZE,
                       getAppTexture(getAppConfig().ant_worker_texture),
                       getDirection()/DEG_TO_RAD);
}

int AntWorker::getStrength() const
{
    return getAppConfig().ant_worker_strength;
}

void AntWorker::update(sf::Time dt)
{
    Animal::update(dt);

    Food* closestFood(getAppEnv().getClosestFoodForAnt(getPosition()));
    if ( ( closestFood != nullptr) and (carriedFood == 0.0) )
    {
        Quantity taken(closestFood->takeQuantity(getAppConfig().ant_max_food));
        carriedFood += taken;
        //if the ant can see a food close to itself and if the ant doesn't carry anything then the ant takes a quantity ant_max_food from the food
        if (getAppEnv().getAnthillForAnt(getPosition(),getAnthillUid()) == nullptr)
        {
            turnAround(); //once it carries food, if the ant doesn't see it's anthill, it will turn around
        }
    }

    if (getAppEnv().getAnthillForAnt(getPosition(),getAnthillUid()) != nullptr and carriedFood != 0.0)
    {
        getAppEnv().getAnthillForAnt(getPosition(),getAnthillUid())->receiveFood(carriedFood);
        carriedFood = 0.0;
        turnAround();
        //if the ant can see the anthill and the position of the ant is the same as the anthill then it drops its carried food to the anthill and tries to go back
    }

}

void AntWorker::drawOn(sf::RenderTarget& target) const
{
    Ant::drawOn(target);
    if (isDebugOn())
    { //if debug on you can see the current foodStock in black
        auto const carriedFoodText = buildText(to_nice_string(carriedFood), getPosition().toVec2d()+Vec2d(0,40), getAppFont(), 15, sf::Color::Black);
        target.draw(carriedFoodText); //shows quantity of carried food via a text
    }
}
