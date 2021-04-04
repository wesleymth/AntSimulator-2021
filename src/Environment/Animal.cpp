#include "Animal.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "Random/Random.hpp"

Angle Animal::getDirection() const
{
    return directionAngle;
}

void Animal::setDirection(Angle setAngle)
{
    directionAngle = setAngle;  //###################### do we need to check if taken between 0 and TAU??
}

bool Animal::isDead() const
{
    bool res(false); //assumes to begin with that the animal isn't dead
    if ( (lifetime <= 0) or (healthPoints <= 0) )
    {
        res = true;
    }
    return res;
}

Animal::Animal(const Vec2d& pos, double HP, double LT)
    :Positionable(pos), directionAngle(uniform(0.0, TAU)), healthPoints(HP), lifetime(LT), timeLastRot(sf::Time::Zero)
{
    //Done
}

Animal::Animal(const Vec2d& pos)
    :Animal(pos, 1.0, 1.0) // calls different constructor
{
    //Done
}

Animal::Animal()
    :Animal(Vec2d(), 1.0, 1.0) //calls different constructor
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
        //on the values of the set degProb, the rotation probabilities
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
