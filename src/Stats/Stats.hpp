#ifndef STATS_HPP
#define STATS_HPP
#include <vector>
#include <memory>
#include <utility>
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "Graph.hpp"

struct Graphs
{
    std::vector<std::unique_ptr<Graph>> collectionOfGraphs;
    std::vector<std::string> labels;
    std::vector<int> ids;
};

struct L
{
    std::vector<std::string> graphNames;
    std::vector<int> ids;
};

typedef std::vector<std::unique_ptr<Graph>> G ;

typedef std::vector<std::string> Labels;


class Stats : public Drawable, public Updatable
{
public:
    Stats();
    void setActiveId(int id);
    std::string getCurrentTitle() const;
    void next();
    void previous();
    void reset();
    void addGraph( int id,
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
