#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "Animal.hpp"
#include "Food.hpp"
#include "Anthill.hpp"
#include "Pheromone.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "FoodGenerator.hpp"
#include "../Interface/Updatable.hpp"
#include "../Interface/Drawable.hpp"

class Environment : public Updatable, public Drawable
{
private:
   std::vector<Animal*> animals;
   std::vector<Food*> foods;
   std::vector<Anthill*> anthills;
   std::vector<Pheromone*> pheromones;
   FoodGenerator foodGenerator;
   bool showPheromones;
public:
   /*!
    *  @brief default constructor
    */
   Environment();

   /*!
    *  @brief adds animal to current environment
    *
    *  @param animal pointer to add
    */
   void addAnimal(Animal* animal);

   /*!
    *  @brief adds food to current environment
    *
    *  @param food pointer to add
    */
   void addFood(Food* food);

   /*!
    *  @brief adds anthill to current environment
    *
    *  @param anthill pointer to add
    */
   void addAnthill(Anthill* anthill);

   /*!
    *  @brief adds pheromone to current environment
    *
    *  @param pheromone pointer to add
    */
   void addPheromone(Pheromone *phero);

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
    *  @brief
    */
   Food* getClosestFoodForAnt(ToricPosition const& position);

   /*!
    *  @brief
    */
   Anthill* getAnthillForAnt(ToricPosition const& position, Uid anthillId);

   /*!
    *  @brief in order to stop copies of environmnet
    */
   Environment(Environment const&) = delete;

   /*!
    *  @brief in order to stop affectations of environment
    */
   void operator=(Environment const&) = delete;



   bool togglePheromoneDisplay();
};

#endif // ENVIRONMENT_HPP


