/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#ifndef FOOD_HPP
#define FOOD_HPP
#include "Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>
#include "../Interface/Drawable.hpp"
#include "../Interface/Savable.hpp"

/*!
 * @class Food
 *
 * @brief Represents and manages the aspects of a food, which can be picked up and moved by ant workers
 *
 * @inherits Positionable, Drawable
 */

class Food : public Positionable, public Drawable, public Savable
{
public:
    /*!
     *  @brief gets the counted number of food in environment
     *
     *  @return number of food quantities in environemnt
     */
    static Quantity getCount();


    /*!
     *  @brief default constructor
     */
    Food();

    /*!
     *  @brief default destructor
     *
     *  @note takes away quantity of Food::count
     */
    ~Food();

    /*!
     *  @brief constructor using a given positionable and quantity
     *
     *  @param TP ToricPosition of the food
     *  @param quant quantity of the food
     *
     *  @note adds quant to Food::count
     */
    Food(const ToricPosition& TP, Quantity quant);

    /*!
     *  @brief constructor using a given positionable and quantity
     *
     *  @param pos position of the food
     *  @param quant quantity of the food
     *
     *  @note calls other constructor using ToricPosition(pos) and quant
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
    void drawOn(sf::RenderTarget& target) const override;

    /*!
     *  @brief checks if the food has no more quantity
     *
     *  @return true if quantity == 0
     *
     *  @note used in Environment.cpp to delete the foods with no more quantity
     */
    bool zeroQuantity() const;

    /*!
     *  @brief Writes information to recreate current this
     *
     *  @param std::ofstream &stream
     *
     *  @note In addition to position and type writes food
     */
    void writeLine(std::ofstream &stream) const override;
private:
    static Quantity count;

    Quantity quantity;
};

#endif // FOOD_HPP
