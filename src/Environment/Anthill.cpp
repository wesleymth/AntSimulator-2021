#include "Anthill.hpp"
#include "Utility/Utility.hpp"
#include "../Application.hpp"
#include "../Random/Random.hpp"
#include "Animal.hpp"
#include "AntSoldier.hpp"
#include "AntWorker.hpp"

Anthill::Anthill()
{
    //Done
}

Anthill::Anthill(const ToricPosition& TP)
    :Positionable(TP), uid(createUid()), foodStock(0.0), timeLastSpawn(sf::Time::Zero)
{
    generateAnt(); //Generates an ant at the creation of an anthill
}

Anthill::Anthill(const Vec2d& pos)
    :Anthill(ToricPosition(pos))
{
    //Done
}

void Anthill::receiveFood(Quantity received)
{
    if (received > 0)
    {
        foodStock += received;
    }
}

void Anthill::drawOn(sf::RenderTarget& target) const
{
    auto const anthillSprite = buildSprite((getPosition()).toVec2d(),
                                           DEFAULT_ANTHILL_SIZE,
                                           getAppTexture(getAppConfig().anthill_texture));;
        target.draw(anthillSprite);
    if (isDebugOn()) //if debug on you can see the current foodStock in black and the uid in magenta
    {
        auto const food = buildText(to_nice_string(foodStock), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black);
        target.draw(food); //shows quantity of foodStock via a text

        auto const id = buildText(to_nice_string(uid), getPosition().toVec2d()+Vec2d(0,40), getAppFont(), 15, sf::Color::Magenta);
        target.draw(id); //shows anthill uid via a text
    }
}

void Anthill::update(sf::Time dt)
{

    timeLastSpawn+=dt;
    if (timeLastSpawn >= sf::seconds(getAppConfig().anthill_spawn_delay))
    {
        timeLastSpawn = sf::Time::Zero;
        generateAnt();
    }
}

double Anthill::getWorkerProb() const
{
    return getAppConfig().anthill_worker_prob_default;
}

void Anthill::generateAntWorker() const
{
    getAppEnv().addAnimal(new AntWorker(getPosition().toVec2d(),uid));
}

void Anthill::generateAntSoldier() const
{
    getAppEnv().addAnimal(new AntSoldier(getPosition().toVec2d(),uid));
}

void Anthill::generateAnt() const
{
    double theta(uniform(0,1)); //                  #################### NE MARCHE PAS DEMANDER A COLIN
    //if prob = 0 que des soldats mais si prob = 1, si theta = 1 il vas y avoir une soldate
    if (getWorkerProb() != 1)
    {
        if ( (theta < getWorkerProb()) and (theta >= 0))
        {
            generateAntWorker();
        }
        else
        {
            generateAntSoldier();
        }
    }
    else
    {
        generateAntWorker();
    }
}

bool Anthill::uidIsEqual(Uid checkId) const
{
    return (uid == checkId);
}
