#include "Environment.hpp"
#include "../Application.hpp"

Environment::Environment()
{
    //Done
}
Environment::~Environment(void)
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

   for(auto& animal: animals)
   {
       animal->update(dt); //in charge of movement and incrementation of attributes
       if (animal->isDead()) //gets rid of the animal in the attribute of the environement
       {
           animal = nullptr;
       }
       animals.erase(std::remove(animals.begin(), animals.end(), nullptr), animals.end());
   }

   for(auto& anthill: anthills)
   {
       anthill->update(dt); //in charge of updating the anthills
   }

   for(auto& phero: pheromones)
   {
       phero->update(dt); //in charge of movement and incrementation of attributes
       if (phero->isNegligeable()) //gets rid of the animal in the attribute of the environement
       {
           phero = nullptr;
       }
       pheromones.erase(std::remove(pheromones.begin(), pheromones.end(), nullptr), pheromones.end());
   }
}

void Environment::drawOn(sf::RenderTarget& targetWindow) const
{
   for(auto& food: foods)
   {
       food->drawOn(targetWindow); //operator overload: uses drawOn method of Food class
   }

   for(auto& animal: animals)
   {
       animal->drawOn(targetWindow); //operator overload: uses drawOn method of Animal class
   }

   for(auto& anthill: anthills)
   {
       anthill->drawOn(targetWindow); //operator overload: uses drawOn method of Anthill class
   }

   if(showPheromones)
   {
       for(auto& pheromone: pheromones)
       {
           pheromone->drawOn(targetWindow); //operator overload: uses drawOn method of Pheromone class
       }
   }
}

void Environment::reset()
{
   for(auto& animal: animals) //desaloccation of memory
   {
       delete animal;
       animal = nullptr;
   }
   for(auto& food: foods) //desaloccation of memory
   {
       delete food;
       food = nullptr;
   }
   for(auto& anthill: anthills) //desaloccation of memory
   {
       delete anthill;
       anthill = nullptr;
   }
   for(auto& pheromone: pheromones) //desaloccation of memory
   {
       delete pheromone;
       pheromone = nullptr;
   }
   animals.clear();
   foods.clear();
   anthills.clear();
   pheromones.clear();
}

//###PEUT FAIRE CRASHER???
Food* Environment::getClosestFoodForAnt(ToricPosition const& position)
{
    Food* foodptr(nullptr);
    double distance(toricDistance(position, foods[0]->getPosition()));
    if (foods.size() != 0)
    {
        for(size_t i(1); i < foods.size(); ++i)
        {
            if (toricDistance(position, foods[i]->getPosition()) < distance) //if the distance of the next food is lower than the distance of the last food
            {
                distance = toricDistance(position, foods[i]->getPosition());
                if (distance <= getAppConfig().ant_max_perception_distance) //if the food is in the radius of perception of the ant
                {
                    foodptr = foods[i];
                }
            }
        }
    }
    return foodptr;
}

Anthill* Environment::getAnthillForAnt(ToricPosition const& position, Uid anthillId)
{
    Anthill* anthillptr(nullptr); //if it doesn't find an anthill with the given anthillId, it will return nullptr
    //if (anthills.size() != 0)
    //{
    for(auto& anthill: anthills)
    {
        if ((anthill->uidIsEqual(anthillId)) and (toricDistance(position, anthill->getPosition()) < getAppConfig().ant_max_perception_distance) )
        //checks if the uids are equal and if the anthill is in the radius of perception of the ant
        {
            anthillptr = anthill;
        }

    }
    //}
    return anthillptr;
}

void Environment::addPheromone(Pheromone* phero)
{
   pheromones.push_back(phero);
}

bool Environment::togglePheromoneDisplay()
{
    return showPheromones=not showPheromones;
}

Quantities Environment::getPheromoneQuantitiesPerIntervalForAnt(const ToricPosition &position,
                                                   Angle direction_rad,
                                                   const Intervals &angles)
{
    Quantities Q(11,0);
    for(auto phero: pheromones)
    {
        if(toricDistance(position, phero->getPosition())<=getAppConfig().ant_smell_max_distance)
        {
            Angle beta((position.toricVector(phero->getPosition()).angle() - direction_rad) / DEG_TO_RAD);
            beta=fmod(beta,2*PI);
            if(beta<0)
            {
                beta+=360;
            }
            /*while(0>beta or beta>360)
            {
                if(beta>360)
                {
                    beta-=360;
                }

            }
            */
            Angle betaPrime(angles[0]);
            int indice(0);
            for(size_t i(1); i<angles.size(); ++i)
            {
                if(abs(angles[i]-beta)<abs(betaPrime-beta))
                {
                    betaPrime=angles[i];
                    indice=i;
                }
            }
            Q[indice]=phero->getQuantity();

        }
    }
    return Q;
}
