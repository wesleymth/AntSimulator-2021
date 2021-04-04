#ifndef FOOD_HPP
#define FOOD_HPP
#include "Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"

class Food : public Positionable //, public Drawable, public Updatable
{
public:
    /*!
     *  @brief constructor using a given positionable and quantity
     *
     *  @param pos position of the food
     *  @param quant quantity of the food
     *
     *  @note calls the ToricPosition constructor with vector as parameter
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
     *  @note doesn't do anything for a negative wantTake
     */
    Quantity takeQuantity(Quantity wantTake);

    /*!
     *  @brief draw a food on a window
     *
     *  @param target window
     *
     *  @note uses getAppConfig().food_texture for food texture
     *  @note if debug mode on you can see the quantity attribute of the food
     */
    void drawOn(sf::RenderTarget& target) const;

private:

    Quantity quantity;
};

#endif // FOOD_HPP
