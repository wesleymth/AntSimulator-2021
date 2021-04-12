#include "Environment.hpp"
#include "../Application.hpp"

Environment::Environment()
{
    //Done
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
           animals.erase(std::remove(animals.begin(), animals.end(), nullptr), animals.end());
       }
   }

   for(auto& anthill: anthills)
   {
       anthill->update(dt); //in charge of updating the anthills
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
   animals.clear();
   foods.clear();
   anthills.clear();
}

//###PEUT FAIRE CRASHER???
Food* Environment::getClosestFoodForAnt(ToricPosition const& position)
{
    Food* foodptr(nullptr);
    double distance(toricDistance(position, foods[0]->getPosition()));
    //if (foods.size() != 0)
    //{
        for(auto& food: foods)
        {
            if (toricDistance(position, food->getPosition()) < distance) //if the distance of the next food is lower than the distance of the last food
            {
                distance = toricDistance(position, food->getPosition());
                if (distance < getAppConfig().ant_max_perception_distance) //if the food is in the radius of perception of the ant
                {
                    foodptr = food;
                }
            }
        }
    //}
    return foodptr;
}

Anthill* Environment::getAnthillForAnt(ToricPosition const& position, Uid anthillId)
{
    Anthill* anthillptr(nullptr); //if it doesn't find an anthill with the given anthillId, it will return nullptr
    //if (anthills.size() != 0)
    //{
    for(auto& anthill: anthills)
        {
            if (anthill->uidIsEqual(anthillId)) //checks if the uids are equal
            {
                if (toricDistance(position, anthill->getPosition()) < getAppConfig().ant_max_perception_distance) //if the anthill is in the radius of perception of the ant
                {
                    anthillptr = anthill;
                }
            }
        }
    //}
    return anthillptr;
}
