#ifndef TERMITE_HPP
#define TERMITE_HPP
#include "Animal.hpp"

class Termite : public Animal
{
public:
    Termite();
    Termite(const ToricPosition& pos);
    Termite(const Vec2d& pos);
    double getSpeed() const;
    sf::Sprite getSprite() const;
    virtual bool isEnemy(Animal const* animal);
    virtual bool isEnemyDispatch(Termite const* other);
    virtual bool isEnemyDispatch(Ant const* other);
};

#endif // TERMITE_HPP
