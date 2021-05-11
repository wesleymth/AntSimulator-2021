#include "Stats.hpp"
#include "../Application.hpp"
#include <utility>

Stats::Stats()
{

}

void Stats::setActiveId(int id) //permettant d'affecter la valeur id à l'identifiant actif
{
    activeId = id;
}

std::string Stats::getCurrentTitle() const //retournant le libellé du graphe courant (celui correspondant à l'identifiant actif)
{
    return graphs.find(activeId)->second.first;
}

void Stats::next() //permettant d'incrémenter l'identifiant actif (modulo le nombre de graphes: on passe à la valeur zéro si l'identifiant actif est celui du dernier graphe possible);
{
    if (activeId == graphs.size()-1)
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
        activeId = graphs.size()-1;
    }
    else
    {
        activeId -= 1;
    }
}

void Stats::reset()
{
    for (Graphs::iterator i(graphs.begin()); i!= graphs.end(); ++i)
    {
        i->second.second.reset();
    }
}

void Stats::addGraph( int id,
               const std::string &title,
               const std::vector<std::string> &series,
               double min,
               double max,
               const Vec2d &size)
{
    graphs.insert(id,std::make_pair<std::string,std::unique_ptr<Graph>>(title,new Graph(series,size,min,max)));
    activeId = id;
}

void Stats::drawOn(sf::RenderTarget& target) const
{
    graphs.find(activeId)->second.second->drawOn(target);
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
