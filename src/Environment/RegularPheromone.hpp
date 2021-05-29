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
     * @brief to know if ants can intercat with the pheromone
     *
     * @return false because a regular pheromone
     *
     * @note (we know this is type testing and not recommended but we didn't find a way otherwise)
     */
    bool interact() const override;

    /*!
     * @return nullptr
     */
    Anthill* getEnemy() const override;

    /*!
     * @return default ToricPosition
     */
    ToricPosition getEnemyPosition() const override;
};

#endif // REGULARPHEROMONE_HPP
