#include "Ant.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "Pheromone.hpp"
#include "Environment.hpp"

Ant::Ant()
{
    //Done
}

Ant::Ant(const ToricPosition& TP, double HP, double LT, Uid uid)
    :Animal::Animal(TP, HP, LT), anthillUid(uid), lastPheromone(TP)
{
    //Done
}

Ant::Ant(const Vec2d& pos, double HP, double LT, Uid uid)
    :Ant(ToricPosition(pos), HP, LT, uid)
{
    //Done
}

Ant::Ant(const ToricPosition& TP, Uid uid)
    :Animal::Animal(TP), anthillUid(uid), lastPheromone(TP)
{
    //Done
}

Ant::Ant(const Vec2d& pos, Uid uid)
    :Ant(ToricPosition(pos),uid)
{
    //Done
}

double Ant::getSpeed() const
{
    return getAppConfig().ant_speed;
}

Uid Ant::getAnthillUid() const
{
    return anthillUid;
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
        target.draw(buildAnnulus(getPosition().toVec2d(), getAppConfig().ant_smell_max_distance, sf::Color::Blue, 5)); //draws a ring around ant representing the perception distance
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
        for(int i(1); i<=dist*getAppConfig().ant_pheromone_density; ++i)
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

RotationProbs Ant::computeRotationProbs() const
{
    RotationProbs rotProb;
    rotProb.first={ -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180};
    rotProb.second={0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000};
    Quantities Q(getAppEnv().getPheromoneQuantitiesPerIntervalForAnt(getPosition(), getDirection(), {-180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180}));
    Probs Pphi;
    double z(0);
    for(size_t i(0); i<Q.size(); ++i)
    {
        Pphi.push_back(1/(1+exp(-getAppConfig().beta_d*(Q[i]-getAppConfig().q_zero))));
    }
    for(size_t n(0); n<Q.size(); ++n)
    {
        z+=rotProb.second[n]*pow(Pphi[n], getAppConfig().alpha);
    }
    for(size_t n(0); n<rotProb.second.size(); ++n)
    {
        rotProb.second[n]=(1/z)*rotProb.second[n]*pow(Pphi[n], getAppConfig().alpha);
    }
    return rotProb;
}

