#include "Config.hpp"
#include <JSON/JSONSerialiser.hpp>
// window
Config::Config(std::string path) : mConfig(j::readFromFile(path))
    , simulation_debug(mConfig["debug"].toBool())
    , display_probs(mConfig["display probabilities"].toBool())
    , window_simulation_width(mConfig["window"]["simulation"]["width"].toDouble())
    , window_simulation_height(mConfig["window"]["simulation"]["height"].toDouble())
    , window_stats_width(mConfig["window"]["stats"]["width"].toDouble())
    , window_title(mConfig["window"]["title"].toString())
    , window_antialiasing_level(mConfig["window"]["antialiasing level"].toInt())

// stats
    , stats_refresh_rate(mConfig["stats"]["refresh rate"].toDouble())

// simulation

    , simulation_time_factor(mConfig["simulation"]["time"]["factor"].toDouble())
    , simulation_fixed_step(mConfig["simulation"]["time"]["fixed step"].toDouble())
    , simulation_time_max_dt(sf::seconds(mConfig["simulation"]["time"]["max dt"].toDouble()))
    , simulation_background(mConfig["simulation"]["background"].toString())
    , simulation_debug_background(mConfig["simulation"]["debug background"].toString())
    , simulation_size(mConfig["simulation"]["size"].toInt())
    , world_size(mConfig["world"]["size"].toInt())
    , map_name(mConfig["world"]["map name"].toString())
//simulation (ants)
    , beta_d(mConfig["environment"]["beta_d"].toDouble())
    , q_zero(mConfig["environment"]["q_zero"].toDouble())
    , alpha(mConfig["environment"]["alpha"].toInt())
    , temperature_initial(mConfig["environment"]["temperature initial"].toDouble())	, temperature_delta(mConfig["environment"]["temperature delta"].toDouble())
    , temperature_min(mConfig["environment"]["temperature min"].toDouble())
    , temperature_max(mConfig["environment"]["temperature max"].toDouble())
//food generator
    ,food_generator_delta(mConfig["food"]["generator"]["delta"].toDouble())

//food
    ,food_min_qty(mConfig["food"]["min qty"].toDouble())
    ,food_max_qty(mConfig["food"]["max qty"].toDouble())
    ,food_texture(mConfig["food"]["texture"].toString())

//pheromone
    ,pheromone_threshold(mConfig["pheromone"]["treshold"].toDouble())
    ,pheromone_evaporation_rate(mConfig["pheromone"]["evaporation rate"].toDouble())
    ,pheromone_test_density(mConfig["pheromone"]["test density"].toDouble())
    ,pheromone_temperature_threshold(mConfig["pheromone"]["temperature threshold"].toDouble())
// anthill
    ,anthill_spawn_delay(mConfig["anthill"]["spawn delay"].toDouble())
    ,anthill_worker_prob_default(mConfig["anthill"]["default worker prob"].toDouble())
    ,anthill_texture(mConfig["anthill"]["texture"].toString())

//animal
    ,animal_next_rotation_delay(mConfig["animal"]["next rotation delay"].toDouble())
    ,animal_sight_distance(mConfig["animal"]["sight distance"].toDouble())
    ,animal_default_speed(mConfig["animal"]["default speed"].toDouble())
    ,animal_default_lifespan(mConfig["animal"]["default lifespan"].toDouble())
    ,animal_default_texture(mConfig["animal"]["default texture"].toString())

// ants
    ,ant_speed(mConfig["ant"]["speed"].toDouble())
    ,ant_attack_delay(mConfig["ant"]["attack"] ["delay"].toDouble())
    ,ant_smell_max_distance(mConfig["ant"]["smell"]["distance"].toDouble())
    ,ant_pheromone_density(mConfig["ant"]["pheromone"]["density"].toDouble())
    ,ant_pheromone_energy(mConfig["ant"]["pheromone"]["energy"].toDouble())
    ,ant_max_food(mConfig["ant"]["max food"].toDouble())
    ,ant_max_perception_distance(mConfig["ant"]["max perception distance"].toDouble())
    ,ant_radius(mConfig["ant"]["radius"].toDouble())

// worker ants
    , ant_worker_hp(mConfig["ant"]["worker"]["hp"].toInt())
    , ant_worker_lifespan(mConfig["ant"]["worker"]["lifespan"].toInt())
    , ant_worker_strength(mConfig["ant"]["worker"]["strength"].toInt())
    , ant_worker_texture(mConfig["ant"]["worker"]["texture"].toString())

//soldier  ants
    , ant_soldier_hp(mConfig["ant"]["soldier"]["hp"].toInt())
    , ant_soldier_lifespan(mConfig["ant"]["soldier"]["lifespan"].toInt())
    , ant_soldier_strength(mConfig["ant"]["soldier"]["strength"].toInt())
    , ant_soldier_texture(mConfig["ant"]["soldier"]["texture"].toString())
//termites
    , termite_hp(mConfig["termite"]["hp"].toInt())
    , termite_lifespan(mConfig["termite"]["lifespan"].toInt())
    , termite_strength(mConfig["termite"]["strength"].toInt())
    , termite_speed(mConfig["termite"]["speed"].toDouble())
    , termite_attack_delay(mConfig["termite"]["attack delay"].toDouble())

    , termite_texture(mConfig["termite"]["texture"].toString())

//DRAWING CONSTANTS
    ,DEFAULT_ANT_SIZE(mConfig["ant"]["DEFAULT_ANT_SIZE"].toDouble())
    ,DEFAULT_TERMITE_SIZE(mConfig["termite"]["DEFAULT_TERMITE_SIZE"].toDouble())
    ,DEFAULT_ANTHILL_SIZE(mConfig["anthill"]["DEFAULT_ANTHILL_SIZE"].toDouble())
    ,DEFAULT_FOOD_SIZE(mConfig["food"]["DEFAULT_FOOD_SIZE"].toDouble())

  //ANIMAL
    ,DEFAULT_ANIMAL_HP(mConfig["animal"]["DEFAULT_ANIMAL_HP"].toDouble())
    ,DEFAULT_ANIMAL_LIFE(mConfig["animal"]["DEFAULT_ANIMAL_LIFE"].toDouble())

  //FOOD
    ,DEFAULT_FOOD_QUANTITY(mConfig["food"]["DEFAULT_FOOD_QUANTITY"].toDouble())
    ,FOOD_DRYING_CONSTANT(mConfig["food"]["FOOD_DRYING_CONSTANT"].toDouble())

  //PHEROMONE
    ,DEFAULT_PHEROMONE_QUANTITY(mConfig["ant"]["pheromone"]["DEFAULT_PHEROMONE_QUANTITY"].toDouble())

  //LOADER
    ,ERROR_LOADER_INCORRECT_ARGUMENTS(mConfig["loader"]["ERROR_LOADER_INCORRECT_ARGUMENTS"].toInt())

  //QUEEN
    ,DEFAULT_QUEEN_SIZE(mConfig["ant"]["queen"]["DEFAULT_QUEEN_SIZE"].toDouble())
    ,DEFAULT_QUEEN_STRENGTH(mConfig["ant"]["queen"]["DEFAULT_QUEEN_STRENGTH"].toDouble())
    ,DEFAULT_QUEEN_HP(mConfig["ant"]["queen"]["DEFAULT_QUEEN_HP"].toDouble())
    ,DEFAULT_QUEEN_LIFE(mConfig["ant"]["queen"]["DEFAULT_QUEEN_LIFE"].toDouble())
    ,ANT_QUEEN_COST(mConfig["ant"]["queen"]["ANT_QUEEN_COST"].toDouble())
    ,DEFAULT_COLONY_DISTANCE(mConfig["ant"]["queen"]["DEFAULT_COLONY_DISTANCE"].toDouble())
    ,DEFAULT_FOOD_COLONY(mConfig["ant"]["queen"]["DEFAULT_FOOD_COLONY"].toDouble())

  //ANTHILLS
    ,DEFAULT_UID(mConfig["anthill"]["DEFAULT_UID"].toDouble())
    ,ANT_WORKER_COST(mConfig["anthill"]["ANT_WORKER_COST"].toDouble())
    ,ANT_SOLDIER_COST(mConfig["anthill"]["ANT_SOLDIER_COST"].toDouble())
    ,ANT_SCOUT_COST(mConfig["anthill"]["ANT_SCOUT_COST"].toDouble())
    ,ANT_KAMIKAZE_COST(mConfig["anthill"]["ANT_KAMIKAZE_COST"].toDouble())
    ,HUNGER_DAMAGE_PER_TIME(mConfig["anthill"]["HUNGER_DAMAGE_PER_TIME"].toDouble())
    ,DEFAULT_ANTHILL_HEALTHPOINTS(mConfig["anthill"]["DEFAULT_ANTHILL_HEALTHPOINTS"].toDouble())
  ,DEFAULT_ANTHILL_REGENERATION(mConfig["anthill"]["DEFAULT_ANTHILL_REGENERATION"].toDouble())
  ,ANTHILL_FOOD_COMSUMPTION(mConfig["anthill"]["ANTHILL_FOOD_COMSUMPTION"].toDouble())
  ,FOOD_NEEDED_FOR_WAR(mConfig["anthill"]["FOOD_NEEDED_FOR_WAR"].toDouble())
  ,DEFAULT_WAR_TIME(mConfig["anthill"]["DEFAULT_WAR_TIME"].toDouble())
  ,DEFAULT_ANTHILL_TERRITORY(mConfig["anthill"]["DEFAULT_ANTHILL_TERRITORY"].toDouble())
  ,DEFAULT_ANTHILL_FOODSTOCK(mConfig["anthill"]["DEFAULT_ANTHILL_FOODSTOCK"].toDouble())

  //ANT GENERATION PROBABILITIES
  ,WAR_WORKER_PROB(mConfig["anthill"]["generation probabilities"]["WAR_WORKER_PROB"].toDouble())
  ,WAR_SOLDIER_PROB(mConfig["anthill"]["generation probabilities"]["WAR_SOLDIER_PROB"].toDouble())
  ,WAR_SCOUT_PROB(mConfig["anthill"]["generation probabilities"]["WAR_SCOUT_PROB"].toDouble())
  ,WAR_KAMIKAZE_PROB(mConfig["anthill"]["generation probabilities"]["WAR_KAMIKAZE_PROB"].toDouble())
  ,PROSPER_WORKER_PROB(mConfig["anthill"]["generation probabilities"]["PROSPER_WORKER_PROB"].toDouble())
  ,PROSPER_SOLDIER_PROB(mConfig["anthill"]["generation probabilities"]["PROSPER_SOLDIER_PROB"].toDouble())
  ,PROSPER_SCOUT_PROB(mConfig["anthill"]["generation probabilities"]["PROSPER_SCOUT_PROB"].toDouble())
  ,PROSPER_KAMIKAZE_PROB(mConfig["anthill"]["generation probabilities"]["PROSPER_KAMIKAZE_PROB"].toDouble())

  //ANT KAMIKAZE
  ,ANT_KAMAIKAZE_HP(mConfig["ant"]["kamikaze"]["ANT_KAMAIKAZE_HP"].toDouble())
  ,ANT_KAMAIKAZE_LIFE(mConfig["ant"]["kamikaze"]["ANT_KAMAIKAZE_LIFE"].toDouble())
  ,ANT_KAMAIKAZE_STRENGTH(mConfig["ant"]["kamikaze"]["ANT_KAMAIKAZE_STRENGTH"].toInt())
  ,ANT_KAMAIKAZE_BLOW_UP_DAMAGE(mConfig["ant"]["kamikaze"]["ANT_KAMAIKAZE_BLOW_UP_DAMAGE"].toInt())
  ,ANT_KAMAIKAZE_SPRITE(mConfig["ant"]["kamikaze"]["ANT_KAMAIKAZE_SPRITE"].toString())

  //ANT SCOUT
  ,ANT_SCOUT_STRENGTH(mConfig["ant"]["scout"]["ANT_SCOUT_STRENGTH"].toInt())
  ,ANT_SCOUT_HP(mConfig["ant"]["scout"]["ANT_SCOUT_HP"].toDouble())
  ,ANT_SCOUT_LIFE(mConfig["ant"]["scout"]["ANT_SCOUT_LIFE"].toDouble())
  ,ANT_SCOUT_SPREAD_INPHO_TIME(mConfig["ant"]["scout"]["ANT_SCOUT_SPREAD_INPHO_TIME"].toDouble())
  ,ANT_SCOUT_SPRITE(mConfig["ant"]["scout"]["ANT_SCOUT_SPRITE"].toString())

  //TEMPERATURE
  ,COLD_TEMPERATURE(mConfig["environment"]["COLD_TEMPERATURE"].toDouble())
  ,HOT_TEMPERATURE(mConfig["environment"]["HOT_TEMPERATURE"].toDouble())
  ,TEMPERATURE_DAMAGE_RATE(mConfig["environment"]["TEMPERATURE_DAMAGE_RATE"].toDouble())
  ,TEMPERATURE_SIN_FACTOR(mConfig["environment"]["TEMPERATURE_SIN_FACTOR"].toDouble())


{ }



// for debugging purposes
void Config::switchDebug()
{
    mConfig["debug"] = j::boolean(!mConfig["debug"].toBool());
    simulation_debug = mConfig["debug"].toBool();
}

bool Config::getDebug()
{
    return simulation_debug;
}

bool Config::getProbaDebug()
{
    return display_probs;
}

void Config::switchProbaDebug()
{
    mConfig["display probabilities"] = j::boolean(!mConfig["display probabilities"].toBool());
    display_probs = mConfig["display probabilities"].toBool();
}
