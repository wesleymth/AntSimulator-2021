#include "Animal.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

double Animal::getSpeed() const
{
    return getAppConfig().animal_default_speed;
}

//[Question Q2.7] BESOIN DETRE REPONDU

Angle Animal::getDirection() const
{
    return direction;
}

void Animal::setDirection(Angle setAngle)
{
    direction = setAngle;
}

bool Animal::isDead() const
{
    bool res(false);
    if ( (lifetime <= 0) or (lifePoints <= 0) )
    {
        res = true;
    }
    return res;
}

void Animal::drawOn(sf::RenderTarget& target) const
{
    auto const animalSprite = buildSprite((position.getPosition()).toVec2d(),
                                          (lifePoints*20),
                                          getAppTexture(getAppConfig().animal_default_texture));
        target.draw(animalSprite);
}

Animal::Animal(const Positionable& pos, double LP, double LT)
    :position(pos), lifePoints(LP), lifetime(LT)
{
    //Done
}

Animal::Animal(const Vec2d& pos, double LP, double LT)
    :position(Positionable(ToricPosition(pos))), lifePoints(LP), lifetime(LT)
{
    //Done
}

Animal::Animal()
    :position(), lifePoints(1.0), lifetime(1.0)
{
    //Done
}

//[Question Q2.8] BESOIN DETRE REPONDU

//[Question Q2.9] BESOIN DETRE REPONDU
