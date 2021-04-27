/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#include "FoodGenerator.hpp"
#include "Application.hpp"
#include "Random/Random.hpp"

FoodGenerator::FoodGenerator()
    :timeLastFood(sf::Time::Zero) //sets the timeLastFood to 0
{
    //Done
}

void FoodGenerator::update(sf::Time dt){

    timeLastFood += dt; //increments timeLastFood by time passed since last update

    if (timeLastFood > sf::seconds(getAppConfig().food_generator_delta)) //if it has been a while since a food was generated
    {
        timeLastFood = sf::Time::Zero; //sets back timeLastFood attribute to 0
        //memory allocation of pointer using "new"
        //normal function to generate random value using normal law of a mean and variance
        getAppEnv().addFood(new Food(Vec2d(normal((getAppConfig().simulation_size/2), (getAppConfig().simulation_size*getAppConfig().simulation_size/16)),
                                           (normal((getAppConfig().simulation_size/2), (getAppConfig().simulation_size*getAppConfig().simulation_size/16)))),
                                     (uniform(getAppConfig().food_min_qty,getAppConfig().food_max_qty))));
    }

}
