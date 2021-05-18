#ifndef LOADER_HPP
#define LOADER_HPP
#include <string>
#include <fstream>

class Loader
{
public:
    Loader();
};

/*!
 * @brief Loads map from .map file
 *
 * @param std::string const& filepath
 *
 * @note
 */
void loadMap(std::string const& filepath);




#endif // LOADER_HPP
