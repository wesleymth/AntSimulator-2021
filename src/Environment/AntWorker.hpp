#ifndef ANTWORKER_HPP
#define ANTWORKER_HPP
#include "Ant.hpp"

class AntWorker : public Ant
{
public:
    /*!
     *  @brief default constructor
     */
    AntWorker();

    /*!
     *  @brief constructor with specific attributes
     *
     *  @param TP position in ToricPosition form
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of Ant
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

    int getStrength() const override;

private:
    Quantity carriedFood;

    /*!
     *  @brief makes ant turn around
    */
    void turnAround();
};

#endif // ANTWORKER_HPP
