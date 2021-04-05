#include "AntSoldier.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"


AntSoldier::AntSoldier(const Vec2d& pos, Uid id)
    :Ant::Ant(pos, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan, id)
{
    //Done
}

AntSoldier::AntSoldier()
    :AntSoldier(Vec2d(), Uid()) //calls constructor above using default Vec2d and default Uid
{
    //Done
}

void AntSoldier::drawOn(sf::RenderTarget& target) const
{
    auto const animalSprite = buildSprite((getPosition()).toVec2d(), (DEFAULT_ANT_SIZE), getAppTexture(getAppConfig().ant_soldier_texture), getDirection()/DEG_TO_RAD);
        target.draw(animalSprite);
    if (isDebugOn()) //if debug on you can see the healthPoints
    {
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
            line[0] = { getPosition().toVec2d(), sf::Color::Black };
            line[1] = { getPosition().toVec2d()+200*Vec2d::fromAngle(getDirection()), sf::Color::Black };
            target.draw(line);  //draws line
        auto const text = buildText(to_nice_string(healthPoints), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black);
        target.draw(text); //shows healthPoints via a text
    }
}
