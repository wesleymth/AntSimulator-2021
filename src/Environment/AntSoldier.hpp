/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#ifndef ANTSOLDIER_HPP
#define ANTSOLDIER_HPP
#include "Ant.hpp"

/*!
 * @class AntSoldier
 *
 * @brief Represents and manages the aspects of an ant soldier, which can interact with other animals and is capable of fighting
 *
 * @inherits Ant
 */

class AntSoldier : public Ant
{
public:
    /*!
     *  @brief gets the counted number of AntSoliders in environment
     *
     *  @return number of ant soldiers in environemnt
     */
    static int getCount();

    /*!
     *  @brief default constructor
     */
    AntSoldier();

    /*!
     *  @brief default destructor
     *
     *  @note decrements count
     */
    ~AntSoldier();

    /*!
     *  @brief constructor with specific position and uid
     *
     *  @param TP position in ToricPosition form
     *  @param uid of the corresponding anthill
     *
     *  @note calls Ant constructor using TP, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan and uid
     *  @note incrments count
     */
    AntSoldier(const ToricPosition& TP, Uid uid);

    /*!
     *  @brief constructor with specific position, uid and direction angle
     *
     *  @param TP position in ToricPosition form
     *  @param uid of the corresponding anthill
     *
     *  @note calls above AntSoldier constructo
     */
    AntSoldier(const ToricPosition& TP, Uid uid, Angle notRandomAngle);

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
     *
     *  @return sprite of an ant soldier
     *
     *  @note uses buildSprite(...) from Utility.hpp
     */
    sf::Sprite getSprite() const override;

    /*!
     *  @brief gets strength of an ant soldier
     *
     *  @return strength of an ant soldier
     *
     *  @note getAppConfig().ant_soldier_strength
     */
    int getStrength() const override;

private:
    static int count;
};

#endif // ANTSOLDIER_HPP
