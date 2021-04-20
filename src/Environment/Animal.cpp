#include "Animal.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "Random/Random.hpp"

Animal::Animal()
    :Animal(Vec2d(getAppConfig().world_size/2, getAppConfig().world_size/2))
{
    //Done
}

Animal::Animal(const ToricPosition& TP, double HP, double LT)
    :Positionable(TP), dirAngle(uniform(0.0, TAU)), healthPoints(HP), lifetime(LT), timeLastRot(sf::Time::Zero), state(Idle)
{
    //Done
}

Animal::Animal(const Vec2d& pos, double HP, double LT)
    :Animal(ToricPosition(pos),HP,LT)
{
    //Done
}

Animal::Animal(const ToricPosition& TP)
    :Animal(TP, DEFAULT_ANIMAL_HP, DEFAULT_ANIMAL_LIFE)
{
    //Done
}

Animal::Animal(const Vec2d& pos)
    :Animal(ToricPosition(pos))
{
    //Done
}

Angle Animal::getDirection() const
{
    return dirAngle;
}

double Animal::getHP() const
{
    return healthPoints;
}

void Animal::setDirection(Angle setAngle)
{
    dirAngle = fmod(setAngle,TAU); //ensures that angle is between 0 and 2pi in rad
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

void Animal::move(sf::Time dt)
{
    auto dx = (getSpeed()*Vec2d::fromAngle(dirAngle)) * dt.asSeconds();
    setPosition(getPosition().toVec2d() + dx); //makes animal move by dx

    if (timeLastRot >= sf::seconds(getAppConfig().animal_next_rotation_delay))
    {
        timeLastRot=sf::Time::Zero; //resets timeLastRot to 0
        RotationProbs degProb(computeRotationProbs()); //gets rotation probabilities
        std::piecewise_linear_distribution<> dist(degProb.first.begin(), degProb.first.end(), degProb.second.begin());
        //declares a random generator which generates a random value using a linear distribution by pieces depending on the values of the set degProb, the rotation probabilities
        dirAngle += dist(getRandomGenerator())*DEG_TO_RAD; //changes direction angle
    }
}

void Animal::update(sf::Time dt)
{
    --lifetime;

    //AJOUTER GESTION COMBAT

    timeLastRot += dt;
    move(dt); //makes animal move
}

RotationProbs Animal::computeRotationProbs() const
{
    RotationProbs ret;
    ret.first={ -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180};
    ret.second={0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000};
    return ret;
}

bool Animal::isInAttackState() const
{
    return (state == Attack);
}

void Animal::setState(State S)
{
    state = S;
}

void Animal::drawOn(sf::RenderTarget& target) const
{
    auto const animalSprite = getSprite(); //calls a virtual method for each specific animal
        target.draw(animalSprite);
    if (isDebugOn()) //if debug on you can see the healthPoints
    {
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
            line[0] = { getPosition().toVec2d(), sf::Color::Black };
            line[1] = { getPosition().toVec2d()+200*Vec2d::fromAngle(getDirection()), sf::Color::Black };
            target.draw(line);  //draws line
        auto const text = buildText(to_nice_string(getHP()), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Red);
        target.draw(text); //shows healthPoints via a text
        target.draw(buildAnnulus(getPosition().toVec2d(), getAppConfig().ant_smell_max_distance, sf::Color::Blue, 5)); //draws a ring around animal representing the perception distance
    }
}
