#ifndef ANTQUEEN_HPP
#define ANTQUEEN_HPP
#include "Ant.hpp"

class AntQueen: public Ant
{
public:
    /*!
     *  @brief default constructor
     */
    AntQueen();

    /*!
     *  @brief constructor with specific attributes
     *
     *  @param TP position in ToricPosition form
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of Ant
     */
    AntQueen(const ToricPosition &TP, Uid uid);

    /*!
     *  @brief constructor with specific attributes
     *
     *  @param pos position in Vec2d form
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of AntWorker using TP.toVec2d() as pos
     */
    AntQueen(const Vec2d &pos, Uid uid);

    /*!
     *  @brief gets sprite of an ant queen
     *
     *  @return sf::Sprite of an ant queen
     */
    sf::Sprite getSprite() const override;

    /*!
     *  @brief gets strength of an ant queen
     *
     *  @return
     */
    int getStrength() const override;

    /*!
     *  @brief updates an ant queen
     *
     *  @note calls Animal::update(dt) and adds specific behaviour new anthills
     */
    void update(sf::Time dt) override;

    /*!
     *  @brief computes rotation probs
     *
     *  @return RotationProbs
     *
     *  @note calls Animal::computeRotationProbs(), There is no reason for a Queen to follow pheromones
     */
    RotationProbs computeRotationProbs() const override;

    void colonise();

private:
    ToricPosition anthillPosition;
};

#endif // ANTQUEEN_HPP
