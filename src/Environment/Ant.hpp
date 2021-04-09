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
     *  @brief
     */
    virtual sf::Sprite getSprite() const = 0;

private:
    Uid anthillID;
};

#endif // ANT_HPP
