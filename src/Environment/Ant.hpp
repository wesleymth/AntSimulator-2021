/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#ifndef ANT_HPP
#define ANT_HPP
#include "Animal.hpp"

/*!
 * @class Ant
 *
 * @brief Represents and manages the aspects of an abstract ant
 *
 * @note abstract class
 *
 * @inherits Animal
 */

class Ant : public Animal
{
public:
    /*!
     *  @brief default constructor
     */
    Ant();

    /*!
     *  @brief constructor with specific attributes
     *
     *  @param TP position in ToricPosition form
     *  @param HP health points
     *  @param LT lifetime
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of Animal
     *  @note sets lastPheromone to TP as well
     */
    Ant(const ToricPosition& pos, double HP, double LT, Uid uid);

    /*!
     *  @brief constructor with specific attributes
     *
     *  @param pos position in Vec2d form
     *  @param HP health points
     *  @param LT lifetime
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of Ant using ToricPosition(pos)
     */
    Ant(const Vec2d& pos, double HP, double LT, Uid uid);

    /*!
     *  @brief constructor with a position and a uid
     *
     *  @param TP position in ToricPosition form
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of Animal
     */
    Ant(const ToricPosition& TP, Uid uid);

    /*!
     *  @brief constructor with a position and a uid
     *
     *  @param pos position in Vec2d form
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of Ant using ToricPosition(pos)
     */
    Ant(const Vec2d& pos, Uid uid);

    /*!
     *  @brief gets speed of ant
     *
     *  @note returns getAppConfig().ant_speed
     */
    double getSpeed() const override;

    /*!
     *  @brief gets the attack delay of the ants
     *
     *  @note returns getAppConfig().ant_attack_delay
     */
    double getAttackDelay() const override;

    /*!
     *  @brief gets anthillUid
     *
     *  @return Uid anthillUid
     */
    Uid getAnthillUid() const;

    /*!
     *  @brief gets the lastPheromone
     *
     *  @return ToricPosition lastPheromone
     */
    ToricPosition getLastPheromone() const;

    /*!
     *  @brief draws ant
     *
     *  @note if debug on you can see a line representing the direction vector and HP value in red
     *  and the ant's perception distance reprenseted by a blue ring
     */
    void drawOn(sf::RenderTarget& target) const override;

    /*!
     *  @brief places pheromones from last placed pheromone to current position
     */
    virtual void spreadPheromones();

    /*!
     *  @brief make ants move
     *
     *  @param target window
     *
     *  @note calls Animal::Move and spreads pheromones
     */
    virtual void move(sf::Time dt) override;

    /*!
     *  @brief draws quantity of pheromones
     *
     *  @param target window
     *
     *  @note code given by  step 3.2
     */
    void drawPheromoneAngles(sf::RenderTarget& target) const;

    /*!
     *  @brief override of computeRotationProbs() to add effect of pheromones
     *
     *  @return RotationProbs
     */
    RotationProbs computeRotationProbs() const override;

    /*!
     *  @brief returns true if animal in parameter is an enemy
     *
     *  @param Animal const* animal
     *
     *  @note uses double dispatch with isEnemyDispatch. Override of pure virtual method in animal
     */
    bool isEnemy(Animal const* animal) const override;

    /*!
     *  @brief double dipatch fonction to allow polymorphism without type testing
     *
     *  @param Termite const* other
     *
     *  @return bool
     *
     *  @note Override of pure virtual method in animal
     */
    bool isEnemyDispatch(Termite const* other) const override;

    /*!
     *  @brief double dipatch fonction to allow polymorphism without type testing
     *
     *  @param Ant const* other
     *
     *  @return bool
     *
     *  @note Override of pure virtual method in animal
     */
    bool isEnemyDispatch(Ant const* other) const override;

protected:

    /*!
     *  @brief sets new position of lastPheromone
     */
    void setLastPheromone(const ToricPosition& newPosition);

private:
    Uid anthillUid;
    ToricPosition lastPheromone;
};

#endif // ANT_HPP
