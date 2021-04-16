#ifndef ANTHILL_HPP
#define ANTHILL_HPP
#include "../Utility/Types.hpp"
#include "Positionable.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"


class Anthill : public Positionable, public Drawable, public Updatable
{
public:
    /*!
     *  @brief default constructor
     */
    Anthill();

    /*!
     *  @brief constructor with specific position
     *
     *  @param TP position in ToricPosition form
     *
     *  @note creates a uid using creatUid() from Utility.hpp
     *  @note sets foodStock and timeLastSpawn to 0
     *  @note generates an ant when created using generateAnt()
     */
    Anthill(const ToricPosition& TP);

    /*!
     *  @brief constructor with specific position
     *
     *  @param TP position in ToricPosition form
     *
     *  @note calls Anthill constructor using ToricPosition(pos)
     */
    Anthill(const Vec2d& pos);

    /*!
     *  @brief gets the probability of generating an ant worker
     *
     *  @return getAppConfig().anthill_worker_prob_default
     */
    double getWorkerProb() const;

    /*!
     *  @brief adds food to the foodStock
     *
     *  @param received quantity received
     *
     *  @note doesn't do anything for negative received
     */
    void receiveFood(Quantity received);

    /*!
     *  @brief draws anthill
     *
     *  @param target window
     *
     *  @note if debug on, shows foodStock in black and uid in magenta
     */
    void drawOn(sf::RenderTarget& target) const override;

    /*!
     *  @brief updates anthill
     *
     *  @param dt time passed
     *
     *  @note generates random ant depending on probability of getting a worker every anthill_spawn_delay using generateAnt()
     */
    void update(sf::Time dt) override;

    /*!
     *  @brief checks if a given uid is the same as the anthill's uid
     *
     *  @return true if both uids are equal
     */
    bool uidIsEqual(Uid checkId) const;

private:
    Uid uid;
    Quantity foodStock;
    sf::Time timeLastSpawn;

    /*!
     *  @brief generates an ant worker in the environment
     */
    void generateAntWorker() const;

    /*!
     *  @brief generates an ant soldier in the environment
     */
    void generateAntSoldier() const;

    /*!
     *  @brief generates an ant depending on a uinform law and the probability of getting a worker
     *
     *  @note uses uniform() from Random.hpp
     */
    void generateAnt() const;

};

#endif // ANTHILL_HPP
