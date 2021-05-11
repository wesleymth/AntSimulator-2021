#ifndef STATS_HPP
#define STATS_HPP
#include <vector>
#include <memory>
#include <utility>
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "Graph.hpp"
#include <unordered_map>

typedef std::pair<std::string, std::unique_ptr<Graph>> GRAPH ;

typedef std::unordered_map<int,GRAPH> Graphs ;

    //   GRAPHS STRUCTURE
    //
    //   -------------------------------
    //   |            |       |        |
    //   |            |       |        |
    //   |            |       |        |
    //   |     id     | title | Graph* |
    //   |   (first)  |(second|(second |
    //   |            |.first |.second |
    //   |            |   )   |   )    |
    //   -------------------------------
    //          ^             ^
    //              1st pair
    //                      ^     ^
    //                      2nd pair


class Stats : public Drawable, public Updatable
{
public:
    Stats();
    void setActiveId(int id);
    std::string getCurrentTitle() const;
    void next();
    void previous();
    void reset();
    void addGraph(int id,
                   const std::string &title,
                   const std::vector<std::string> &series,
                   double min,
                   double max,
                   const Vec2d &size);
    void drawOn(sf::RenderTarget& target) const override;
    void update(sf::Time dt) override;

private:
    Graphs graphs;
    int activeId;
    sf::Time timeLastUpdate;
};

#endif // STATS_HPP
