/*
* POOSV 2020-21
* @author:
*/

#pragma once
#include "ToricPosition.hpp"

    /*!
    * @brief Manage a position in a toric world
    *
    *
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

     //Un constructeur initialisant la position à l'aide de la ToricPosition passée en paramètre.
     /*!
      * @brief constructor initialising the position using a given ToricPosition
      */
     Positionable(const ToricPosition& T);

     //Une méthode publique getPosition() qui retourne la position.
     /*!
      * @brief gets the position
      *
      * @return position in ToricPosition form
      */
     ToricPosition getPosition() const;

     /*!
      * @brief gets the position
      *
      * @return position in ToricPosition form
      *
      * @note uses operator= for ToricPosition
      */
     void setPosition(const ToricPosition& pos);

     /*!
      * @brief displays current Positionable using << operator
      *
      * @return ostream& out
      *
      * @note uses << operator
      */
     //Une méthode ostream& display(ostream& out) affichant les mêmes informations que l'opérateur <<.
     std::ostream& display(std::ostream& out);

private:
    ToricPosition position;
};

/*!
* @brief << operator
*
* @return ostream& out
*
* @note uses << operator for ToricPosition
*/
//Une surcharge de l'opérateur d'affichage <<
std::ostream& operator<<(std::ostream& out, Positionable const& P);
