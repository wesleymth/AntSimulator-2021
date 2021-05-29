
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
      foodStock(getAppConfig().DEFAULT_ANTHILL_FOODSTOCK),
      timeLastSpawn(sf::Time::Zero),
      healthPoints(getAppConfig().DEFAULT_ANTHILL_HEALTHPOINTS),
      state(Prosper),
      enemy(nullptr),
      enemyPosition(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2)),
      warTime(sf::Time::Zero)
{
    getAppEnv().StatsNeedReset();
    generateAntWorker(); //Generates an antWorker at the creation of an anthill because it does'nt cost anything and will get food for the anthill
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
                                           getAppConfig().DEFAULT_ANTHILL_SIZE,
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

        foodStock -= dt.asSeconds()*getAppConfig().ANTHILL_FOOD_COMSUMPTION; //decrements foodStock
        if (foodStock <= 0.0)
        {
            if (state != Decay)
            {
                state = Decay;
            }
            foodStock = 0.0;
            receiveDamage(getAppConfig().HUNGER_DAMAGE_PER_TIME*dt.asSeconds()); //if anthill is in decay it loses healthpoints
        }
        else
        {
            if (state == Decay)
            {
                state = Prosper;
            }
            if (foodStock>=getAppConfig().DEFAULT_FOOD_COLONY)
            {
                generateAntQueen(); //once it has enough food it will create a new ant queen
            }
            if (healthPoints<getAppConfig().DEFAULT_ANTHILL_HEALTHPOINTS and not isDead())
            {
                healthPoints+=getAppConfig().DEFAULT_ANTHILL_REGENERATION; //if anthill is in prosper state, it will regenerate its hp to the max
                if (healthPoints>getAppConfig().DEFAULT_ANTHILL_HEALTHPOINTS)
                {
                    healthPoints=getAppConfig().DEFAULT_ANTHILL_HEALTHPOINTS;
                }
            }
        }
        if (not (state == War))
        {
            if (foundEnemy() and foodStock >= getAppConfig().FOOD_NEEDED_FOR_WAR) //if it has an enemy and sufficient food to create an army
            {
                if (getAppEnv().anthillStillAlive(enemy)) //if the enemy is still alive
                {
                    state = War;
                    generateSoldierKamikazePair(); //generates a kamikaze and a soldier at once to attack fast
                }
                else
                {
                    enemy = nullptr; //if the enemy is dead there is no need to go to war
                }
            }
        }
        else
        {
            warTime += dt;
            if (not getAppEnv().anthillStillAlive(enemy) or warTimeOver()) //if the enemy is dead or they have been fighting too long
            {
                state = Prosper; //goes back toa state of prosperity
                warTime = sf::Time::Zero;
            }
        }
    }
}

bool Anthill::foundEnemy() const
{
    return enemy != nullptr;
}

bool Anthill::warTimeOver() const
{
    return warTime >= sf::seconds(getAppConfig().DEFAULT_WAR_TIME);
}

bool Anthill::uidIsEqual(Uid checkId) const
{
    return (uid == checkId);
}

void Anthill::generateAntWorker()
{
    if(foodStock>=getAppConfig().ANT_WORKER_COST)
    {
        getAppEnv().addAnimal(new AntWorker(getPosition(),uid)); //adds an ant worker to the current environment
        consumeFood(getAppConfig().ANT_WORKER_COST);
    }
}

void Anthill::generateAntSoldier()
{
    if(foodStock>=getAppConfig().ANT_SOLDIER_COST)
    {
        getAppEnv().addAnimal(new AntSoldier(getPosition(),uid)); //adds an ant soldier to the current environment
        consumeFood(getAppConfig().ANT_SOLDIER_COST);
    }
}

void Anthill::generateAntQueen()
{
    if(foodStock>=getAppConfig().ANT_QUEEN_COST)
    {
        getAppEnv().addAnimal(new AntQueen(getPosition(),uid)); //adds an ant queen to the current environment
        consumeFood(getAppConfig().ANT_QUEEN_COST);
    }
}

void Anthill::generateAntKamikaze()
{
    if(foodStock>=getAppConfig().ANT_KAMIKAZE_COST)
    {
        getAppEnv().addAnimal(new AntKamikaze(getPosition(),uid)); //adds an ant kamikaze to the current environment
        consumeFood(getAppConfig().ANT_KAMIKAZE_COST);
    }
}


void Anthill::generateAntScout()
{
    if(foodStock>=getAppConfig().ANT_SCOUT_COST)
    {
        getAppEnv().addAnimal(new AntScout(getPosition(),uid)); //adds an ant scout to the current environment
        consumeFood(getAppConfig().ANT_SCOUT_COST);
    }
}

void Anthill::generateWarAntKamikaze()
{
    if(foodStock>=getAppConfig().ANT_KAMIKAZE_COST)
    {
        getAppEnv().addAnimal(new AntKamikaze(getPosition(),uid, enemy, enemyPosition)); //adds an ant kamikaze to the current environment
        consumeFood(getAppConfig().ANT_KAMIKAZE_COST);
    }
}

void Anthill::generateWarAntSoldier()
{
    if(foodStock>=getAppConfig().ANT_SOLDIER_COST)
    {
        getAppEnv().addAnimal(new AntSoldier(getPosition(),uid,calculateAngle(Positionable(enemy->getPosition())))); //adds an ant soldier to the current environment
        consumeFood(getAppConfig().ANT_SOLDIER_COST);
    }
}

void Anthill::generateAnt()
{
    double theta(uniform(0.0,1.0)); //gets a random double between 0.0 and 1.0

    if(state == War)
    {
        if ( (0 <= theta) and (theta <= getAppConfig().WAR_WORKER_PROB) ) {
            generateAntWorker();
        }
        else if( (getAppConfig().WAR_WORKER_PROB < theta) and (theta <= (getAppConfig().WAR_WORKER_PROB + getAppConfig().WAR_SOLDIER_PROB)) )
        {
            generateWarAntSoldier(); //made to attack the enemy
        }
        else if( ((getAppConfig().WAR_WORKER_PROB + getAppConfig().WAR_SOLDIER_PROB) < theta) and (theta <= (getAppConfig().WAR_WORKER_PROB + getAppConfig().WAR_SOLDIER_PROB + getAppConfig().WAR_SCOUT_PROB)) )
        {
            generateAntScout();
        }
        else //all probabilities sum up to 1
        {
            generateWarAntKamikaze(); //made to attack the enemy
        }
    }
    else if (state == Prosper)
    {
        if ( (0 <= theta) and (theta <= getAppConfig().PROSPER_WORKER_PROB) ) {
            generateAntWorker();
        }
        else if( (getAppConfig().PROSPER_WORKER_PROB < theta) and (theta <= (getAppConfig().PROSPER_WORKER_PROB + getAppConfig().PROSPER_SOLDIER_PROB)) )
        {
            generateAntSoldier();
        }
        else if( ((getAppConfig().PROSPER_WORKER_PROB + getAppConfig().PROSPER_SOLDIER_PROB) < theta) and (theta <= (getAppConfig().PROSPER_WORKER_PROB + getAppConfig().PROSPER_SOLDIER_PROB + getAppConfig().PROSPER_SCOUT_PROB)) )
        {
            generateAntScout();
        }
        else //all probabilities sum up to 1
        {
            generateAntKamikaze();
        }
    }
    else if(state == Decay) //if decaying the priority is to find food
    {
        generateAntWorker();
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

bool Anthill::isDead() const
{
    return healthPoints<=0;
}

void Anthill::generateSoldierKamikazePair()
{
    if (foodStock > (getAppConfig().ANT_KAMIKAZE_COST + getAppConfig().ANT_SOLDIER_COST))
    {
        generateWarAntKamikaze();
        generateWarAntSoldier();
    }
}
