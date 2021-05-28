
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
#include "AntScout.hpp"


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
    getAppEnv().StatsNeedReset();
    --count;
    enemy = nullptr;
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
    :Positionable(TP),
      uid(id),
      foodStock(0.0),
      timeLastSpawn(sf::Time::Zero),
      healthPoints(DEFAULT_ANTHILL_HEALTHPOINTS),
      state(Prosper),
      enemy(nullptr),
      enemyPosition(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2)),
      warTime(sf::Time::Zero)
{
    getAppEnv().StatsNeedReset();
    generateAntWorker(); //Generates an ant at the creation of an anthill
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
    if (received > 0) { //doesn't do anything for negative received
        foodStock += received;
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
    auto const anthillSprite = buildSprite((getPosition()).toVec2d(),
                                           DEFAULT_ANTHILL_SIZE,
                                           getAppTexture(getAppConfig().anthill_texture));;
    target.draw(anthillSprite);
    if (isDebugOn()) { //if debug on you can see the current foodStock in black and the uid in magenta
        auto const foodStockText = buildText("FOOD: " + to_nice_string(foodStock), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black);
        target.draw(foodStockText); //shows quantity of foodStock via a text

        auto const uidText = buildText("UID: " + to_nice_string(uid), getPosition().toVec2d()+Vec2d(0,20), getAppFont(), 15, sf::Color::Magenta);
        target.draw(uidText); //shows anthill's uid via a text

        auto const healthPointsText = buildText("HP: " + to_nice_string(healthPoints), getPosition().toVec2d()+Vec2d(0,40), getAppFont(), 15, sf::Color::Red);
        target.draw(healthPointsText); //shows anthill's healthpoints
        if(state == War)
        {
            auto const targetText = buildText("WAR :"+ to_nice_string(enemy->getUid()),
                                              getPosition().toVec2d()+Vec2d(0,60), getAppFont(), 15, sf::Color::Magenta);
            target.draw(targetText); //shows target anthill's uid via a text
        }
    }
}

void Anthill::receiveEnemyInfo(Anthill* newEnemy, const ToricPosition& newEnemyPos)
{
    enemy = newEnemy;
    enemyPosition = newEnemyPos;
}

void Anthill::update(sf::Time dt)
{
    {
        timeLastSpawn+=dt;
        if (timeLastSpawn >= sf::seconds(getAppConfig().anthill_spawn_delay)) {
            timeLastSpawn = sf::Time::Zero;
            generateAnt(); //randomly generates ant every anthill_spawn_delay
        }

        foodStock -= dt.asSeconds()*ANTHILL_FOOD_COMSUMPTION;
        if (foodStock <= 0.0)
        {
            foodStock = 0.0;
            receiveDamage(HUNGER_DAMAGE_PER_TIME*dt.asSeconds());
        }
        else
        {
            if (foodStock>=DEFAULT_FOOD_COLONY)
            {
                generateAntQueen();
            }
            if (healthPoints<DEFAULT_ANTHILL_HEALTHPOINTS)
            {
                healthPoints+=foodStock*DEFAULT_ANTHILL_REGENERATION;
                if (healthPoints>DEFAULT_ANTHILL_HEALTHPOINTS)
                {
                    healthPoints=DEFAULT_ANTHILL_HEALTHPOINTS;
                }
            }

        }
        if (state == Prosper)
        {
            if (foundEnemy() and foodStock >= FOOD_NEEDED_FOR_WAR)
            {
                if (not enemy->isDead())
                {
                    state = War;
                    generateSoldierKamikazePair();
                }
                else
                {
                    enemy = nullptr;
                }
            }
        }
        else
        {
            warTime += dt;
            if (enemy->isDead() or warTimeOver())
            {
                state = Prosper;
                warTime = sf::Time::Zero;
            }
        }

        if (healthPoints==0) ///////A CHANGERRRRR
        {
            foodStock=0;
        }
    }
}

bool Anthill::foundEnemy() const
{
    return enemy != nullptr;
}

bool Anthill::warTimeOver() const
{
    return warTime >= sf::seconds(DEFAULT_WAR_TIME);
}

bool Anthill::uidIsEqual(Uid checkId) const
{
    return (uid == checkId);
}

void Anthill::generateAntWorker()
{
    if(foodStock>=ANT_WORKER_COST)
    {
        getAppEnv().addAnimal(new AntWorker(getPosition(),uid)); //adds an ant worker to the current environment
        consumeFood(ANT_WORKER_COST);
    }
}

void Anthill::generateAntSoldier()
{
    if(foodStock>=ANT_SOLDIER_COST)
    {
        getAppEnv().addAnimal(new AntSoldier(getPosition(),uid)); //adds an ant soldier to the current environment
        consumeFood(ANT_SOLDIER_COST);
    }
}

void Anthill::generateAntQueen()
{
    if(foodStock>=ANT_QUEEN_COST)
    {
        getAppEnv().addAnimal(new AntQueen(getPosition(),uid)); //adds an ant queen to the current environment
        consumeFood(ANT_QUEEN_COST);
    }
}

void Anthill::generateAntKamikaze()
{
    getAppEnv().addAnimal(new AntKamikaze(getPosition(),uid)); //adds an ant kamikaze to the current environment
    consumeFood(ANT_KAMIKAZE_COST);
}


void Anthill::generateAntScout()
{
    getAppEnv().addAnimal(new AntScout(getPosition(),uid)); //adds an ant scout to the current environment
    consumeFood(ANT_SCOUT_COST);
}

void Anthill::generateWarAntKamikaze()
{
    getAppEnv().addAnimal(new AntKamikaze(getPosition(),uid, enemy, enemyPosition)); //adds an ant kamikaze to the current environment
    consumeFood(ANT_KAMIKAZE_COST);
}

void Anthill::generateWarAntSoldier()
{
    getAppEnv().addAnimal(new AntSoldier(getPosition(),uid,calculateAngle(Positionable(enemy->getPosition())))); //adds an ant soldier to the current environment
    consumeFood(ANT_SOLDIER_COST);
}

void Anthill::generateAnt()
{
    double theta(uniform(0.0,1.0)); //gets a random double between 0.0 and 1.0

    if(state == War)
    {
        if ( (0 <= theta) and (theta <= WAR_WORKER_PROB) ) {
            generateAntWorker();
        }
        else if( (WAR_WORKER_PROB < theta) and (theta <= (WAR_WORKER_PROB + WAR_SOLDIER_PROB)) )
        {
            generateWarAntSoldier();
        }
        else if( ((WAR_WORKER_PROB + WAR_SOLDIER_PROB) < theta) and (theta <= (WAR_WORKER_PROB + WAR_SOLDIER_PROB + WAR_SCOUT_PROB)) )
        {
            generateAntScout();
        }
        else
        {
            generateWarAntKamikaze();
        }
    }
    else
    {
        if ( (0 <= theta) and (theta <= PROSPER_WORKER_PROB) ) {
            generateAntWorker();
        }
        else if( (PROSPER_WORKER_PROB < theta) and (theta <= (PROSPER_WORKER_PROB + PROSPER_SOLDIER_PROB)) )
        {
            generateAntSoldier();
        }
        else if( ((PROSPER_WORKER_PROB + PROSPER_SOLDIER_PROB) < theta) and (theta <= (PROSPER_WORKER_PROB + PROSPER_SOLDIER_PROB + PROSPER_SCOUT_PROB)) )
        {
            generateAntScout();
        }
        else
        {
            generateAntKamikaze();
        }
    }
}

void Anthill::writeLine(std::ofstream &stream) const
{
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
    return healthPoints<=0;
}

void Anthill::generateSoldierKamikazePair()
{
    if (foodStock > (ANT_KAMIKAZE_COST + ANT_SOLDIER_COST))
    {
        generateWarAntKamikaze();
        generateWarAntSoldier();
    }
}
