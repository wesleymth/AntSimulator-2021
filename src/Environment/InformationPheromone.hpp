#ifndef INFORMATIONPHEROMONE_HPP
#define INFORMATIONPHEROMONE_HPP
#include "Pheromone.hpp"
#include "Anthill.hpp"

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
     *  @note
     */
    void update(sf::Time dt) override;

    /*!
     *  @brief draw a pheromone on a window
     *
     *  @param target window
     */
    void drawOn(sf::RenderTarget &target) const override;



private:
    Uid allowedReading;
    Anthill* enemy;
    ToricPosition enemyPosition;
};

#endif // INFORMATIONPHEROMONE_HPP
