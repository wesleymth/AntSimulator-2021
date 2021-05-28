#ifndef REGULARPHEROMONE_HPP
#define REGULARPHEROMONE_HPP
#include "Pheromone.hpp"
#include "AntKamikaze.hpp"

class RegularPheromone : public Pheromone
{
public:
    /*!
     *  @brief default constructor
     */
    RegularPheromone();

    /*!
     *  @brief constructor that initialises position and quantity
     *
     *  @param vect const Vec2d&
     *  @param quant Quantity
     */
    RegularPheromone(const Vec2d& vect, Quantity quant);

    /*!
     *  @brief constructor that initialises position and quantity
     *
     *  @param vect const ToricPosition&
     *  @param quant Quantity
     */
    RegularPheromone(const ToricPosition &vect, Quantity quant);

    /*!
     *
     */
    bool interact() const override;

    Anthill* getEnemy() const override;

    ToricPosition getEnemyPosition() const override;
};

#endif // REGULARPHEROMONE_HPP
