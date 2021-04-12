/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 */

#pragma once
#include "../Utility/Vec2d.hpp"
#include <iostream>

/*!
 * @brief Handle toric coordinate, distance and other
 * basic math operation in a toric world
 *
 * @note Gets the dimensions of the world from getAppConfig()
 */

class ToricPosition
{
public:

    /*!
     *  @brief constructor using 2 vectors
     *
     *  @param coords the coordinates of the new ToricPosition
     *  @param dim the dimensions of the world
     *
     *  @note uses clamp
     */
    ToricPosition(const Vec2d& coords, const Vec2d& dim);

    /*!
     *  @brief constructor using two specific values as coordinates
     *
     *  @param x the coordinate on the x-axis
     *  @param y the coordinate on the y-axis
     *
     *  @note uses clamp and getAppConfig().simulation_size for world dimensions
     */
    ToricPosition(double x, double y);

    /*!
     *  @brief constructor using one vector for coordinates
     *
     *  @param coords a vector for coordiantes
     *
     *  @note uses the constructor with two doubles as parameters and uses clamp
     */
    ToricPosition(const Vec2d& coords);

    /*!
     *  @brief default constructor
     *
     *  @note calls the constructor with doubles using x=0.0 and y=0.0
     */
    ToricPosition();

    /*!
     *  @brief default copy constructor
     *
     *  @param other ToricPosition by constant reference (no memory loss)
     */
    ToricPosition(ToricPosition const& other);

    /*!
     *  @brief operator=
     *
     *  @param other ToricPosition by constant reference (no memory loss)
     *
     *  @return reference onto a ToricPosition
     */
    ToricPosition& operator=(const ToricPosition& other);

    /*!
     *  @brief gets the coordinates of a ToricPosition instance
     *
     *  @return coordinates of a ToricPosition instance in Vec2d form
     */
    Vec2d const& toVec2d() const;

    /*!
     *  @brief gets the x-coordinate of a ToricPosition instance
     *
     *  @return x-coordinate of a ToricPosition instance
     */
    double x() const;

    /*!
     *  @brief gets the y-coordinate of a ToricPosition instance
     *
     *  @return y-coordinate of a ToricPosition instance
     */
    double y() const;

    /*!
     *  @brief operator==
     *
     *  @param other ToricPosiotion instance by constant reference
     *
     *  @return bool true if coordinates are approximatly equal, else false
     *
     *  @note uses the method isEqual for Vec2ds
     */
    bool operator==(const ToricPosition& other) const;

    /*!
     *  @brief operator+=
     *
     *  @param other ToricPosiotion instance by constant reference
     *
     *  @return reference of the addition of both coordinates
     */
    ToricPosition& operator+=(const ToricPosition& other);

    /*!
     *  @brief indexation operator
     *
     *  @param index which gets desired coordinate; 0 gives x-coordinate, 1 gives y-coordinate
     *
     *  @return desired coordinate in double form
     *
     *  @note uses clamp();
     */
    double operator[](int index) const;

    /*!
     *  @brief calculates the smallest vector from this to that in the toric world
     *
     *  @param that ToricPosiotion instance by constant reference
     *
     *  @return smallest vector in vec2d form
     *
     *  @note uses indexation from vec2d
     */
    Vec2d toricVector(ToricPosition const& that) const;

private:

    Vec2d coordinates;

    Vec2d worldDimensions;

    /*!
     *  @brief assures that the position is in the world
     *
     *  @note uses fmod and x,y "getters" for vec2d
     */
    void clamp();
};

/*!
 *  @brief operator+
 *
 *  @param other1 ToricPosiotion instance by constant reference
 *  @param other2 ToricPosiotion instance by constant reference
 *
 *  @return ToricPotion of the sum
 *
 *  @note uses operator+=
 */
const ToricPosition operator+(const ToricPosition& other1, const ToricPosition& other2);

/*!
 *  @brief operator<<
 *
 *  @param out reference ostream
 *  @param T ToricPosition taken by constant reference
 *
 *  @return reference onto an ostream
 */
std::ostream& operator<<(std::ostream& out, ToricPosition const& T);

/*!
 *  @brief calculates the shortest distance from "from" to "to" in the toric world
 *
 *  @param from ToricPosition
 *  @param to ToricPosition
 *
 *  @return distance in double form
 *
 *  @note calls upon the method toricVector and length() of Vec2d class
 */
double toricDistance(ToricPosition const& from, ToricPosition const& to);

