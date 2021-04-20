#ifndef ANTSOLDIER_HPP
#define ANTSOLDIER_HPP
#include "Ant.hpp"

class AntSoldier : public Ant
{
public:
    /*!
     *  @brief default constructor
     */
    AntSoldier();

    /*!
     *  @brief constructor with specific position and uid
     *
     *  @param TP position in ToricPosition form
     *  @param uid of the corresponding anthill
     *
     *  @note calls Ant constructor using TP, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan and uid
     */
    AntSoldier(const ToricPosition& TP, Uid uid);

    /*!
     *  @brief constructor with specific position and uid
     *
     *  @param pos position in Vec2d form
     *  @param uid of the corresponding anthill
     *
     *  @note calls AntSoldier constructor using ToriPosition(pos)
     */
    AntSoldier(const Vec2d& pos, Uid uid);

    /*!
     *  @brief gets sprite of an ant soldier
     */
    sf::Sprite getSprite() const override;

    double getStrength() const override;
};

#endif // ANTSOLDIER_HPP
