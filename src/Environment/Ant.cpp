#include "Ant.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

Ant::Ant(const Vec2d& pos, double HP, double LT, Uid id)
    :Animal::Animal(pos, HP, LT), anthillID(id)
{
    //Done
}

Ant::Ant(const Vec2d& pos, Uid id)
    :Animal::Animal(pos), anthillID(id) //calls constructor of Animal using only a position
{
    //Done
}

Ant::Ant()
    :Animal::Animal(), anthillID() //calls default constructor of Animal
{
    //Done
}

double Ant::getSpeed() const
{
    return getAppConfig().ant_speed;
}
