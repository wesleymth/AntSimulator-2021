#ifndef ANTWORKER_HPP
#define ANTWORKER_HPP
#include "Ant.hpp"

class AntWorker : public Ant
{
public:
    AntWorker(const Vec2d& pos, Uid id);

    AntWorker();

    sf::Sprite getSprite() const;

    void turnAround();

    void update(sf::Time dt);

    void drawOn(sf::RenderTarget& target) const;

private:
    Quantity carriedFood;
};

#endif // ANTWORKER_HPP
