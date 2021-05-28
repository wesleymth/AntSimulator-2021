#include "AntQueen.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "../Utility/Constants.hpp"


AntQueen::AntQueen()
    :AntQueen(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2), DEFAULT_UID)
{
    //Done
}


AntQueen::AntQueen(const ToricPosition& TP, Uid uid)
    :Ant::Ant(TP, DEFAULT_QUEEN_HP, DEFAULT_QUEEN_LIFE, uid), anthillPosition(TP)
{
    //Done
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
                       getAppTexture(getAppConfig().ant_worker_texture),
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
        colonise();
    }
}

RotationProbs AntQueen::computeRotationProbs() const
{
    return Animal::computeRotationProbs();
}

void AntQueen::colonise()
{
    getAppEnv().addAnthill(new Anthill(getPosition(), createUid()));
    kill();  //Mimics Ant queen going into anthill
}






