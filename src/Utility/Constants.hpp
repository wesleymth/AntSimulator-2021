/*
 * prjsv 2015-21
 * Marco Antognini & Jamila Sam
 */

#ifndef INFOSV_CONSTANTS_HPP
#define INFOSV_CONSTANTS_HPP

#include <string>
#include <unordered_map>

// Numerical constants
double const DEG_TO_RAD = 0.0174532925; ///< Degree to Radian conversion constant
double const TAU = 6.283185307;         ///< TAU constant (= 2 * PI)
double const PI = 3.141592654;          ///< PI constant
double const EPSILON = 1e-8;            ///< a small epsilon value

//DRAWING CONSTANTS
double const DEFAULT_ANT_SIZE = 20.0;   ///< drawing constant for ants
double const DEFAULT_TERMITE_SIZE = 20.0;   ///<  constant for
double const DEFAULT_ANTHILL_SIZE = 50;
double const DEFAULT_FOOD_SIZE = 8;

//ANIMAL
double const DEFAULT_ANIMAL_HP = 1.0;   ///<  constant for animals
double const DEFAULT_ANIMAL_LIFE = 1.0; ///<  constant for animals

//FOOD
double const DEFAULT_FOOD_QUANTITY = 0;

//PHEROMONE
double const DEFAULT_PHEROMONE_QUANTITY = 0;

//LOADER
const int ERROR_LOADER_INCORRECT_ARGUMENTS(1699); ///random int

//QUEEN
double const DEFAULT_QUEEN_SIZE = 60.0;   ///< drawing constant
double const DEFAULT_QUEEN_STRENGTH = 4;   ///<  constant for
double const DEFAULT_QUEEN_HP = 300;   ///<  constant for
double const DEFAULT_QUEEN_LIFE = 30000; ///<  constant for
const double ANT_QUEEN_COST = 100;
double const DEFAULT_COLONY_DISTANCE = 200; ///<  constant for
double const DEFAULT_FOOD_COLONY = 200; ///<  constant for

//ANTHILLS
double const DEFAULT_UID = 0;
const double ANT_WORKER_COST = 10;
const double ANT_SOLDIER_COST = 10;
const double ANT_SCOUT_COST = 10;
const double ANT_KAMIKAZE_COST = 10;
const double HUNGER_DAMAGE_PER_TIME = 1;
const double DEFAULT_ANTHILL_HEALTHPOINTS = 100;
const double DEFAULT_ANTHILL_REGENERATION = 1;

//ANT GENERATION PROBABILITIES
const double WAR_WORKER_PROB = 0.1;
const double WAR_SOLDIER_PROB = 0.4;
const double WAR_SCOUT_PROB = 0.1;
const double WAR_KAMIKAZE_PROB = 0.4;

const double PROSPER_WORKER_PROB = 0.5;
const double PROSPER_SOLDIER_PROB = 0.1;
const double PROSPER_SCOUT_PROB = 0.3;
const double PROSPER_KAMIKAZE_PROB = 0.1;

//ANT KAMIKAZE
double const ANT_KAMAIKAZE_HP = 20;
double const ANT_KAMAIKAZE_LIFE = 10000;
int const ANT_KAMAIKAZE_STRENGTH = 0;
int const ANT_KAMAIKAZE_BLOW_UP_DAMAGE = 100;
const std::string ANT_KAMAIKAZE_SPRITE = "green_ant.png";

//ANT SCOUT
int const ANT_SCOUT_STRENGTH = 4;
double const ANT_SCOUT_HP = 20;
double const ANT_SCOUT_LIFE = 10000;
double const ANT_SCOUT_SPREAD_INPHO_TIME = 4;
const std::string ANT_SCOUT_SPRITE = "grey_ant.png";

//TEMPERATURE
double const COLD_TEMPERATURE = 0;
double const HOT_TEMPERATURE = 40;
double const TEMPERATURE_DAMAGE_RATE = 0.5;
double const TEMPERATURE_SIN_FACTOR = 0.5;

// Define resources location
std::string const RES_LOCATION = "../res/";

// Define the location of the config file
std::string const DEFAULT_CFG = "app.json";

// Define the location of the font file (could be in the config instead of here)
std::string const APP_FONT_LOCATION = RES_LOCATION + "sansation.ttf";

/// Loader parameters
std::string const MAP_NAME = "MAP_NAME";
// Stats titles
namespace s
{

std::string const GENERAL      = "general";
std::string const WORKER_ANTS  = "worker ants";
std::string const SOLDIER_ANTS = "soldier ants";
std::string const TERMITES     = "termites";
std::string const ANTHILLS     = "anthills";
std::string const FOOD         = "food";
std::string const TEMPERATURE  = "temperature";
} // s

#endif // INFOSV_CONSTANTS_HPP
