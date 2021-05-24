#ifndef STATS_HPP
#define STATS_HPP
#include <vector>
#include <memory>
#include <utility>
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "Graph.hpp"
#include <unordered_map>

typedef std::pair<std::string, std::unique_ptr<Graph>> GraphAndLabel ;

typedef std::unordered_map<int,GraphAndLabel> Graphs ;

    //   STRUCTURE
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
    //               Graphs
    //                      ^     ^
    //                    GraphAndLabel(pair)


class Stats : public Drawable, public Updatable
{
public:
    /*!
     *  @brief default constructor
     *
     *  @note sets activeId to 0
     */
    Stats();

    /*!
     *  @brief sets activeId of stats to draw to desired id
     *
     *  @param id desired id
     */
    void setActiveId(int id);

    /*!
     *  @brief gets the title of the graph corrsponding to the active id
     *
     *  @param graph title in string form
     *
     *  @note uses method fin() from unordered maps
     */
    std::string getCurrentTitle() const;

    /*!
     *  @brief goes to the next id in the Graphs
     */
    void next();

    /*!
     *  @brief goes to the previous id in the Graphs
     */
    void previous();

    /*!
     *  @brief resets all graphs
     *
     *  @note calls reset() method of Graph class
     */
    void reset();

    /*!
     *  @brief adds a graphs to the corresponding id and makes active id equal to id
     *
     *  @param id desired id, which becomes active
     *  @param title of the graph
     *  @param series
     *  @param min of graph
     *  @param max of graph
     *  @param size of graph
     *
     *  @note calls the method reset() from unique_ptrs
     */
    void addGraph(int id,
                   const std::string &title,
                   const std::vector<std::string> &series,
                   double min,
                   double max,
                   const Vec2d &size);

    /*!
     *  @brief draws the graph corresponding to the active id
     *
     *  @param target window
     *
     *  @note calls find() method from unordered maps
     *  @note calls drawOn() method from Graph class
     */
    void drawOn(sf::RenderTarget& target) const override;

    /*!
     *  @brief updates
     *
     *  @param dt a time
     *
     *  @note works periodically using attribute timeLastUpdate
     *  @note calls updateData from Graph class
     *  @note gets the new data using getAppEnv().fetchData(graph_title)
     */
    void update(sf::Time dt) override;

private:
    Graphs graphs;
    int activeId;
    sf::Time timeLastUpdate;
};

#endif // STATS_HPP
