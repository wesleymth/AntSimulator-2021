#ifndef FOODGENERATOR_HPP
#define FOODGENERATOR_HPP
#include <SFML/Graphics.hpp>
#include "../Interface/Updatable.hpp"

class FoodGenerator : public Updatable
{
public:

    /*!
     * @brief default constructor
     */
    FoodGenerator();

    /*!
     * @brief adds new foods periodically
     *
     * @param dt time passed since last update
     *
     * @note uses the Random class to generate random values
     * @note uses getAppConfig() for specific values
     * @note memory allocation of food pointer
     * @note uses getAppEnv() to tap into the current environment and add the pointer to its foods
     */
    void update(sf::Time dt);

private:
    sf::Time timeLastFood;
};

#endif // FOODGENERATOR_HPP
