/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#include "Termite.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "Environment.hpp"

int Termite::count = 0;

Termite::Termite()
    :Termite(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2))
{
    //Done
}

Termite::~Termite()
{
    --count;
}

Termite::Termite(const ToricPosition& pos)
    :Animal::Animal(pos, getAppConfig().termite_hp, getAppConfig().termite_lifespan)
{
    ++count;
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

int Termite::getStrength() const
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

bool Termite::isEnemy(Animal const* animal) const
{
    return !isDead() && !animal->isDead() && animal->isEnemyDispatch(this);
}

bool Termite::isEnemyDispatch(Termite const* other) const
{
    return false;
}


bool Termite::isEnemyDispatch(Ant const* other) const
{
    return true;
}

void Termite::writeLine(std::ofstream& stream) const
{
    stream << "termite " << getPosition().x() << " " << getPosition().y() << std::endl;
}
