#include "Environment.hpp"

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

void Environment::update(sf::Time dt)
{
   foodGenerator.update(dt);       //######

   for(auto& animal: animals)
   {
       animal->move(dt);
       if (animal->isDead())
       {
           animal = nullptr;
           animals.erase(std::remove(animals.begin(), animals.end(), nullptr), animals.end());
       }
   }
}

void Environment::drawOn(sf::RenderTarget& targetWindow) const
{
   for(auto& food: foods)
   {
       food->drawOn(targetWindow);  //################
   }

   for(auto& animal: animals)
   {
       animal->drawOn(targetWindow);    //################
   }
}

void Environment::reset()
{
   for(auto& animal: animals) //desaloccation of memeory        #######
   {
       delete animal;
       animal = nullptr;
   }
   for(auto& food: foods) //desaloccation of memeory        ######
   {
       delete food;
       food = nullptr;
   }
   animals.clear();
   foods.clear();
}


