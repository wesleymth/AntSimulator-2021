/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#ifndef ANTSCOUT_HPP
#define ANTSCOUT_HPP
#include "Ant.hpp"
#include "Anthill.hpp"
#include "AntKamikaze.hpp"
#include "AntSoldier.hpp"
#include "AntWorker.hpp"

/*!
 * @class AntScout
 *
 * @brief Represents and manages the aspects of an ant scout, which can specifically interact with anthills and kamikazes
 *
 * @inherits Ant
 */

enum ScoutCondition {TargetAcquiered,Roam};

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
     *  @return getAppConfig().ANT_SCOUT_STRENGTH
     */
    int getStrength() const override;

    /*!
     *  @brief bool if target is found
     *
     *  @return target != nullptr
     */
    bool foundTarget() const;

    /*!
     *  @brief bool if condition == roam
     *
     *  @return condition == roam
     */
    bool roaming() const;

    /*!
     *  @brief if it found a target it saves all info needed for a Kamikaze or an Anthill
     *
     *  @param victim Anthill*
     */
    void saveTargetInfo(Anthill *victim);

    /*!
     *  @brief updates the scout: makes it able to give enemy information to its anthill
     *  or to it's anthill's kamikazes via information pheromones
     *
     *  @param dt sf::Time
     *
     *  @note calls Animal::update(dt)
     */
    void update(sf::Time dt) override;

    /*!
     *  @brief resembles Ant::spreadPheromones except that it can spread information pheromones as well
     */
    void spreadPheromones() override;

    /*!
     *  @brief Ant::drawOn(target) with a debug option showing the target's uid
     *
     *  @param target
     *
     *  @note if the target is dead but the scout does'nt know it will say "UID: DEAD"
     */
    void drawOn(sf::RenderTarget& target) const override;

private:
    static int count;
    Anthill* target;
    ToricPosition targetPosition;
    ScoutCondition condition;
    sf::Time timeSpreadInpho;
};

#endif // ANTSCOUT_HPP
