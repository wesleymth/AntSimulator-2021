#ifndef ANT_HPP
#define ANT_HPP
#include "Animal.hpp"

class Ant : public Animal
{
public:
    Ant(const Vec2d& pos, double LP, double LT, Uid id);

    Ant(const Vec2d& pos, Uid id);

    Ant(); 
private:
    Uid anthillID;
};

#endif // ANT_HPP
