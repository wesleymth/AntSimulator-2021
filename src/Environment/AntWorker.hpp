/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#ifndef ANTWORKER_HPP
#define ANTWORKER_HPP
#include "Ant.hpp"

/*!
 * @class AntWorker
 *
 * @brief Represents and manages the aspects of an ant worker, which can interact with food instances and other animals
 *
 * @inherits Ant
 */

class AntWorker : public Ant
{
public:
    /*!
     *  @brief gets the counted number of AntWorkers in environment
     *
     *  @return number of ant workers in environemnt
     */
    static int getCount();


    /*!
     *  @brief default constructor
     */
    AntWorker();

    /*!
     *  @brief default destructor
     *
     *  @note decrements count
     *  @note the antworker drops its food if it dies while carrying food
     */
    ~AntWorker();

    /*!
     *  @brief constructor with specific attributes
     *
     *  @param TP position in ToricPosition form
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of Ant
     *  @note increments count
     */
    AntWorker(const ToricPosition& TP, Uid uid);

    /*!
     *  @brief constructor with specific attributes
     *
     *  @param pos position in Vec2d form
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of AntWorker using TP.toVec2d() as pos
     */
    AntWorker(const Vec2d& pos, Uid id);

    /*!
     *  @brief gets sprite of an ant worker
     *
     *  @return sf::Sprite of an ant worker
     */
    sf::Sprite getSprite() const override;

    /*!
     *  @brief gets strength of an ant worker
     *
     *  @return return getAppConfig().ant_worker_strength
     */
    int getStrength() const override;

    /*!
     *  @brief updates an ant worker
     *
     *  @note calls Animal::update(dt) and adds specific behaviour regarding foods
     */
    void update(sf::Time dt) override;

    /*!
     *  @brief draws an ant worker
     *
     *  @note calls Ant::drawOn(target) and if debug on you can see carriedFood in black and anthillUid in magenta
     */
    void drawOn(sf::RenderTarget& target) const override;

private:
    static int count;
    Quantity carriedFood;

};

#endif // ANTWORKER_HPP
