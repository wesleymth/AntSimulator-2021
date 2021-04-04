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
private:
    Uid anthillID;
};

#endif // ANT_HPP
