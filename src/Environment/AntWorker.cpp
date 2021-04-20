#include "AntWorker.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

AntWorker::AntWorker()
{
    //Done
}

AntWorker::AntWorker(const ToricPosition& TP, Uid uid)
    :Ant::Ant(TP, getAppConfig().ant_worker_hp, getAppConfig().ant_worker_lifespan, uid), carriedFood(0.0)
{
    //Done
}

AntWorker::AntWorker(const Vec2d& pos, Uid id)
    :AntWorker(ToricPosition(pos),id)
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

double AntWorker::getStrength() const
{
    return getAppConfig().ant_worker_strength;
}

void AntWorker::turnAround()
{
        setDirection(getDirection()+PI); //adds PI in radians to the direction angle
}

void AntWorker::update(sf::Time dt)
{
    Animal::update(dt);

    Food* closestFood(getAppEnv().getClosestFoodForAnt(getPosition()));
    if ( ( closestFood != nullptr) and (carriedFood == 0.0) )
    {
        carriedFood += closestFood->takeQuantity(getAppConfig().ant_max_food);
        //if the ant can see a food close to itself and if the ant doesn't carry anything then the ant takes a quantity ant_max_food from the food
        if (getAppEnv().getAnthillForAnt(getPosition(),getAnthillUid()) == nullptr)
        {
            turnAround(); //once it carries food, if the ant doesn't see it's anthill, it will turn around
        }
    }

    if (getAppEnv().getAnthillForAnt(getPosition(),getAnthillUid()) != nullptr)
    {
        getAppEnv().getAnthillForAnt(getPosition(),getAnthillUid())->receiveFood(carriedFood);
        carriedFood = 0.0;
        //if the ant can see the anthill and the position of the ant is the same as the anthill then it drops its carried food to the anthill
    }

}

void AntWorker::drawOn(sf::RenderTarget& target) const
{
    Ant::drawOn(target);
    if (isDebugOn()) //if debug on you can see the current foodStock in black and the uid in magenta
    {
        auto const carriedFoodText = buildText(to_nice_string(carriedFood), getPosition().toVec2d()+Vec2d(0,20), getAppFont(), 15, sf::Color::Black);
        target.draw(carriedFoodText); //shows quantity of carried food via a text

        auto const uidText = buildText(to_nice_string(getAnthillUid()), getPosition().toVec2d()+Vec2d(0,40), getAppFont(), 15, sf::Color::Magenta);
        target.draw(uidText); //shows anthill uid via a text


        target.draw(buildAnnulus(getPosition().toVec2d(), getAppConfig().ant_smell_max_distance, sf::Color::Blue, 5)); //draws a ring around animal representing the perception distance
    }
}
