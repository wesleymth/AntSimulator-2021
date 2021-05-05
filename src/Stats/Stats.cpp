#include "Stats.hpp"
#include "../Application.hpp"

Stats::Stats()
{

}

void Stats::setActiveId(int id) //permettant d'affecter la valeur id à l'identifiant actif
{
    activeId = id;
}

std::string Stats::getCurrentTitle() const //retournant le libellé du graphe courant (celui correspondant à l'identifiant actif)
{
    std::string title("");
    for (auto& graph:graphs)
    {
        if (activeId == graph.first)
        {
            title = graph.second.first;
        }
    }
    return title;
}

void Stats::next() //permettant d'incrémenter l'identifiant actif (modulo le nombre de graphes: on passe à la valeur zéro si l'identifiant actif est celui du dernier graphe possible);
{
    if (activeId == graphs[graphs.size()-1].first)
    {
        activeId = 0;
    }
    else
    {
        activeId += 1;
    }
}

void Stats::previous()
{
    if ((activeId-1) < 0)
    {
        activeId = (graphs[graphs.size()-1].first);
    }
    else
    {
        activeId -= 1;
    }
}

void Stats::reset()
{
    for (auto& graph:graphs)
    {
        graph.second.second.reset();
    }
}

void Stats::addGraph( int id,
               const std::string &title,
               const std::vector<std::string> &series,
               double min,
               double max,
               const Vec2d &size)
{
    for (auto& graph:graphs)
    {
        if (id == graph.first)
        {
            graph.second.first = title;
            graph.second.second.reset(new Graph(series, size, min, max));
        }
    }
    activeId = id;
}

void Stats::drawOn(sf::RenderTarget& target) const
{

}

void Stats::update(sf::Time dt)
{
    timeLastUpdate += dt; //increments timeLastUpdate by time passed since last update

    if (timeLastUpdate > sf::seconds(getAppConfig().food_generator_delta)) { //if it has been a while since a food was generated
        for (auto& graph:graphs)
        {
            graph.second.second->updateData(timeLastUpdate, getAppEnv().fetchData(graph.second.first));
        }
        timeLastUpdate = sf::Time::Zero; //sets back timeLastUpdate attribute to 0
    }
}
