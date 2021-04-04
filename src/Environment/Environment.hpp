#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "Animal.hpp"
#include "Food.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "FoodGenerator.hpp"
#include "../Interface/Updatable.hpp"

class Environment : public Updatable
{
private:
   std::vector<Animal*> animals;
   std::vector<Food*> foods;
   FoodGenerator foodGenerator;
public:
   /*!
    *  @brief default constructor
    */
   Environment();

   /*!
    *  @brief adds animal to current environment
    *
    *  @param Animal* pointer to animal to add
    */
   void addAnimal(Animal*);

   /*!
    *  @brief adds food to current environment
    *
    *  @param Food* pointer to food to add
    */
   void addFood(Food*);

   /*!
    *  @brief in charge of changing animals a a set time interval
    *
    *  @param dt time interval
    *
    *  @note updates the generation of foods and the movement/life of animals
    *  @note if animal is dead gets rid of it as well
    */
   void update(sf::Time dt);

   /*!
    *  @brief draws environment on application
    *
    *  @param targetWindow reference
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

   /*!
    *  @brief in order to stop affectations of environment
    */
   void operator=(Environment const&) = delete;
};

#endif // ENVIRONMENT_HPP


