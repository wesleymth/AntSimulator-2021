#ifndef ANTHILL_HPP
#define ANTHILL_HPP
#include "../Utility/Types.hpp"
#include "Positionable.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"


class Anthill : public Positionable, public Drawable, public Updatable
{
public:
    Anthill();

    Anthill(const Vec2d& pos);

    Anthill(const ToricPosition& TP);

    void receiveFood(Quantity received);

    void drawOn(sf::RenderTarget& target) const;

    void update(sf::Time dt);

    double getWorkerProb() const;

    bool uidIsEqual(Uid checkId) const;



private:
    Uid uid;
    Quantity foodStock;
    sf::Time timeLastSpawn;

    void generateAntWorker() const;

    void generateAntSoldier() const;

    void generateAnt() const;

};

#endif // ANTHILL_HPP
