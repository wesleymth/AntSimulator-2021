#include "Animal.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "Random/Random.hpp"

double Animal::getSpeed() const
{
    return getAppConfig().animal_default_speed;
}

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
    bool res(false); //assumes to begin with that the animal isn't dead
    if ( (lifetime <= 0) or (lifePoints <= 0) )
    {
        res = true;
    }
    return res;
}

void Animal::drawOn(sf::RenderTarget& target) const
{
    auto const animalSprite = buildSprite((getPosition()).toVec2d(), (lifePoints*20), getAppTexture(getAppConfig().animal_default_texture), directionAngle/DEG_TO_RAD);
        target.draw(animalSprite);
    if (isDebugOn()) //if debug on you can see the lifePoints
    {
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
            line[0] = { getPosition().toVec2d(), sf::Color::Black };
            line[1] = { getPosition().toVec2d()+200*Vec2d::fromAngle(directionAngle), sf::Color::Black };
            target.draw(line);  //draws line
        auto const text = buildText(to_nice_string(lifePoints), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black);
        target.draw(text); //shows lifePoints via a text
    }
}

Animal::Animal(const Vec2d& pos, double LP, double LT)
    :Positionable(pos), directionAngle(uniform(0.0, TAU)), lifePoints(LP), lifetime(LT), timeLastRot(sf::Time::Zero)
{
    //Done
}

Animal::Animal()
    :Positionable(), directionAngle(uniform(0.0, TAU)), lifePoints(1.0), lifetime(1.0), timeLastRot(sf::Time::Zero)
{
    //Done
}

void Animal::move(sf::Time dt)
{
    auto dx = (getSpeed()*Vec2d::fromAngle(directionAngle)) * dt.asSeconds();
    setPosition(getPosition().toVec2d() + dx); //makes animal move by dx
    --lifetime;
    timeLastRot += dt;

    if (timeLastRot >= sf::seconds(getAppConfig().animal_next_rotation_delay))
    {
        timeLastRot=sf::Time::Zero; //resets timeLastRot to 0
        RotationProbs degProb(computeRotationProbs()); //gets rotation probabilities
        std::piecewise_linear_distribution<> dist(degProb.first.begin(), degProb.first.end(), degProb.second.begin());
        //declares a random generator which generates a random value using a linear distribution by pieces depending
        //on the vales of the set degProb
        directionAngle += dist(getRandomGenerator())*DEG_TO_RAD; //changes directionAngle
    }

}

RotationProbs Animal::computeRotationProbs()
{
    RotationProbs ret;
    ret.first={ -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180};
    ret.second={0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000};
    return ret;
}
