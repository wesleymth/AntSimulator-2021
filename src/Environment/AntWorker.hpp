#ifndef ANTWORKER_HPP
#define ANTWORKER_HPP
#include "Ant.hpp"

class AntWorker : public Ant
{
public:
    AntWorker(const Vec2d& pos, Uid id);

    AntWorker();

    /*!
     *  @brief draws AntWorker
     *
     *  @note if debug on you can see a line representing the direction vector
     */
    void drawOn(sf::RenderTarget& target) const;
};

#endif // ANTWORKER_HPP
