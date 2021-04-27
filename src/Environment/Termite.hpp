/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

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

    int getStrength() const override;
    double getAttackDelay() const override;

    sf::Sprite getSprite() const override;

    bool isEnemy(Animal const* animal) const override;
    bool isEnemyDispatch(Termite const* other) const override;
    bool isEnemyDispatch(Ant const* other) const override;

};

#endif // TERMITE_HPP
