/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

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
#include <unordered_map>
#include <fstream>
#include "AntKamikaze.hpp"

enum Temp {Cold, Normal, Hot};

/*!
 * @class Environment
 *
 * @inherits Drawable, Updatable
 *
 * @brief Represents and manages Environment and all compoments
 */
class Environment : public Updatable, public Drawable
{
private:
    std::vector<Animal*> animals;
    std::vector<Food*> foods;
    std::vector<Anthill*> anthills;
    std::vector<Pheromone*> pheromones;
    FoodGenerator foodGenerator;
    bool showPheromones;
    Temperature temperature;
    sf::Time totalTime;
    Temp temp;
    bool resetStatsNeeded;
public:
    /*!
     *  @brief default constructor
     *
     *  @note sets temperature to getAppConfig().temperature_initial
     */
    Environment();

    /*!
     *  @brief destructor that frees memory
     *
     *  @note uses reset()
     */
    ~Environment();

    /*!
     * @brief gets Temperature
     *
     * @return temperature in temperature form
     */
    Temperature getTemperature() const;


    /*!
     *  @brief returns pointer on closest food if it is in the perception radius
     *
     *  @return pointer on closest food
     */
    Food* getClosestFoodForAnt(ToricPosition const& position) const;

    /*!
     *  @brief returns pointer on closest animal if it is in the sight radius
     *
     *  @return pointer on closest animal
     */
    Animal* getClosestAnimalForAnimal(const Animal* currentInstance) const;

    /*!
     *  @brief returns pointer on anthill with the specific uid if it is in the perception radius
     *
     *  @return pointer on anthill
     */
    Anthill* getAnthillForAnt(ToricPosition const& position, Uid anthillUid) const;

    /*!
     *  @brief returns pointer on the closest anthill if it is in the perception radius
     *
     *  @return pointer on anthill
     */
    Anthill* getClosestAnthillForAnt(Ant * const &currentInstance) const;

    /*!
     *  @brief returns pointer on the closest pheromone if it is in the perception radius
     *
     *  @return pointer on pheromone
     */
    Pheromone* getClosestPheromoneForAnt(Ant * const &currentInstance) const;

    /*!
     *  @brief gives information of the closest pheromone that the kamikaze can interact with
     *
     *  @return bool if it was able to take any information
     */
    bool getPheromoneInfo(AntKamikaze* const &currentInstance) const;

    /*!
     *  @brief checks if the anthill still exists
     *
     *  @return true if the anthill is still in the environment
     */
    bool anthillStillAlive(Anthill* currentInstance) const;

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
     *
     *  @return the opposite value of current showPheromones
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

    /*!
     *  @brief fetches data for stats
     *
     *  @param title of the wanted graph
     *
     *  @return unordered map of information
     */
    std::unordered_map<std::string, double> fetchData(const std::string &title);

    /*!
     *  @brief gets all the environments anthill's
     *
     *  @param title of the wanted graph
     *
     *  @return a vector with "anthill#..." of the envrionment
     */
    std::vector<std::string> getAnthillsIds() const;

    /*!
     *  @brief creates file containing information to recreate current enironment with loadMap function
     */
    void saveMap() const;

    /*!
     *  @brief indicator of temperature
     *
     *  @return bool, true if temperature is outside of normal temperature
     */
    bool isTemperatureExtreme() const;

    /*!
     *  @brief Toggles between cold, normal and hot state for temperature
     */
    void toggleTemp();

    /*!
     *  @brief sets bool attribute resetsStatsNeeded to true
     */
    void StatsNeedReset();

    /*!
     *  @brief sets bool attribute resetsStatsNeeded to false
     */
    void StatsReset();

    /*!
     *  @brief getter for bool attribute resetsStatsNeeded
     *
     *  @return bool attribute resetsStatsNeeded
     */
    bool getStatsStatus() const;

};




#endif // ENVIRONMENT_HPP


