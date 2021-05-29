/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#include "RegularPheromone.hpp"

RegularPheromone::RegularPheromone()
    :Pheromone()
{
    //Done
}

RegularPheromone::RegularPheromone(const Vec2d& vect, Quantity quant)
    :Pheromone(ToricPosition(vect), quant)
{
    //Done
}

RegularPheromone::RegularPheromone( const ToricPosition& TP, Quantity quant)
    :Pheromone(TP,quant)
{
    //Done
}

bool RegularPheromone::interact() const
{
    return false;
}

Anthill* RegularPheromone::getEnemy() const
{
    return nullptr;
}

ToricPosition RegularPheromone::getEnemyPosition() const
{
    return ToricPosition(); //its ugly yeah we know
}
