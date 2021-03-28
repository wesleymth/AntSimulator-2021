/*
 * POOSV 2020-21
 * @author:
 */

#include "Positionable.hpp"

Positionable::Positionable()
    :position(ToricPosition())
{
    //Done
}

Positionable::Positionable(const ToricPosition& T)
    :position(T)
{
    //Done
}

ToricPosition Positionable::getPosition() const{
    return position;
}

void Positionable::setPosition(const ToricPosition& pos){
    position=pos;
}

std::ostream& operator<<(std::ostream& out, Positionable const& P)
{
    return out << P.getPosition(); //uses the operator<< of ToricPosition
}

std::ostream& Positionable::display(std::ostream& out){
    return out << *this; //uses the external operator<< above
}

