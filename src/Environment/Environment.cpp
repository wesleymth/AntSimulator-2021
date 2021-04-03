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
   foodGenerator.update(dt); //operator overload: uses update method of FoodGenerator class

   for(auto& animal: animals)
   {
       animal->move(dt); //makes the animal move automatically
       if (animal->isDead()) //gets rid of the animal in the attribute of the environement
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
       food->drawOn(targetWindow); //operator overload: uses drawOn method of Food class
   }

   for(auto& animal: animals)
   {
       animal->drawOn(targetWindow); //operator overload: uses drawOn method of Animal class
   }
}

void Environment::reset()
{
   for(auto& animal: animals) //desaloccation of memeory
   {
       delete animal;
       animal = nullptr;
   }
   for(auto& food: foods) //desaloccation of memeory
   {
       delete food;
       food = nullptr;
   }
   animals.clear();
   foods.clear();
}


