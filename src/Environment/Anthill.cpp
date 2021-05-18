
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

int Anthill::count = 0;

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
    :Positionable(TP), uid(createUid()), foodStock(0.0), timeLastSpawn(sf::Time::Zero)
{
    generateAnt(); //Generates an ant at the creation of an anthill
    ++count;
}

Anthill::Anthill(const Vec2d& pos)
    :Anthill(ToricPosition(pos))
{
    //Done
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
    if (received > 0) { //doesn't do anything for negative received
        foodStock += received;
    }
}

void Anthill::drawOn(sf::RenderTarget& target) const
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
    }
}

void Anthill::update(sf::Time dt)
{
    timeLastSpawn+=dt;
    if (timeLastSpawn >= sf::seconds(getAppConfig().anthill_spawn_delay)) {
        timeLastSpawn = sf::Time::Zero;
        generateAnt(); //randomly generates ant every anthill_spawn_delay
    }
}

bool Anthill::uidIsEqual(Uid checkId) const
{
    return (uid == checkId);
}

void Anthill::generateAntWorker() const
{
    getAppEnv().addAnimal(new AntWorker(getPosition().toVec2d(),uid)); //adds an ant worker to the current environment
}

void Anthill::generateAntSoldier() const
{
    getAppEnv().addAnimal(new AntSoldier(getPosition().toVec2d(),uid)); //adds an ant soldir to the current environment
}

void Anthill::generateAnt() const
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
    stream << "anthill " << getPosition().x() << " " << getPosition().y() << std::endl;
}

void Anthill::takeDamage(double damage)
{
    if(healthPoints>damage)
    {
        healthPoints-=damage;
    } else {
        healthPoints=0;
    }
}
