#include "Ant.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "Pheromone.hpp"

Ant::Ant(const Vec2d& pos, double HP, double LT, Uid id)
    :Animal::Animal(pos, HP, LT), anthillID(id)
{
    //Done
}

Ant::Ant(const Vec2d& pos, Uid id)
    :Animal::Animal(pos), anthillID(id) //calls constructor of Animal using only a position
{
    //Done
}

Ant::Ant()
    :Animal::Animal(), anthillID() //calls default constructor of Animal
{
    //Done
}

double Ant::getSpeed() const
{
    return getAppConfig().ant_speed;
}

void Ant::drawOn(sf::RenderTarget& target) const
{
    auto const animalSprite = getSprite(); //calls a virtual method for each specific ant
        target.draw(animalSprite);
    if (isDebugOn()) //if debug on you can see the healthPoints
    {
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
            line[0] = { getPosition().toVec2d(), sf::Color::Black };
            line[1] = { getPosition().toVec2d()+200*Vec2d::fromAngle(getDirection()), sf::Color::Black };
            target.draw(line);  //draws line
        auto const text = buildText(to_nice_string(getHP()), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Red);
        target.draw(text); //shows healthPoints via a text
    }
    if(getAppConfig().getProbaDebug())
    {
        drawPheromoneAngles(target);
    }
}

void Ant::spreadPheromones()
{
    double dist(toricDistance(getPosition(),lastPheromone));
    Vec2d vect(getPosition().toricVector(lastPheromone));
    if(dist*getAppConfig().ant_pheromone_density>=1)
    {
    for(int i(0); i<=dist*getAppConfig().ant_pheromone_density; ++i)
    {
        getAppEnv().addPheromone(new Pheromone(lastPheromone.toVec2d()+i*vect/(dist*getAppConfig().ant_pheromone_density),
                                               getAppConfig().ant_pheromone_energy));
        lastPheromone=getPosition();
    }
    }
}

void Ant::move(sf::Time dt)
{
    Animal::move(dt);
    spreadPheromones();
}

void Ant::drawPheromoneAngles(sf::RenderTarget &target) const
{
    Intervals intervals = {   -180,   -100,    -55,    -25,    -10,      0,     10,     25,     55,    100,    180 };
    auto const intervalProbs = computeRotationProbs();
        // pour intervalProbs (first désigne l'ensemble des angles)
        for (std::size_t i = 0; i < intervalProbs.first.size(); ++i) {
            // "second" designe l'ensemble des probabilités
            auto const msg = std::to_string(intervalProbs.second[i]).substr(2, 4);
            auto const angle = intervalProbs.first[i];
            auto const local = Vec2d::fromAngle(getDirection() + angle * DEG_TO_RAD) * 250;

            auto const text = buildText(msg, getPosition().toVec2d() + local, getAppFont(), 15, sf::Color::Black);
            target.draw(text);
        }

        auto const quantities = getAppEnv().getPheromoneQuantitiesPerIntervalForAnt(getPosition(), getDirection(), intervals);
        for (std::size_t i = 0; i < quantities.size(); ++i) {
            auto const msg = std::to_string(quantities[i]).substr(0, 4);
            auto const angle = intervals[i];
            auto const local = Vec2d::fromAngle(getDirection() + angle * DEG_TO_RAD) * 200;

            auto const text = buildText(msg, getPosition().toVec2d() + local, getAppFont(), 15, sf::Color::Red);
            target.draw(text);
        }
}
