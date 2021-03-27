#include "Food.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"


Food::Food(const Vec2d& pos, Quantity quant)
    :position(ToricPosition(pos).toVec2d()),quantity(quant)
{
    //Done
}

//d'une méthode takeQuantity permettant de prélever une quantité donnée de nourriture de la source.
//Cette méthode retournera la quantité qui a pu être prélevée (on ne peut prélever que ce qui est disponible).
Quantity Food::takeQuantity(Quantity wantTake){
    Quantity taken(quantity);
    //if (wantTake)
    if (quantity>wantTake) //CAS OU WANTTAKE EST NÉGATIF?
    {
        quantity -= wantTake;
        taken = wantTake;
    }
    else
    {
        quantity = 0.0;
    }
    return taken;
}

//d'une méthode de dessin qui devra strictement adhérer au prototype suivant : void drawOn(sf::RenderTarget& target) const.
void Food::drawOn(sf::RenderTarget& target) const{
    auto const foodSprite = buildSprite((position.getPosition()).toVec2d(), (quantity/2), getAppTexture(getAppConfig().food_texture));
        target.draw(foodSprite);

        if (isDebugOn())
        {
            auto const text = buildText(to_nice_string(quantity), position.getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black);
            target.draw(text);
        }
}
