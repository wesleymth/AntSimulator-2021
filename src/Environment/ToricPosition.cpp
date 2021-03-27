/*
 * POOSV 2020-21
 * @author:
 */

#include "ToricPosition.hpp"
#include "Application.hpp"
#include "../Utility/Utility.hpp"


void ToricPosition::clamp(){
    double x(coordinates.x());
    double y(coordinates.y());
    //if the position is negative we add the corresponding world dimension (width or height)
    //otherwise we add the rest of its division by the corresponding world dimension (width or height)
    if(x<0)
    {
        x += worldDimensions.x();
    }
    else
    {
        x = fmod(x,worldDimensions.x());
    }

    if(y<0)
    {
        y += worldDimensions.y();
    }
    else
    {
        y = fmod(y,worldDimensions.y());
    }
    //use of a new 2d vector to replace the past coordinates
    Vec2d newcoords(x,y);
    coordinates = newcoords;
}

ToricPosition::ToricPosition(Vec2d coords, Vec2d dim)
    :coordinates(coords),worldDimensions(dim)
{
    clamp(); //assures that the position is in the world
}

ToricPosition::ToricPosition(double x, double y)
    :coordinates(x,y),worldDimensions(getAppConfig().simulation_size,getAppConfig().simulation_size)
    //takes the dimensions of the world with the use of getAppConfig().simulation_size
{
    clamp(); //assures that the position is in the world
}

ToricPosition::ToricPosition(const Vec2d& coords)
    : ToricPosition(coords.x(), coords.y())
{
    //Done
}

ToricPosition::ToricPosition()
    : ToricPosition(0.0,0.0)
{
    //Done
}

ToricPosition::ToricPosition(ToricPosition const& other)
    :coordinates(other.coordinates),worldDimensions(other.worldDimensions)
{
    //Done
}

//[Q1.1] answered

ToricPosition& ToricPosition::operator=(const ToricPosition& other){
    worldDimensions=other.worldDimensions;
    coordinates=other.coordinates;
    clamp(); //assures that the coordinates are clamped
    return *this; //returns the reference of a ToricPosition instance
}

Vec2d const& ToricPosition::toVec2d() const{
    return coordinates;
}

double ToricPosition::x() const{
    return coordinates.x();
}

double ToricPosition::y() const{
    return coordinates.y();
}

bool ToricPosition::operator==(const ToricPosition& other) const{
    return ((isEqual(other.x(),this->x()))and(isEqual(other.y(),this->y())));
}

ToricPosition& ToricPosition::operator+=(const ToricPosition& other){
    coordinates=coordinates+other.coordinates; //"+" is defined for Vec2ds
    clamp(); //assures that the position is in the world
    return *this;
}

const ToricPosition operator+(const ToricPosition& other1, const ToricPosition& other2){
    ToricPosition res(other1);
    res += other2;
    return  res;
}

//[Q1.2] answered

std::ostream& operator<<(std::ostream& out, ToricPosition const& T)
{
    return out << "[" << T.x() << ", " << T.y() << "]";
}

double ToricPosition::operator[](int index) const{
    return coordinates[index]; //uses the indexation method of Vec2ds
}

//[Q1.3] answered

Vec2d ToricPosition::toricVector(ToricPosition const& that) const
{
   Vec2d to(that.coordinates-coordinates);
   double dist(distance(that.coordinates, this->coordinates));
   for(int i(-1); i<=1; ++i) //2 "for" loops to iterate on x & y coordinates
   {
       for(int j(-1); j<=1; ++j)
       {
           Vec2d incr(i*worldDimensions.x(), j*worldDimensions.y());
           if(distance(that.coordinates+incr, this->coordinates)<dist)
           {
               dist=distance(that.coordinates+incr, this->coordinates);
               to=(that.coordinates+incr)-this->coordinates;
           }
       }
   }
   return to;
}

//[Q1.5] answered

double toricDistance(ToricPosition const& from, ToricPosition const& to)
{
   Vec2d segment(from.toricVector(to)); //calls the method toricVector
   return segment.length();
}



