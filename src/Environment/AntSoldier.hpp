#ifndef ANTSOLDIER_HPP
#define ANTSOLDIER_HPP
#include "Ant.hpp"

class AntSoldier : public Ant
{
public:
    AntSoldier(const Vec2d& pos, Uid id);

    AntSoldier();

    /*!
     *  @brief draws AntSoldier
     *
     *  @note if debug on you can see a line representing the direction vector
     */
    void drawOn(sf::RenderTarget& target) const;
};

#endif // ANTSOLDIER_HPP
