#include "Animal.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "Random/Random.hpp"

double Animal::getSpeed() const
{
    return getAppConfig().animal_default_speed;
}

//[Question Q2.7] BESOIN DETRE REPONDU

Angle Animal::getDirection() const
{
    return directionAngle;
}

void Animal::setDirection(Angle setAngle)
{
    directionAngle = setAngle;
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
    auto const animalSprite = buildSprite((getPosition()).toVec2d(), (lifePoints*20), getAppTexture(getAppConfig().animal_default_texture));
        target.draw(animalSprite);
    if (isDebugOn()) //if debug on you can see the lifePoints
    {
        sf::VertexArray ligne(sf::PrimitiveType::Lines, 2);
            ligne[0] = { getPosition().toVec2d(), sf::Color::Black };
            ligne[1] = { getPosition().toVec2d()+200*Vec2d::fromAngle(directionAngle), sf::Color::Black };
            target.draw(ligne);  //draws line
        auto const text = buildText(to_nice_string(lifePoints), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black);
        target.draw(text); //shows lifePoints via a text
    }
}

Animal::Animal(const Vec2d& pos, double LP, double LT)
    :Positionable(pos), directionAngle(uniform(0.0, TAU)), lifePoints(LP), lifetime(LT)
{
    //Done
}

Animal::Animal()
    :Positionable(), directionAngle(uniform(0.0, TAU)), lifePoints(1.0), lifetime(1.0)
{
    //Done
}

//[Question Q2.8] BESOIN DETRE REPONDU

//[Question Q2.9] BESOIN DETRE REPONDU

void Animal::move(sf::Time dt)
{
    auto dx = (getSpeed()*Vec2d::fromAngle(directionAngle)) * dt.asSeconds();
    Vec2d res;
    setPosition(getPosition().toVec2d() + dx);
    --lifetime;
}
