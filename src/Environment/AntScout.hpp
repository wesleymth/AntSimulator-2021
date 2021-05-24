#ifndef ANTSCOUT_HPP
#define ANTSCOUT_HPP
#include "Ant.hpp"
#include "Anthill.hpp"
#include "AntKamikaze.hpp"
#include "AntSoldier.hpp"
#include "AntWorker.hpp"

class AntScout : public Ant
{
public:

    /*!
     *  @brief gets the counted number of AntScouts in environment
     *
     *  @return number of ant scouts in environemnt
     */
    static int getCount();

    /*!
     *  @brief default constructor
     */
    AntScout();

    /*!
     *  @brief default destructor
     *
     *  @note decrements count
     */
    ~AntScout();

    /*!
     *  @brief constructor with specific position and uid
     *
     *  @param TP position in ToricPosition form
     *  @param uid of the corresponding anthill
     *
     *  @note calls Ant constructor using TP, ANT_SCOUT_HP, ANT_SCOUT_LIFE and uid
     *  @note incrments count
     */
    AntScout(const ToricPosition& TP, Uid uid);

    /*!
     *  @brief constructor with specific position and uid
     *
     *  @param pos position in Vec2d form
     *  @param uid of the corresponding anthill
     *
     *  @note calls AntScout constructor using ToriPosition(pos)
     */
    AntScout(const Vec2d& pos, Uid uid);

    /*!
     *  @brief gets sprite of an ant scout
     *
     *  @return sprite of an ant scout
     *
     *  @note uses buildSprite(...) from Utility.hpp
     */
    sf::Sprite getSprite() const override;

    /*!
     *  @brief gets strength of an ant scout
     *
     *  @return ANT_SCOUT_STRENGTH
     */
    int getStrength() const override;

    /*!
     *  @brief bool if target is found
     *
     *  @return target != nullptr
     */
    bool foundTarget() const;

    /*!
     *  @brief if it found a target it saves alol info needed for a Kamikaze
     *
     *  @param victim Anthill*
     */
    void saveTargetInfo(Anthill *victim);

    //void update(sf::Time dt) override;

private:
    static int count;
    Anthill* target;
    ToricPosition targetPosition;
};

#endif // ANTSCOUT_HPP
