#ifndef SAVABLE_HPP
#define SAVABLE_HPP
#include <fstream>

class Savable
{
public:
    /*!
     *  @brief Writes information to recreate current this
     *
     *  @param std::ofstream &stream
     *
     *  @note Override of pure virtual method in animal
     */
    virtual void writeLine(std::ofstream& stream) const = 0;
};

#endif // SAVABLE_HPP
