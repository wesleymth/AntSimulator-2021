/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#include "AntSoldier.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

AntSoldier::AntSoldier()
{
    //Done
}

AntSoldier::AntSoldier(const ToricPosition& TP, Uid uid)
    :Ant::Ant(TP, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan, uid)
{
    //Done
}

AntSoldier::AntSoldier(const Vec2d& pos, Uid uid)
    :AntSoldier(ToricPosition(pos),uid)
{
    //Done
}

sf::Sprite AntSoldier::getSprite() const
{
    return buildSprite((getPosition()).toVec2d(),
                       DEFAULT_ANT_SIZE,
                       getAppTexture(getAppConfig().ant_soldier_texture),
                       getDirection()/DEG_TO_RAD);
}

int AntSoldier::getStrength() const
{
    return getAppConfig().ant_soldier_strength;
}

void AntSoldier::drawOn(sf::RenderTarget& target) const
{
    Ant::drawOn(target);
    if (isDebugOn()) { //if debug on you can see the uid in magenta
        auto const uidText = buildText(to_nice_string(getAnthillUid()), getPosition().toVec2d()+Vec2d(0,40), getAppFont(), 15, sf::Color::Magenta);
        target.draw(uidText); //shows anthill uid via a text
        target.draw(buildAnnulus(getPosition().toVec2d(), getAppConfig().ant_smell_max_distance, sf::Color::Blue, 5)); //draws a ring around animal representing the perception distance
    }
}
