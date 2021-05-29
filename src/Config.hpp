/*
 * prjsv 2016-21
 * Marco Antognini & Jamila Sam
 */

#ifndef INFOSV_CONFIG_HPP
#define INFOSV_CONFIG_HPP

#include <string>
#include "JSON/JSON.hpp"
#include <SFML/Graphics.hpp>




class Config
{
private:
    j::Value mConfig;
    bool simulation_debug;
    bool display_probs;

public:
    Config(std::string path);

    // enables / disables debug mode
    void switchDebug();
    void switchProbaDebug();
    bool getDebug();
    bool getProbaDebug();

    // returns read
    j::Value& getJsonRead()
    {
        return mConfig;
    }

    j::Value const& getJsonRead() const
    {
        return mConfig;
    }


    //window
    const double window_simulation_width;
    const double window_simulation_height;
    const double window_stats_width;
    const std::string  window_title;
    const int window_antialiasing_level;


    // stats
    const double stats_refresh_rate;
    const std::string stats_log_folder = "logs/";
    const std::string stats_log_prefix = "log_";
    const std::string stats_log_header = "# Plot with GNUPLOT : gnuplot -e \"plot for [i=1:6] 'log_0.txt' u i w l title columnheader(i)\"";

    // debug
    const sf::Color debug_text_color = sf::Color::White;
    const size_t default_debug_text_size = 20;


    //simulation (general)

    const double  simulation_time_factor;
    const double  simulation_fixed_step;
    const sf::Time  simulation_time_max_dt;
    const std::string simulation_background;
    const std::string simulation_debug_background;
    const int simulation_size;
    const int world_size;
    const std::string map_name;

    // simulation (ants)
    const double  beta_d;
    const double  q_zero;
    const int     alpha;
    const double temperature_initial;
    const double temperature_delta;
    const double temperature_min;
    const double temperature_max;



    // food generator
    const double food_generator_delta;

    //food

    const double food_min_qty;
    const double food_max_qty;
    const std::string food_texture;

    //pheromone
    const double pheromone_threshold;
    const double pheromone_evaporation_rate;
    const double pheromone_test_density;
    const double pheromone_temperature_threshold;

    // anthills
    const double anthill_spawn_delay;
    const double anthill_worker_prob_default;
    const std::string anthill_texture;

    // animal
    const double animal_next_rotation_delay;
    const double animal_sight_distance;
    const double animal_default_speed;
    const double animal_default_lifespan;
    const std::string animal_default_texture;

    //ants
    const double ant_speed;
    const double ant_attack_delay;
    const double ant_smell_max_distance;
    const double ant_pheromone_density;
    const double ant_pheromone_energy;
    const double ant_max_food;
    const double ant_max_perception_distance;
    const double ant_radius;


    //worker ants
    const int ant_worker_hp;
    const int ant_worker_lifespan;
    const int ant_worker_strength;
    const std::string ant_worker_texture;

    //soldier ants
    const int ant_soldier_hp;
    const int ant_soldier_lifespan;
    const int ant_soldier_strength;
    const std::string ant_soldier_texture;

    // termites
    const int termite_hp;
    const int termite_lifespan;
    const int termite_strength;
    const double termite_speed;
    const double termite_attack_delay;
    const std::string termite_texture;

    //DRAWING CONSTANTS
    double const DEFAULT_ANT_SIZE;
    double const DEFAULT_TERMITE_SIZE;
    double const DEFAULT_ANTHILL_SIZE;
    double const DEFAULT_FOOD_SIZE;

    //ANIMAL
    double const DEFAULT_ANIMAL_HP;
    double const DEFAULT_ANIMAL_LIFE;

    //FOOD
    double const DEFAULT_FOOD_QUANTITY;
    double const FOOD_DRYING_CONSTANT;

    //PHEROMONE
    double const DEFAULT_PHEROMONE_QUANTITY;

    //LOADER
    const int ERROR_LOADER_INCORRECT_ARGUMENTS;

    //QUEEN
    double const DEFAULT_QUEEN_SIZE;
    double const DEFAULT_QUEEN_STRENGTH;
    double const DEFAULT_QUEEN_HP;
    double const DEFAULT_QUEEN_LIFE;
    const double ANT_QUEEN_COST;
    double const DEFAULT_COLONY_DISTANCE;
    double const DEFAULT_FOOD_COLONY;

    //ANTHILLS
    double const DEFAULT_UID;
    const double ANT_WORKER_COST;
    const double ANT_SOLDIER_COST;
    const double ANT_SCOUT_COST;
    const double ANT_KAMIKAZE_COST;
    const double HUNGER_DAMAGE_PER_TIME;
    const double DEFAULT_ANTHILL_HEALTHPOINTS;
    const double DEFAULT_ANTHILL_REGENERATION;
    const double ANTHILL_FOOD_COMSUMPTION;
    const double FOOD_NEEDED_FOR_WAR;
    const double DEFAULT_WAR_TIME;
    const double DEFAULT_ANTHILL_TERRITORY;
    const double DEFAULT_ANTHILL_FOODSTOCK;

    //ANT GENERATION PROBABILITIES
    const double WAR_WORKER_PROB;
    const double WAR_SOLDIER_PROB;
    const double WAR_SCOUT_PROB;
    const double WAR_KAMIKAZE_PROB;
    const double PROSPER_WORKER_PROB;
    const double PROSPER_SOLDIER_PROB;
    const double PROSPER_SCOUT_PROB;
    const double PROSPER_KAMIKAZE_PROB;

    //ANT KAMIKAZE
    double const ANT_KAMAIKAZE_HP;
    double const ANT_KAMAIKAZE_LIFE;
    int const ANT_KAMAIKAZE_STRENGTH;
    int const ANT_KAMAIKAZE_BLOW_UP_DAMAGE;
    const std::string ANT_KAMAIKAZE_SPRITE;

    //ANT SCOUT
    int const ANT_SCOUT_STRENGTH;
    double const ANT_SCOUT_HP;
    double const ANT_SCOUT_LIFE;
    double const ANT_SCOUT_SPREAD_INPHO_TIME ;
    const std::string ANT_SCOUT_SPRITE;

    //TEMPERATURE
    double const COLD_TEMPERATURE;
    double const HOT_TEMPERATURE;
    double const TEMPERATURE_DAMAGE_RATE;
    double const TEMPERATURE_SIN_FACTOR;

};

#endif // INFOSV_CONFIG_HPP

