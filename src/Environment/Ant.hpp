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
     *  @param pos position in Vec2d form
     *  @param HP health points
     *  @param LT lifetime
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of Animal
     *  @note sets lastPheromone to pos as well
     */
    Ant(const Vec2d& pos, double HP, double LT, Uid uid);

    /*!
     *  @brief constructor with specific attributes
     *
     *  @param TP position in Toriposition form
     *  @param HP health points
     *  @param LT lifetime
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of Ant using TP.toVec2d as pos
     */
    Ant(const ToricPosition& TP, double HP, double LT, Uid uid);

    /*!
     *  @brief constructor with a position and a uid
     *
     *  @param pos position in vec2d form
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of Animal using a vec2d
     */
    Ant(const Vec2d& pos, Uid uid);

    /*!
     *  @brief constructor with a position and a uid
     *
     *  @param pos position in ToricPosition form
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of Ant using TP.toVec2d as pos
     */
    Ant(const ToricPosition& TP, Uid uid);

    /*!
     *  @brief gets speed of ant
     *
     *  @note returns getAppConfig().ant_speed
     */
    virtual double getSpeed() const override;

    /*!
     *  @brief gets sprite of an ant
     *
     *  @return sf::Sprite
     *
     *  @note to be defined for specific ant sub-classes
     */
    virtual sf::Sprite getSprite() const = 0;

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
     *  @note calls Animal::Move and spreads pheromones
     */
    virtual void move(sf::Time dt) override;

    void drawPheromoneAngles(sf::RenderTarget& target) const;

    RotationProbs computeRotationProbs() const override;

private:
    Uid anthillUid;
    ToricPosition lastPheromone;
};

#endif // ANT_HPP
