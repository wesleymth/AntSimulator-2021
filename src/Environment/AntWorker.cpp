#include "AntWorker.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"


AntWorker::AntWorker(const Vec2d& pos, Uid id)
    :Ant::Ant(pos, getAppConfig().ant_worker_hp, getAppConfig().ant_worker_lifespan, id)
{
    //Done
}

AntWorker::AntWorker()
    :AntWorker(Vec2d(), Uid())
{
    //Done
}

void AntWorker::drawOn(sf::RenderTarget& target) const
{
    auto const animalSprite = buildSprite((getPosition()).toVec2d(), (DEFAULT_ANT_SIZE), getAppTexture(getAppConfig().ant_worker_texture), getDirection()/DEG_TO_RAD);
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
