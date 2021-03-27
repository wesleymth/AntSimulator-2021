#include "FoodGenerator.hpp"
#include "Application.hpp"
#include "Random/Random.hpp"

FoodGenerator::FoodGenerator()
    :timeLastFood(sf::Time::Zero)
{
    //Done.
}

void FoodGenerator::update(sf::Time dt){

    timeLastFood += dt;

    if (timeLastFood > sf::seconds(getAppConfig().food_generator_delta)){
        timeLastFood = sf::Time::Zero;
        /*
        double x (normal((getAppConfig().simulation_size/2), (getAppConfig().simulation_size*getAppConfig().simulation_size/16)));
        double y (normal((getAppConfig().simulation_size/2), (getAppConfig().simulation_size*getAppConfig().simulation_size/16)));
        double qty (uniform(getAppConfig().food_min_qty,getAppConfig().food_max_qty));
        Food* ptr(nullptr);
        ptr = new Food(Vec2d(x,y),qty);
        getAppEnv().addFood(ptr);
        */
        getAppEnv().addFood(new Food(Vec2d(normal((getAppConfig().simulation_size/2), (getAppConfig().simulation_size*getAppConfig().simulation_size/16)),
                                           (normal((getAppConfig().simulation_size/2), (getAppConfig().simulation_size*getAppConfig().simulation_size/16)))),
                                     (uniform(getAppConfig().food_min_qty,getAppConfig().food_max_qty))));
    }

}
