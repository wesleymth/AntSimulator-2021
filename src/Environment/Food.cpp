/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#include "Food.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

Food::Food(const ToricPosition& TP, Quantity quant)
    :Positionable(TP),quantity(quant)
{
    //Done
}

Food::Food(const Vec2d& pos, Quantity quant)
    :Food(ToricPosition(pos),quant)
{
    //Done
}

Quantity Food::takeQuantity(Quantity wantTake)
{
    Quantity taken(quantity);
    if (wantTake < 0)
    {
        taken=0.0; //gets rid of the case when you want to take something negative
    }
    else
    {
        if (quantity>wantTake)
        {
            quantity -= wantTake;
            taken = wantTake;
        }
        else
        {
            quantity = 0.0; //cannot take anything more than what is available
        }
    }
    return taken;
}

void Food::drawOn(sf::RenderTarget& target) const
{
    auto const foodSprite = buildSprite((getPosition()).toVec2d(), quantity/5, getAppTexture(getAppConfig().food_texture));
        target.draw(foodSprite); //draws a food

        if (isDebugOn()) //if debug on you can see the quantity of the food
        {
            auto const text = buildText(to_nice_string(quantity), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black);
            target.draw(text); //shows quantity via a text
        }
}

bool Food::zeroQuantity() const
{
    return (quantity == 0);
}
