/*
* POOSV 2020-21
* @author:
*/

#pragma once
#include "ToricPosition.hpp"

/*!
 * @class Positionable
 *
 * @brief Represents an entitiy that has a postion
 */
class Positionable
{
public:
     /*!
      * @brief default constructor
      *
      * @note calls the default constructor of ToricPositions
      */
     Positionable();

     /*!
      * @brief constructor initialising the position using a given ToricPosition
      */
     Positionable(const ToricPosition& T);

     /*!
      * @brief constructor using a Vec2D
      */
     Positionable(const Vec2d& pos);

     /*!
      * @brief gets the position
      *
      * @return position in ToricPosition form
      */
     ToricPosition getPosition() const;

     /*!
      * @brief sets the position using a ToricPosition
      *
      * @return position in ToricPosition form
      *
      * @note uses operator= for ToricPosition
      */
     void setPosition(const ToricPosition& pos);

     /*!
      * @brief sets the position using a Vec2d
      *
      * @return position in ToricPosition form
      *
      * @note uses operator= for ToricPosition
      */
     void setPosition(const Vec2d& pos);

     /*!
      * @brief displays current Positionable using operator<<
      *
      * @return ostream& out
      *
      * @note uses external operator<<
      */
     std::ostream& display(std::ostream& out);

private:
    ToricPosition position;
};

/*!
* @brief operator<<
*
* @return ostream& out
*
* @note uses operator<< for ToricPosition
*/
std::ostream& operator<<(std::ostream& out, Positionable const& P);
