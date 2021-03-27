#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "Animal.hpp"
#include "Food.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "FoodGenerator.hpp"

class Environment
{
private:
   std::vector<Animal*> animals;
   std::vector<Food*> foods;
   FoodGenerator foodGenerator;
public:
   Environment();

   /*!
    *  @brief adds animal to current environment
    *
    *  @param pointer to animal to add
    */
   void addAnimal(Animal*);

   /*!
    *  @brief adds food to current environment
    *
    *  @param pointer to food to add
    */
   void addFood(Food*);

   /*!
    *  @brief in charge of changing animals a a set time interval
    *
    *  @param time interval
    */
   void update(sf::Time dt);

   /*!
    *  @brief draws environment on application
    *
    *  @param reference window to draw on
    */
   void drawOn(sf::RenderTarget& targetWindow) const;

   /*!
    *  @brief resets all food and animals in environement
    */
   void reset();

   /*!
    *  @brief in order to stop copies of environmnet
    */
   Environment(Environment const&) = delete;

   //manque affectattion
};

#endif // ENVIRONMENT_HPP


