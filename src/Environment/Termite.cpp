#include "Termite.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "Environment.hpp"

Termite::Termite()

{

}

Termite::Termite(const ToricPosition& pos)
    :Animal::Animal(pos, getAppConfig().termite_hp, getAppConfig().termite_lifespan)
{
    //Done
}

Termite::Termite(const Vec2d& pos)
    :Termite(ToricPosition(pos))
{
    //Done
}

double Termite::getSpeed() const
{
    return getAppConfig().termite_speed;
}

double Termite::getStrength() const
{
    return getAppConfig().termite_strength;
}

double Termite::getAttackDelay() const
{
    return getAppConfig().termite_attack_delay;
}

sf::Sprite Termite::getSprite() const
{
    return buildSprite((getPosition()).toVec2d(),
                       DEFAULT_TERMITE_SIZE,
                       getAppTexture(getAppConfig().termite_texture),
                       getDirection()/DEG_TO_RAD);
}

bool Termite::isEnemy(Animal const* animal)
{
    return !isDead() && !animal->isDead() && animal->isEnemyDispatch(this);
}

bool Termite::isEnemyDispatch(Termite const* other)
{
    return false;
}

 bool Termite::isEnemyDispatch(Ant const* other)
{
    return true;
}