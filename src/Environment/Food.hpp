#ifndef FOOD_HPP
#define FOOD_HPP
#include "Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>

class Food
{
public:

    /*!
     *  @brief constructor using a given positionable and quantity
     *
     *  @param pos position of the food
     *  @param quant quantity of the food
     */
    Food(const Vec2d& pos, Quantity quant);

    /*!
     *  @brief takes and gives back wanted quantity
     *
     *  @param wantTake quantity you want to take
     *
     *  @return quantity taken
     *
     *  @note cannot take anything more than what is available
     */
    //d'une méthode takeQuantity permettant de prélever une quantité donnée de nourriture de la source.
    //Cette méthode retournera la quantité qui a pu être prélevée (on ne peut prélever que ce qui est disponible).
    Quantity takeQuantity(Quantity wantTake);

    /*!
     *  @brief
     *
     *  @param
     *
     *  @return
     *
     *  @note
     */
    //d'une méthode de dessin qui devra strictement adhérer au prototype suivant : void drawOn(sf::RenderTarget& target) const.
    //Il vous est expliqué un peu plus bas comment implémenter cette méthode.
    void drawOn(sf::RenderTarget& target) const;

private:
    Positionable position;
    Quantity quantity;
};

#endif // FOOD_HPP
