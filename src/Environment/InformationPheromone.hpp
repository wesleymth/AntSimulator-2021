#ifndef INFORMATIONPHEROMONE_HPP
#define INFORMATIONPHEROMONE_HPP
#include "Pheromone.hpp"
#include "Anthill.hpp"
#include "AntKamikaze.hpp"

class InformationPheromone : public Pheromone
{
public:
    /*!
     *  @brief default constructor
     */
    InformationPheromone();

    /*!
     *  @brief constructor that initialises position and quantity
     *
     *  @param vect const Vec2d&
     *  @param quant Quantity
     */
    InformationPheromone(const Vec2d& vect, Quantity quant, Uid antUid, Anthill* victim, const ToricPosition& victimPosition);

    /*!
     *  @brief constructor that initialises position and quantity
     *
     *  @param vect const ToricPosition&
     *  @param quant Quantity
     */
    InformationPheromone( const ToricPosition& TP, Quantity quant, Uid antUid, Anthill* victim, const ToricPosition& victimPosition);

    /*!
     *  @brief in charge of decreasing quantity of pheromones at a set interval
     *
     *  @param dt time interval
     *
     *  @note make it last longer than a regular pheromone
     */
    void update(sf::Time dt) override;

    /*!
     *  @brief draw a pheromone on a window
     *
     *  @param target window
     */
    void drawOn(sf::RenderTarget &target) const override;

    /*!
     * @brief get enemy to give to other ants
     *
     * @return enemy
     */
    Anthill* getEnemy() const override;

    /*!
     * @brief get enemyPosition to give to other ants
     *
     * @return enemyPosition
     */
    ToricPosition getEnemyPosition() const override;

    /*!
     * @brief get the uid of the ants that are able to read the information
     *
     * @return allowedReading
     */
    Uid getAllowedReading() const;

    /*!
     * @brief to know if animals can interact with this type of pheromone
     *
     * @return true
     *
     * @note (a type testing but we didn't find a way to make it work otherwise)
     */
    bool interact() const override;

private:
    Uid allowedReading;
    Anthill* enemy;
    ToricPosition enemyPosition;
};

#endif // INFORMATIONPHEROMONE_HPP
