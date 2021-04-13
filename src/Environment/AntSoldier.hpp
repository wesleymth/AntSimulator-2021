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
     *  @param pos position in Vec2d form
     *  @param uid of the corresponding anthill
     *
     *  @note calls Ant constructor using pos, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan and uid
     */
    AntSoldier(const Vec2d& pos, Uid uid);

    /*!
     *  @brief constructor with specific position and uid
     *
     *  @param pos position in ToricPosition form
     *  @param uid of the corresponding anthill
     *
     *  @note calls AntSoldier constructor using TP as pos
     */
    AntSoldier(const ToricPosition& TP, Uid uid);

    /*!
     *  @brief gets sprite of an ant soldier
     */
    sf::Sprite getSprite() const override;
};

#endif // ANTSOLDIER_HPP
