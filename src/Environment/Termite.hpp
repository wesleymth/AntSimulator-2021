#ifndef TERMITE_HPP
#define TERMITE_HPP
#include "Animal.hpp"

class Termite : public Animal
{
public:
    Termite();
    Termite(const ToricPosition& pos);
    Termite(const Vec2d& pos);
    double getSpeed() const override;

    double getStrength() const override;
    double getAttackDelay() const override;

    sf::Sprite getSprite() const override;
    bool isEnemy(Animal const* animal) const;
    bool isEnemyDispatch(Termite const* other) const;
    bool isEnemyDispatch(Ant const* other) const;
};

#endif // TERMITE_HPP
