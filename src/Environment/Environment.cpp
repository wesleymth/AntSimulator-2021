/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */
#include "../Utility/Utility.hpp"
#include "Environment.hpp"
#include "../Application.hpp"
#include "AntSoldier.hpp"
#include "AntWorker.hpp"
#include "AntQueen.hpp"
#include "Termite.hpp"
#include "AntScout.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include "Random/Random.hpp"

Environment::Environment()
    :animals(), foods(), anthills(), pheromones(), foodGenerator(),
     showPheromones(), temperature(getAppConfig().temperature_initial), temp(Normal), resetStatsNeeded(false)
{
    //Done
}
Environment::~Environment()
{
    reset();
}

void Environment::addAnimal(Animal* animal)
{
    animals.push_back(animal);
}

void Environment::addFood(Food* food)
{
    foods.push_back(food);
}

void Environment::addAnthill(Anthill* anthill)
{
    anthills.push_back(anthill);
}

void Environment::update(sf::Time dt)
{
    totalTime+=dt;
    foodGenerator.update(dt); //operator overload: uses update method of FoodGenerator class

    for(auto& animal: animals) {
        animal->update(dt); //in charge of movement and incrementation of attributes
        if (animal->isDead()) { //gets rid of the animal in the attribute of the environement if the animal is dead
            delete animal;
            animal = nullptr;
        }
        animals.erase(std::remove(animals.begin(), animals.end(), nullptr), animals.end());
    }

    for(auto& anthill: anthills) {
    anthill->update(dt); //in charge of updating the anthills
        if (anthill->isDead()) { //gets rid of the animal in the attribute of the environement if the animal is dead
            delete anthill;
            anthill = nullptr;
        }
        anthills.erase(std::remove(anthills.begin(), anthills.end(), nullptr), anthills.end());
    }

    for(auto& phero: pheromones) {
        phero->update(dt); //in charge of movement and incrementation of attributes
        if (phero->isNegligeable()) { //gets rid of the pheromone in the attribute of the environement
            delete phero;
            phero = nullptr;
        }
        pheromones.erase(std::remove(pheromones.begin(), pheromones.end(), nullptr), pheromones.end());
    }

    for(auto& food: foods) {
        food->update(dt);
        if (food->zeroQuantity()) { //gets rid of the food in the attribute of the environement if its quantity equals 0
            delete food;
            food = nullptr;
        }
        foods.erase(std::remove(foods.begin(), foods.end(), nullptr), foods.end());
    }

    if (temp==Normal)
    {
        temperature=getAppConfig().temperature_initial+14*sin(getAppConfig().TEMPERATURE_SIN_FACTOR*totalTime.asSeconds());
    } else if (temp==Cold)
    {
        temperature=getAppConfig().COLD_TEMPERATURE;
    } else {
        temperature=getAppConfig().HOT_TEMPERATURE;
    }
}


void Environment::drawOn(sf::RenderTarget& targetWindow) const
{
    for(auto& food: foods) {
        food->drawOn(targetWindow); //operator overload: uses drawOn method of Food class
    }

    for(auto& animal: animals) {
        animal->drawOn(targetWindow); //operator overload: uses drawOn method of Animal class
    }

    for(auto& anthill: anthills) {
        anthill->drawOn(targetWindow); //operator overload: uses drawOn method of Anthill class
    }

    if(showPheromones) {
        for(auto& pheromone: pheromones) {
            pheromone->drawOn(targetWindow); //operator overload: uses drawOn method of Pheromone class
        }
    }
    if (isDebugOn())
    {
        if (temp==Cold)
        {
            auto const text = buildText("COLD", Vec2d(1,1), getAppFont(), 15, sf::Color::Blue);
            targetWindow.draw(text); //shows temp via a text
        } else if (temp==Normal)
        {
            auto const text = buildText("NORMAL", Vec2d(1,1), getAppFont(), 15, sf::Color::Black);
            targetWindow.draw(text); //shows temp via a text
        } else {
            auto const text = buildText("HOT", Vec2d(1,1), getAppFont(), 15, sf::Color::Red);
            targetWindow.draw(text); //shows temp via a text
        }
        auto const text = buildText(to_nice_string(temperature),  Vec2d(1,15), getAppFont(), 15, sf::Color::Red);
        targetWindow.draw(text); //shows healthPoints via a text

    }
}

void Environment::reset()
{
    for(auto& animal: animals) { //desaloccation of memory
        delete animal;
        animal = nullptr;
    }
    for(auto& food: foods) { //desaloccation of memory
        delete food;
        food = nullptr;
    }
    for(auto& anthill: anthills) { //desaloccation of memory
        delete anthill;
        anthill = nullptr;
    }
    for(auto& pheromone: pheromones) { //desaloccation of memory
        delete pheromone;
        pheromone = nullptr;
    }
    animals.clear();
    foods.clear();
    anthills.clear();
    pheromones.clear();
}

Temperature Environment::getTemperature() const
{
    return temperature;
}

Food* Environment::getClosestFoodForAnt(ToricPosition const& position) const
{
    Food* foodptr(nullptr);
    double compareDistance(getAppConfig().world_size); //sets the distance to compare to a very large number
    for(auto& food: foods) {
        if (toricDistance(position, food->getPosition()) < compareDistance) { //if the distance of the next food is lower than the distance of the last food
            compareDistance = toricDistance(position, food->getPosition()); //distance is then equal to the distance of the new food
            if (compareDistance <= getAppConfig().ant_max_perception_distance) { //if the food is in the radius of perception of the ant
                foodptr = food;
            }
        }
    }
    return foodptr;
}

Animal* Environment::getClosestAnimalForAnimal(const Animal* currentInstance) const
{
    Animal* animalptr(nullptr);
    double compareDistance(getAppConfig().world_size); //sets the distance to compare to a very large number
    for(auto& animal: animals)
    {
        if ((toricDistance(currentInstance->getPosition(), animal->getPosition()) < compareDistance) and (currentInstance != animal))
        { //if the distance of the next animal is lower than the distance of the last animal and the animal isn't itself
            compareDistance = toricDistance(currentInstance->getPosition(), animal->getPosition()); //distance is then equal to the distance of the new animal
            if (compareDistance <= getAppConfig().animal_sight_distance)
            { //if the animal is in the sight distance of the given animal
                animalptr = animal;
            }
        }
    }
    return animalptr;
}

Anthill* Environment::getAnthillForAnt(ToricPosition const& position, Uid anthillUid) const
{
    Anthill* anthillptr(nullptr); //if it doesn't find an anthill with the given anthillId, it will return nullptr
    for(auto& anthill: anthills) {
        if ((anthill->uidIsEqual(anthillUid)) and (toricDistance(position, anthill->getPosition()) < getAppConfig().ant_max_perception_distance))//checks if the uids are equal and if the anthill is in the radius of perception of the ant
        {
            anthillptr = anthill;
        }
    }
    return anthillptr;
}

Anthill* Environment::getClosestAnthillForAnt(Ant* const& currentInstance) const
{
    Anthill* anthillptr(nullptr);
    double compareDistance(getAppConfig().world_size); //sets the distance to compare to a very large number
    for(auto& anthill: anthills)
    {
        if ((toricDistance(currentInstance->getPosition(), anthill->getPosition()) < compareDistance))
        { //if the distance of the next anthill is lower than the distance of the last anthill
            compareDistance = toricDistance(currentInstance->getPosition(), anthill->getPosition()); //distance is then equal to the distance of the new anthill
            if ((compareDistance <= getAppConfig().ant_max_perception_distance))
            { //if the anthill is in the sight distance of the given ant
                anthillptr = anthill;
            }
        }
    }
    return anthillptr;
}


Pheromone* Environment::getClosestPheromoneForAnt(Ant * const &currentInstance) const
{
    Pheromone* pheromoneptr(nullptr);
    double compareDistance(getAppConfig().world_size); //sets the distance to compare to a very large number
    for(auto& pheromone: pheromones)
    {
        if ((toricDistance(currentInstance->getPosition(), pheromone->getPosition()) < compareDistance))
        { //if the distance of the next pheromone is lower than the distance of the last pheromone
            compareDistance = toricDistance(currentInstance->getPosition(), pheromone->getPosition()); //distance is then equal to the distance of the new pheromone
            if (compareDistance <= getAppConfig().ant_max_perception_distance)
            { //if the pheromone is in the sight distance of the given ant
                pheromoneptr = pheromone;
            }
        }
    }
    return pheromoneptr;
}

bool Environment::getPheromoneInfo(AntKamikaze* const &currentInstance) const
{
    //bool res(false);

    for(auto& pheromone: pheromones)
    {
        if ((toricDistance(currentInstance->getPosition(), pheromone->getPosition()) < getAppConfig().ant_max_perception_distance))
        { //if the distance of the next pheromone is lower than the distance of the last pheromone
            if(pheromone->interact())
            {
                //currentInstance->setTarget(pheromone->getEnemy());
                //currentInstance->setTargetPosition(pheromone->getEnemyPosition());
                if (currentInstance->getTarget() != pheromone->getEnemy())
                {
                    currentInstance->receiveTargetInformation(pheromone->getEnemy(),pheromone->getEnemyPosition());
                    return true;
                }
            }
        }
    }

    return false;
}

void Environment::addPheromone(Pheromone* phero)
{
    pheromones.push_back(phero);
}

bool Environment::togglePheromoneDisplay()
{
    return (showPheromones=not showPheromones);
}

Quantities Environment::getPheromoneQuantitiesPerIntervalForAnt(const ToricPosition &position,
        Angle direction_rad,
        const Intervals &angles)
{
    Quantities Q(11,0);
    for(auto phero: pheromones) { //looks in list of all pheromones
        if(toricDistance(position, phero->getPosition())<=getAppConfig().ant_smell_max_distance) { // only considers pheromones within smelling distance
            Angle beta((position.toricVector(phero->getPosition()).angle() - direction_rad) / DEG_TO_RAD); //gets angle between ant and pheromone
            while(-180>beta or beta>180) {
                if(beta>180) {
                    beta-=360;
                } else {
                    beta+=360;
                }

            }
            Angle betaPrime(angles[0]);
            int indice(0);
            for(size_t i(1); i<angles.size(); ++i) {
                if(abs(angles[i]-beta)<abs(betaPrime-beta)) {
                    betaPrime=angles[i];
                    indice=i;
                }
            }
            Q[indice]=phero->getQuantity();

        }
    }
    return Q;
}

std::vector<std::string> Environment::getAnthillsIds() const
{
    std::vector<std::string> res;
    for(auto& anthill: anthills)
    {
        res.push_back("anthill #" + std::to_string(anthill->getUid()));
    }
    return res;
}

std::unordered_map<std::string, double> Environment::fetchData(const std::string & title)
{
    if(title == "general")
    {
        return
        {
            {"worker ants", AntWorker::getCount()},
            {"soldier ants", AntSoldier::getCount()},
            {"termites", Termite::getCount()},
            {"scout ants", AntScout::getCount()},
            {"kamikaze ants", AntKamikaze::getCount()},
            {"temperature", temperature}
        };
    } else if (title == "food")
    {
        return
        {
            {"food", Food::getCount()}
        };
    } else if (title == "anthills")
    {
        std::unordered_map<std::string, double> new_data;
        for(auto& anthill: anthills)
        {
            new_data.insert(std::make_pair<std::string,double>("anthill #" + std::to_string(anthill->getUid()),anthill->getFoodStock()));
        }
        return new_data;
    } else {
        throw std::invalid_argument("Graph title doesn't correspond to defined graphs");
    }
}



void Environment::saveMap() const
{

    std::string fileName;
    std::cout << "File Name.map" << std::endl;
    std::cin >> fileName;
    std::ofstream file(RES_LOCATION+fileName);
    for(auto& food : foods)
    {
        food->writeLine(file);
    }
    for(auto anthill : anthills)
    {
        anthill->writeLine(file);
    }
    for(auto animal : animals)
    {
        animal->writeLine(file);
    }
    file.close();

}

bool Environment::isTemperatureExtreme() const
{
    return (getAppEnv().getTemperature()<=getAppConfig().COLD_TEMPERATURE or getAppEnv().getTemperature()>=getAppConfig().HOT_TEMPERATURE);
}

void Environment::toggleTemp()
{
    if (temp==Cold)
    {
        temp=Normal;
    } else if (temp==Normal)
    {
        temp=Hot;
    } else {
        temp=Cold;
    }
}

void Environment::StatsNeedReset()
{
    resetStatsNeeded=true;
}

void Environment::StatsReset()
{
    resetStatsNeeded=false;
}

bool Environment::anthillStillAlive(Anthill* currentInstance) const
{
    bool res(false);
    for(auto& anthill: anthills)
    {
        if (anthill == currentInstance)
        {
            res = true;
        }
    }
    return res;
}


bool Environment::getStatsStatus() const
{
    return resetStatsNeeded;
}
