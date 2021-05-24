/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#ifndef TERMITE_HPP
#define TERMITE_HPP
#include "Animal.hpp"
#include "../Interface/Savable.hpp"

/*!
 * @class Termite
 *
 * @inherits Animal
 *
 * @brief Represents a Termite
 */
class Termite : public Animal, public Savable
{
public:
    /*!
     *  @brief gets the counted number of termites in environment
     *
     *  @return number of termites in environemnt
     */
    static int getCount();


    /*!
     *  @brief default constructor
     */
    Termite();

    /*!
     *  @brief default destructor
     *
     *  @note decrements count
     */
    ~Termite();

    /*!
     *  @brief constructor with specific attributes
     *
     *  @param TP position in ToricPosition form
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of Animal
     *  @note increments count
     */
    Termite(const ToricPosition& pos);

    /*!
     *  @brief constructor with specific attributes
     *
     *  @param pos position in Vec2d form
     *  @param uid the anthill it belongs to's uid
     *
     *  @note calls constructor of Termite using TP constructor
     */
    Termite(const Vec2d& pos);

    /*!
     *  @brief gets speed of termite
     *
     *  @note returns getAppConfig().termite_speed
     */
    double getSpeed() const override;


    /*!
     *  @brief gets strength of termite
     *
     *  @note returns getAppConfig().termite_strength
     */
    int getStrength() const override;

    /*!
     *  @brief gets attack delay of termite
     *
     *  @note returns getAppConfig().termite_attack_delay;
     */
    double getAttackDelay() const override;

    /*!
     *  @brief gets sprite of a termite
     *
     *  @return sf::Sprite of an ant termite
     */
    sf::Sprite getSprite() const override;

    /*!
     *  @brief returns true if animal in parameter is an enemy
     *
     *  @param Animal const* animal
     *
     *  @note uses double dispatch with isEnemyDispatch. Override of pure virtual method in animal
     */
    bool isEnemy(Animal const* animal) const override;

    /*!
     *  @brief double dipatch fonction to allow polymorphism without type testing
     *
     *  @param Termite const* other
     *
     *  @return bool
     *
     *  @note Override of pure virtual method in animal
     */
    bool isEnemyDispatch(Termite const* other) const override;

    /*!
     *  @brief double dipatch fonction to allow polymorphism without type testing
     *
     *  @param Ant const* other
     *`
     *  @return bool
     *
     *  @note Override of pure virtual method in animal
     */
    bool isEnemyDispatch(Ant const* other) const override;


    /*!
     *  @brief Writes information to recreate current this
     *
     *  @param std::ofstream &stream
     *
     *  @note Override of pure virtual method in animal
     */
    void writeLine(std::ofstream &stream) const override;

private:
    static int count;
};

#endif // TERMITE_HPP
