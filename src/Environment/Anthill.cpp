#include "Anthill.hpp"
#include "Utility/Utility.hpp"
#include "../Application.hpp"
#include "../Random/Random.hpp"
#include "Animal.hpp"
#include "AntSoldier.hpp"
#include "AntWorker.hpp"

Anthill::Anthill()
{

}

Anthill::Anthill(const ToricPosition& TP)
    :Positionable(TP), uid(createUid()), foodStock(0.0), timeLastSpawn(sf::Time::Zero)
{

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
        auto const text = buildText(to_nice_string(foodStock), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black);
        target.draw(text); //shows quantity of foodStock via a text

        auto const txt = buildText(to_nice_string(uid), getPosition().toVec2d()+Vec2d(0,40), getAppFont(), 15, sf::Color::Magenta);
        target.draw(txt); //shows anthill uid via a text
    }
}

void Anthill::update(sf::Time dt)
{
    timeLastSpawn+=dt;
    /*if (timeLastSpawn >= getAppConfig().anthill_spawn_delay)
    {
        timeLastSpawn = sf::Time::Zero;
        double theta(uniform(0,1));
        if ( (0 <= theta) and (theta <= getWorkerProb()) )
        {
            getAppEnv().addAnimal(new AntWorker(getPosition().toVec2d(),uid));
        }
        else
        {
            getAppEnv().addAnimal(new AntSoldier(getPosition().toVec2d(),uid));
        }
    }*/
}

double Anthill::getWorkerProb() const
{
    return getAppConfig().anthill_worker_prob_default;
}
