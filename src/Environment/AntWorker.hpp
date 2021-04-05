#ifndef ANTWORKER_HPP
#define ANTWORKER_HPP
#include "Ant.hpp"

class AntWorker : public Ant
{
public:
    AntWorker(const Vec2d& pos, Uid id);

    AntWorker();

    sf::Sprite getSprite() const;
};

#endif // ANTWORKER_HPP
