#include "AntQueen.hpp"
#include "AntSoldier.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"


AntQueen::AntQueen()
    :AntQueen(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2), DEFAULT_UID)
{
    //Done
}


AntQueen::AntQueen(const ToricPosition& TP, Uid uid)
    :Ant::Ant(TP, DEFAULT_QUEEN_HP, DEFAULT_QUEEN_LIFE, uid)
{

}

AntQueen::AntQueen(const Vec2d& pos, Uid uid)
    :AntQueen(ToricPosition(pos),uid)
{
    //Done
}

sf::Sprite AntQueen::getSprite() const
{
    return buildSprite((getPosition()).toVec2d(),
                       DEFAULT_QUEEN_SIZE,
                       getAppTexture(getAppConfig().ant_soldier_texture),
                       getDirection()/DEG_TO_RAD);
}

int AntQueen::getStrength() const
{
    return DEFAULT_QUEEN_STRENGTH;
}

void AntQueen::update(sf::Time dt)
{
    Animal::update(dt);
    if (toricDistance(anthillPosition, getPosition())>DEFAULT_COLONY_DISTANCE)
    {
        colonise;
    }
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


RotationProbs AntQueen::computeRotationProbs() const
{
    Animal::computeRotationProbs();
}

void AntQueen::colonise()
{
    getAppEnv().addAnthill(new Anthill(getPosition(), getAnthillUid()));
    kill();  //Mimics Ant queen going into anthill
}






