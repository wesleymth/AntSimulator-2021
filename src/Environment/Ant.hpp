#ifndef ANT_HPP
#define ANT_HPP
#include "Animal.hpp"

class Ant : public Animal
{
public:
    Ant(const Vec2d& pos, double HP, double LT, Uid id);

    Ant(const Vec2d& pos, Uid id);

    Ant();

    /*!
     *  @brief gets speed of ant
     *
     *  @note returns getAppConfig().ant_speed
     */
    virtual double getSpeed() const;

    /*!
     *  @brief draws ant
     *
     *  @note if debug on you can see a line representing the direction vector and HP value
     */
    void drawOn(sf::RenderTarget& target) const;

    /*!

     *  @brief places pheromones from last placed pheromone to current position
     *
     *  @note
     */
    void spreadPheromones();

    /*!
     *  @brief makes ants move
     *
     *  @note calls Animal::Move and spreads pheromones
     */
    virtual void move(sf::Time dt);

    virtual sf::Sprite getSprite() const = 0;

    void drawPheromoneAngles(sf::RenderTarget& target) const;

    RotationProbs computeRotationProbs() const;

    //getter de anthillID
protected: //passer en private
    Uid anthillID;
    ToricPosition lastPheromone;
};

#endif // ANT_HPP
