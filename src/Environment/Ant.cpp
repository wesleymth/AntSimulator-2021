/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#include "Ant.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "Pheromone.hpp"
#include "Environment.hpp"

Ant::Ant()
    :Animal(Vec2d(getAppConfig().world_size/2, getAppConfig().world_size/2))
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

double Ant::getAttackDelay() const
{
    return getAppConfig().ant_attack_delay;
}

Uid Ant::getAnthillUid() const
{
    return anthillUid;
}

void Ant::drawOn(sf::RenderTarget& target) const
{
    Animal::drawOn(target);
    if(getAppConfig().getProbaDebug()) {
        drawPheromoneAngles(target);
    }
}

void Ant::spreadPheromones()
{
    double dist(toricDistance(getPosition(),lastPheromone));
    Vec2d vect(getPosition().toricVector(lastPheromone));
    if(dist*getAppConfig().ant_pheromone_density>=1) {
        for(int i(1); i<=dist*getAppConfig().ant_pheromone_density; ++i) {
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
    for (std::size_t i = 0; i < intervalProbs.first.size(); ++i) {
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
    rotProb.first= { -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180};
    rotProb.second= {0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000};
    Quantities Q(getAppEnv().getPheromoneQuantitiesPerIntervalForAnt(getPosition(), getDirection(), {-180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180}));
    Probs Pphi;
    double sumPphi(0);
    double z(0);
    for(size_t i(0); i<Q.size(); ++i) { // Calculates Pphi vector Pphi[i]=D(Q[i])
        Pphi.push_back(1/(1+exp(-getAppConfig().beta_d*(Q[i]-getAppConfig().q_zero))));
    }
    for(size_t n(0); n<Q.size(); ++n) { //Calculates z(alpha) and nomalisies Pphi then Calculates Pm'(n), probabilities influenced by pheromones
        Pphi[n]=Pphi[n]/sumPphi;
        z+=rotProb.second[n]*pow(Pphi[n], getAppConfig().alpha);
        rotProb.second[n]=(1/z)*rotProb.second[n]*pow(Pphi[n], getAppConfig().alpha);
    }
    return rotProb;
}

bool Ant::isEnemy(Animal const* animal) const
{
    return !isDead() && !animal->isDead() && animal->isEnemyDispatch(this);
}
bool Ant::isEnemyDispatch(Termite const* other) const  //unused param is normal
{
    return true;
}
bool Ant::isEnemyDispatch(Ant const* other) const
{
    return getAnthillUid()!=other->getAnthillUid();
}

