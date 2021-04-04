#include "Ant.hpp"


Ant::Ant(const Vec2d& pos, double LP, double LT, Uid id)
    :Animal::Animal(pos, LP, LT), anthillID(id)
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
