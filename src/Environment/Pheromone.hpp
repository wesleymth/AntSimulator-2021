/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#ifndef PHEROMONE_HPP
#define PHEROMONE_HPP
#include "Positionable.hpp"
#include "./Interface/Updatable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>
#include "../Interface/Drawable.hpp"
#include "./Interface/Updatable.hpp"
#include "Anthill.hpp"

//Cette façon simple de modéliser la phéromone sera potentiellement gourmande en ressources.
//Vous pourrez proposer des alternatives plus efficaces dans la partie « extensions » du projet.

/*!
 * @class Pheromone
 *
 * @inherits Positionable, Drawable, Updatable
 *
 * @brief Represents a Pheromone
 */
class Pheromone: public Positionable, public Drawable, public Updatable
{
public:
    /*!
     *  @brief default constructor
     */
    Pheromone();

    /*!
     *  @brief constructor that initialises position and quantity
     *
     *  @param vect const Vec2d&
     *  @param quant Quantity
     */
    Pheromone( const Vec2d& vect, Quantity quant);

    /*!
     *  @brief constructor that initialises position and quantity
     *
     *  @param vect const ToricPosition&
     *  @param quant Quantity
     */
    Pheromone(const ToricPosition &vect, Quantity quant);

    /*!
     *  @brief in charge of decreasing quatity of pheromones at a set interval
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

    /*!
     *  @brief returns true if quantity of of pheromone is below threshold
     *
     *  @param target window
     *
     *  @note uses getAppConfig().pheromone_threshold for food threshold
     */
    bool isNegligeable() const;

    /*!
     * @brief gets the quatity
     *
     * @return quantity in Quantity form
     */
    Quantity getQuantity() const;

    /*!
     * @brief makes the pheromone evaporate
     */
    void evaporate(Quantity takeAway);

    /*!
     * @brief can an ant interact with the pheromone
     *
     * @return true of false
     */
    virtual bool interact() const=0;

    /*!
     * @brief gets the enemy if it is an info pheromone
     *
     * @return nullptr or enemy
     */
    virtual Anthill* getEnemy() const=0;

    /*!
     * @brief gets the enemy's position if it is an info pheromone
     *
     * @return default ToricPosition or enemyPosition
     */
    virtual ToricPosition getEnemyPosition() const=0;


private:
    Quantity quantity;
};

#endif // PHEROMONE_HPP
