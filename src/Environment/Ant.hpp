#ifndef ANT_HPP
#define ANT_HPP
#include "Animal.hpp"

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
    virtual double getSpeed() const override;


    double getAttackDelay() const override;


    /*!
     *  @brief gets anthillUid
     *
     *  @return Uid anthillUid
     */
    Uid getAnthillUid() const;

    /*!
     *  @brief draws ant
     *
     *  @note if debug on you can see a line representing the direction vector and HP value in red
     *  and the ant's perception distance reprenseted by a blue ring
     */
    void drawOn(sf::RenderTarget& target) const override;

    /*!
     *  @brief places pheromones from last placed pheromone to current position
     *
     *  @note
     */
    void spreadPheromones();

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
     */
    RotationProbs computeRotationProbs() const override;

    bool isEnemy(Animal const* animal) const override;
    bool isEnemyDispatch(Termite const* other) const override;
    bool isEnemyDispatch(Ant const* other) const override;
private:
    Uid anthillUid;
    ToricPosition lastPheromone;
};

#endif // ANT_HPP
