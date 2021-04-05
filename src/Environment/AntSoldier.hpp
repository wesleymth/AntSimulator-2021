#ifndef ANTSOLDIER_HPP
#define ANTSOLDIER_HPP
#include "Ant.hpp"

class AntSoldier : public Ant
{
public:
    AntSoldier(const Vec2d& pos, Uid id);

    AntSoldier();

    sf::Sprite getSprite() const;
};

#endif // ANTSOLDIER_HPP
