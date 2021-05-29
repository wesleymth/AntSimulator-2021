#ifndef ANTKAMIKAZE_HPP
#define ANTKAMIKAZE_HPP
#include "Ant.hpp"
#include "Anthill.hpp"
#include "Pheromone.hpp"

enum KamikazeCondition {Wander,KillTarget};

class AntKamikaze : public Ant
{
public:
    /*!
     *  @brief gets the counted number of Kamikazes in environment
     *
     *  @return number of kamikazes in environemnt
     */
    static int getCount();

    /*!
     *  @brief default constructor
     */
    AntKamikaze();

    /*!
     *  @brief default destructor
     *
     *  @note decrements count
     */
    ~AntKamikaze();

    /*!
     *  @brief constructor with specific position and uid
     *
     *  @param TP position in ToricPosition form
     *  @param uid of the corresponding anthill
     *
     *  @note calls Ant constructor using TP, ANT_KAMAIKAZE_HP, ANT_KAMAIKAZE_LIFE and uid
     *  @note incrments count
     */
    AntKamikaze(const ToricPosition& TP, Uid uid);

    /*!
     *  @brief constructor with a given enemy
     *
     *  @param TP position in ToricPosition form
     *  @param uid of the corresponding anthill
     *
     *  @note calls AntKamikaze constructor
     */
    AntKamikaze(const ToricPosition& TP, Uid uid, Anthill* enemy, const ToricPosition& enemyPosition);

    /*!
     *  @brief constructor with specific position and uid
     *
     *  @param pos position in Vec2d form
     *  @param uid of the corresponding anthill
     *
     *  @note calls AntKamikaze constructor using ToriPosition(pos)
     */
    AntKamikaze(const Vec2d& pos, Uid uid);

    /*!
     *  @brief gets sprite of an ant kamikaze
     *
     *  @return sprite of an ant kamikaze
     *
     *  @note uses buildSprite(...) from Utility.hpp
     */
    sf::Sprite getSprite() const override;

    /*!
     *  @brief gets strength of an ant kamikaze
     *
     *  @return getAppConfig().ANT_KAMAIKAZE_STRENGTH;
     */
    int getStrength() const override;

    /*!
     *  @brief gets target of an ant kamikaze
     *
     *  @return target
     */
    Anthill* getTarget() const;

    /*!
     *  @brief makes kamikaze move using Animal::move(sf::Time dt) except if condition = KillTarget in which case Kamikaze goes straigth to targetted anthill
     *
     *  @note always spreads pheromones
     */
    void move(sf::Time dt) override;

    /*!
     *  @brief updates kamaikaze using Animal::update(sf::Time dt) plus manages the kamikaze's attacks on other anthills
     */
    void update(sf::Time dt) override;

    /*!
     *  @brief draws kamaikaze using Ant::update(sf::Time dt) and if debug on you can see it's target's uid if it has one
     */
    void drawOn(sf::RenderTarget& Target) const override;

    /*!
     *  @brief bool if target is found
     *
     *  @return target != nullptr
     */
    bool foundTarget() const;

    /*!
     *  @brief makes the kamikaze explode onto an anthill
     *
     *  @note calls method kill from Animal class and takeDamage from Anthill class
     */
    void explode(Anthill* victim);

    /*!
     *  @brief bool if target is in perception distance
     *
     *  @return true if in perception distance
     */
    bool targetInPerceptionDistance() const;

    /*!
     *  @brief receives all information needed to go kill a targetted anthill
     *
     *  @note sets target and targetPosition attribute to anthill and position
     *  @note calculates tragetAngle using calculateAngle from Positionable class
     *  @note sets condition to KillTarget
     */
    void receiveTargetInformation(Anthill *anthill, const ToricPosition& position);

private:
    static int count;
    Anthill* target;
    ToricPosition targetPosition;
    KamikazeCondition condition;

};

#endif // ANTKAMIKAZE_HPP
