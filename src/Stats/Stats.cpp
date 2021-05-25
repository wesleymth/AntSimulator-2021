#include "Stats.hpp"
#include "../Application.hpp"
#include <utility>

Stats::Stats()
    :activeId(0), timeLastUpdate(sf::Time::Zero)
{
    //Dones
}

void Stats::setActiveId(int id)
{
    activeId = id;
}

std::string Stats::getCurrentTitle() const
{
    return graphs.find(activeId)->second.first;
}

void Stats::next()
{
    activeId += 1;
    if (activeId > graphs.size()-1)
    {
        activeId = 0; //if it is too big bring it back to zero
    }
}

void Stats::previous()
{
    activeId -= 1;
    if ((activeId) < 0)
    {
        activeId = graphs.size()-1; //if it less than zero bring it back to zero
    }
}

void Stats::reset()
{
    for(auto& graph : graphs)
    {
        graph.second.second->reset();
    }
}

void Stats::addGraph( int id,
               const std::string &title,
               const std::vector<std::string> &series,
               double min,
               double max,
               const Vec2d &size)
{

    graphs[id].second.reset(new Graph(series,size,min,max)); //resets the graph with a new graph
    graphs[id].first = title;
    setActiveId(id);
}

void Stats::drawOn(sf::RenderTarget& target) const
{
    graphs.find(activeId)->second.second->drawOn(target);
}

void Stats::update(sf::Time dt)
{
    timeLastUpdate += dt; //increments timeLastUpdate by time passed since last update

    if (timeLastUpdate > sf::seconds(getValueConfig()["stats"]["refresh rate"].toDouble())) { //if it has been a while since a food was generated
        for (auto& graph:graphs)
        {
            graph.second.second->updateData(timeLastUpdate, getAppEnv().fetchData(graph.second.first)); //updates graph by getting new data
        }
        timeLastUpdate = sf::Time::Zero; //sets back timeLastUpdate attribute to 0
    }
}
