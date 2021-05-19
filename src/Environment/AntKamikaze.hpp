#ifndef ANTKAMIKAZE_HPP
#define ANTKAMIKAZE_HPP
#include "Ant.hpp"
#include "Anthill.hpp"

enum Condition {Wander,KillTarget};

class AntKamikaze : public Ant
{
public:
    static int count;

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
     *  @return ANT_KAMIKAZE_STRENGTH
     */
    int getStrength() const override;

    void move(sf::Time dt) override;

    void update(sf::Time dt) override;

    bool foundTarget() const;

    void explode();

    bool targetInPerceptionDistance() const;

    void receiveTargetInformation(Anthill *anthill, const ToricPosition& position);



private:
    Anthill* target;
    ToricPosition targetPosition;
    Angle targetAngle;
    Condition condition;

};

#endif // ANTKAMIKAZE_HPP
