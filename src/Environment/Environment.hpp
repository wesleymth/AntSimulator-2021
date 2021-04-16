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
    *  @brief destructor that frees memory
    *
    *  @note uses reset()
    */
   ~Environment();

   /*!
    *  @brief returns pointer on closest food if it is in the perception radius
    */
   Food* getClosestFoodForAnt(ToricPosition const& position);

   /*!
    *  @brief returns pointer on anthill with the specific uid if it is in the perception radius
    *
    *  @return pointer on food
    */
   Anthill* getAnthillForAnt(ToricPosition const& position, Uid anthillUid);

   /*!
    *  @brief adds animal to current environment
    *
    *  @param animal pointer to add
    *
    *  @return pointer on Anthill
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
    *  @brief in charge of changing all udatable entities at a set time interval
    *
    *  @param dt time interval
    *
    *  @note updates the generation of foods and the movement/life of animals
    *  @note if entity is dead or no longer useful, gets rid of it as well
    */
   void update(sf::Time dt) override;

   /*!
    *  @brief draws environment on application
    *
    *  @param targetWindow reference
    *
    *  @note calls on drawOn function of all elements
    */
   void drawOn(sf::RenderTarget& targetWindow) const override;

   /*!
    *  @brief resets all food, pheromones and animals in environement
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

   /*!
    *  @brief toggles display of pheromones
    */
   bool togglePheromoneDisplay();

   /*!
    *  @brief determines quantity of pheromones in each interval within smell distance
    *
    *  @param position constant ToricPosition reference
    *  @param direction_angle Angle
    *  @param angles constant Intervals reference
    *
    *  @return Quantities of pheromones
    */
   Quantities getPheromoneQuantitiesPerIntervalForAnt(const ToricPosition &position,
                                                      Angle direction_rad,
                                                      const Intervals &angles);
};

#endif // ENVIRONMENT_HPP


