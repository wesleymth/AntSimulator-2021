/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
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

Positionable::Positionable(const Vec2d& pos)
    :position(ToricPosition(pos))
{
    //Done
}

ToricPosition Positionable::getPosition() const
{
    return position;
}

void Positionable::setPosition(const ToricPosition& pos)
{
    position=pos;
}

void Positionable::setPosition(const Vec2d& pos)
{
    position=ToricPosition(pos);
}

std::ostream& operator<<(std::ostream& out, Positionable const& P)
{
    return out << P.getPosition(); //uses the operator<< of ToricPosition
}

std::ostream& Positionable::display(std::ostream& out)
{
    return out << *this; //uses the external operator<< above
}

double Positionable::calculateAngle(const Positionable& other) const
{
    double x(other.getPosition().x() - getPosition().x());
    double y(other.getPosition().y() - getPosition().y());
    return atan2(y,x);
}

