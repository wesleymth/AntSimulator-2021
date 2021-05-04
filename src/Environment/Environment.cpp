/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#include "Environment.hpp"
#include "../Application.hpp"

Environment::Environment()
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
        if (food->zeroQuantity()) { //gets rid of the food in the attribute of the environement if its quantity equals 0
            delete food;
            food = nullptr;
        }
        foods.erase(std::remove(foods.begin(), foods.end(), nullptr), foods.end());
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

Food* Environment::getClosestFoodForAnt(ToricPosition const& position)
{
    Food* foodptr(nullptr);
    double compareDistance(getAppConfig().world_size); //sets the distance to compare to a very large number
    if (foods.size() != 0) {
        compareDistance = (toricDistance(position, foods[0]->getPosition())); //sets the comparing distance to the distance between the first food and the position of the ant worker
    }
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

Animal* Environment::getClosestAnimalForAnimal(const Animal* currentInstance)
{
    Animal* animalptr(nullptr);
    double compareDistance(getAppConfig().world_size); //sets the distance to compare to a very large number
    for(auto& animal: animals) {
        if ((toricDistance(currentInstance->getPosition(), animal->getPosition()) < compareDistance) and (currentInstance != animal)) { //if the distance of the next animal is lower than the distance of the last animal and the animal isn't itself
            compareDistance = toricDistance(currentInstance->getPosition(), animal->getPosition()); //distance is then equal to the distance of the new animal
            if (compareDistance <= getAppConfig().animal_sight_distance) { //if the animal is in the sight distance of the given animal
                animalptr = animal;
            }
        }
    }
    return animalptr;
}

Anthill* Environment::getAnthillForAnt(ToricPosition const& position, Uid anthillUid)
{
    Anthill* anthillptr(nullptr); //if it doesn't find an anthill with the given anthillId, it will return nullptr
    for(auto& anthill: anthills) {
        if ((anthill->uidIsEqual(anthillUid)) and (toricDistance(position, anthill->getPosition()) < getAppConfig().ant_max_perception_distance) )
            //checks if the uids are equal and if the anthill is in the radius of perception of the ant
        {
            anthillptr = anthill;
        }
    }
    return anthillptr;
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

std::unordered_map<std::string, double> Environment::fetchData(const std::string &)
{
    return {
        {"worker ants", p1j+1},
        {"soldier ants", p2j+1},
        {"termites", p3j+1},
        {"temperature", p4j+1}
      }
}
