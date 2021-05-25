
/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#include "Anthill.hpp"
#include "Utility/Utility.hpp"
#include "../Application.hpp"
#include "../Random/Random.hpp"
#include "Animal.hpp"
#include "AntSoldier.hpp"
#include "AntWorker.hpp"
#include "AntQueen.hpp"


int Anthill::count = 0;

int Anthill::getCount()
{
    return count;
}

Anthill::Anthill()
    :Anthill(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2))
{
    //Done
}

Anthill::~Anthill()
{
    --count;
}

Anthill::Anthill(const ToricPosition& TP)
    :Anthill(TP, createUid())
{
    //Done
}

Anthill::Anthill(const Vec2d& pos)
    :Anthill(ToricPosition(pos))
{
    //Done
}

Anthill::Anthill(const ToricPosition& TP, Uid id)
    :Positionable(TP), uid(id), foodStock(0.0), timeLastSpawn(sf::Time::Zero), healthPoints(2)
{
    generateAnt(); //Generates an ant at the creation of an anthill
    ++count;
}

double Anthill::getWorkerProb() const
{
    return getAppConfig().anthill_worker_prob_default;
}

Uid Anthill::getUid() const
{
    return uid;
}

Quantity Anthill::getFoodStock() const
{
    return foodStock;
};

void Anthill::receiveFood(Quantity received)
{
    if (isDead())
    {
        if (received > 0) { //doesn't do anything for negative received
            foodStock += received;
        }
    }
}

void Anthill::consumeFood(Quantity removed)
{
    if (removed > 0 and foodStock>removed) { //doesn't do anything for negative received
        foodStock -= removed;
    }
}

void Anthill::drawOn(sf::RenderTarget& target) const
{
    if (not isDead())
    {
        auto const anthillSprite = buildSprite((getPosition()).toVec2d(),
                                               DEFAULT_ANTHILL_SIZE,
                                               getAppTexture(getAppConfig().anthill_texture));;
        target.draw(anthillSprite);
        if (isDebugOn()) { //if debug on you can see the current foodStock in black and the uid in magenta
            auto const foodStockText = buildText(to_nice_string(foodStock), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black);
            target.draw(foodStockText); //shows quantity of foodStock via a text

            auto const uidText = buildText(to_nice_string(uid), getPosition().toVec2d()+Vec2d(0,40), getAppFont(), 15, sf::Color::Magenta);
            target.draw(uidText); //shows anthill's uid via a text

            auto const healthPointsText = buildText(to_nice_string(healthPoints), getPosition().toVec2d()+Vec2d(0,80), getAppFont(), 15, sf::Color::Red);
            target.draw(healthPointsText); //shows anthill's healthpoints
        }
    } else {
        if (isDebugOn())  // Makes a cross on position of dead anthill
        {
            sf::VertexArray line1(sf::PrimitiveType::Lines, 2);
            line1[0] = { getPosition().toVec2d() + Vec2d(5, 5), sf::Color::Red };
            line1[1] = { getPosition().toVec2d() + Vec2d(-5, -5), sf::Color::Red };
            sf::VertexArray line2(sf::PrimitiveType::Lines, 2);
            line2[0] = { getPosition().toVec2d() + Vec2d(-5, 5), sf::Color::Red };
            line2[1] = { getPosition().toVec2d() + Vec2d(5, -5), sf::Color::Red };
            target.draw(line1);  //draws line
            target.draw(line2);  //draws line
        }
    }
}

void Anthill::update(sf::Time dt)
{
    if (not isDead())
    {
        timeLastSpawn+=dt;
        if (timeLastSpawn >= sf::seconds(getAppConfig().anthill_spawn_delay)) {
            timeLastSpawn = sf::Time::Zero;
            generateAnt(); //randomly generates ant every anthill_spawn_delay
        }
        if (foodStock==0)
        {
            receiveDamage(HUNGER_DAMAGE_PER_TIME*dt.asSeconds());
        }
        if (foodStock>=DEFAULT_FOOD_COLONY)
        {
            generateAntQueen();
        }
        if (healthPoints==0)
        {
            foodStock=0;
        }
        if (healthPoints<DEFAULT_ANTHILL_HEALTHPOINTS and foodStock>=0)
        {
            healthPoints+=foodStock*DEFAULT_ANTHILL_REGENERATION;
        }
        if (getAppEnv().isTemperatureExtreme())
        {
            receiveDamage(abs(getAppEnv().getTemperature()-getAppConfig().temperature_initial)*dt.asSeconds()*TEMPERATURE_DAMAGE_RATE);
        }
    }
}

bool Anthill::uidIsEqual(Uid checkId) const
{
    return (uid == checkId);
}

void Anthill::generateAntWorker()
{
    getAppEnv().addAnimal(new AntWorker(getPosition(),uid)); //adds an ant worker to the current environment
    consumeFood(ANT_WORKER_COST);
}

void Anthill::generateAntSoldier()
{
    getAppEnv().addAnimal(new AntSoldier(getPosition(),uid)); //adds an ant soldier to the current environment
    consumeFood(ANT_SOLDIER_COST);
}

void Anthill::generateAntQueen()
{
    getAppEnv().addAnimal(new AntQueen(getPosition(),uid)); //adds an ant queen to the current environment
    consumeFood(ANT_QUEEN_COST);
}

void Anthill::generateAnt()
{
    double theta(uniform(0.0,1.0)); //gets a random double between 0.0 and 1.0
    if ( (0 <= theta) and (theta <= getWorkerProb())) {
        generateAntWorker();
    } else {
        generateAntSoldier();
    }
}

void Anthill::writeLine(std::ofstream &stream) const
{
    if (not isDead())
    {
        stream << "anthill " << getPosition().x() << " " << getPosition().y() << std::endl;
    }
}

void Anthill::receiveDamage(double damage)
{
    if(healthPoints>damage)
    {
        healthPoints-=damage;
    } else {
        healthPoints=0;
    }
}

bool Anthill::isDead() const // a l'origine nous avions prevu de de pouvoir tuer les anthill mais il y a eu un conflit avec le code fourni dans Graph
{
    return healthPoints>0;
}
