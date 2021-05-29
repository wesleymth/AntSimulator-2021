/*
 * POOSV 2020-21
 * @authors: BELISSENT Guillaume, MONTEITH-FINAS Wesley
 * @group: 76
 */

#ifndef ANTHILL_HPP
#define ANTHILL_HPP
#include "../Utility/Types.hpp"
#include "Positionable.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "../Interface/Savable.hpp"

enum AnthillState {Prosper,War, Decay};

/*!
 * @class Anthill
 *
 * @brief Represents and manages the aspects of an anthill
 *
 * @inherits Positionable, Drawable, Updatable
 */

class Anthill : public Positionable, public Drawable, public Updatable, public Savable
{
public:
    /*!
     *  @brief gets the counted number of Anthills in environment
     *
     *  @return number of anthills in environemnt
     */
    static int getCount();

    /*!
     *  @brief default constructor
     */
    Anthill();

    /*!
     *  @brief default destructor
     *
     *  @note decrements count
     */
    ~Anthill();

    /*!
     *  @brief constructor with specific position
     *
     *  @param TP position in ToricPosition form
     *
     *  @note creates a uid using creatUid() from Utility.hpp
     */
    Anthill(const ToricPosition& TP);

    /*!
     *  @brief constructor with specific position
     *
     *  @param TP position in ToricPosition form
     *
     *  @note calls Anthill constructor using ToricPosition(pos)
     */
    Anthill(const Vec2d& pos);

    /*!
     *  @brief constructor with specific position
     *
     *  @param TP position in ToricPosition form
     *  @param Uid uid
     *
     *  @note sets foodStock to getAppConfig().DEFAULT_ANTHILL_FOODSTOCK
     *  @note generates an ant worker when created
     *  @note sets state to Prosper
     *  @note sets enemy to nullptr
     *  @note sets timeLastSpawn and warTime to sf::Time::Zero
     *  @note increments count
     */
    Anthill(const ToricPosition& TP, Uid id);

    /*!
     *  @brief gets the probability of generating an ant worker
     *
     *  @return getAppConfig().anthill_worker_prob_default
     */
    double getWorkerProb() const;

    /*!
     *  @brief gets the anthill's uid
     *
     *  @return uid
     */
    Uid getUid() const;

    /*!
     *  @brief gets the anthill's foodStock
     *
     *  @return foodStock
     */
    Quantity getFoodStock() const;

    /*!
     *  @brief adds food to the foodStock
     *
     *  @param received quantity received
     *
     *  @note doesn't do anything for negative received
     */
    void receiveFood(Quantity received);

    /*!
     *  @brief removes food from the foodStock
     *
     *  @param Quantity removed
     *
     *  @note doesn't do anything for negative received
     */
    void consumeFood(Quantity removed);

    /*!
     *  @brief draws anthill
     *
     *  @param target window
     *
     *  @note if debug on, shows foodStock in black, uid in magenta, hp in red, if in a war shows enemy's uid
     */
    void drawOn(sf::RenderTarget& target) const override;

    /*!
     *  @brief updates anthill
     *
     *  @param dt time passed
     *
     *  @note generates random ant depending on probability of getting a worker every anthill_spawn_delay using generateAnt()
     *  @note can make the anthill go to war with another anthill
     *  @note has three states: if in war mode focalises on attcking the enemy,
     *  if it has foodstock and no enemy it is in prosper mode and can regenerate its health points
     *  if it has no foodstock the anthill is in decay mode and it loses healthpoints periodically
     */
    void update(sf::Time dt) override;

    /*!
     *  @brief checks if a given uid is the same as the anthill's uid
     *
     *  @return true if both uids are equal
     */
    bool uidIsEqual(Uid checkId) const;

    /*!
     *  @brief Writes information to recreate current this
     *
     *  @param std::ofstream &stream
     */
    void writeLine(std::ofstream &stream) const override;

    /*!
     *  @brief takes away healthpoints
     */
    void receiveDamage(double damage);

    /*!
     *  @brief checks if a given anthill is still alive
     *
     *  @return true if healthpoints<=0
     */
    bool isDead() const;

    /*!
     *  @brief checks if enemy is found
     *
     *  @return enemy != nullptr
     */
    bool foundEnemy() const;

    /*!
     *  @brief checks if the time given for war is over
     *
     *  @return true if warTime superior than default war time
     *
     *  @note uses sf::seconds(...)
     */
    bool warTimeOver() const;

    /*!
     *  @brief receives all the info of enemy attributes to start a war
     */
    void receiveEnemyInfo(Anthill* newEnemy, const ToricPosition& newEnemyPos);
private:
    static int count;
    Uid uid;
    Quantity foodStock;
    sf::Time timeLastSpawn;
    double healthPoints;
    AnthillState state;
    Anthill* enemy;
    ToricPosition enemyPosition;
    sf::Time warTime;

    /*!
     *  @brief generates an ant worker in the environment attached to the anthill
     *
     *  @note costs a certain amount of food, if it doesn't have enough it will not spawn it
     *  @note for antworkers the cost is zero
     */
    void generateAntWorker();

    /*!
     *  @brief generates an ant soldier in the environment attached to the anthill
     *
     *  @note costs a certain amount of food, if it doesn't have enough it will not spawn it
     */
    void generateAntSoldier();

    /*!
     *  @brief generates an ant queen in the environment that will go make a new anthill further than this anthill
     *
     *  @note costs a certain amount of food, if it doesn't have enough it will not spawn it
     */
    void generateAntQueen();

    /*!
     *  @brief generates an ant kamikaze in the environment attached to the anthill
     *
     *  @note costs a certain amount of food, if it doesn't have enough it will not spawn it
     */
    void generateAntKamikaze();

    /*!
     *  @brief generates an ant scout in the environment attached to the anthill
     *
     *  @note costs a certain amount of food, if it doesn't have enough it will not spawn it
     */
    void generateAntScout();

    /*!
     *  @brief generates an ant soldier made for war in the environment
     *
     *  @note costs a certain amount of food, if it doesn't have enough it will not spawn it
     *  @note sets its direction towards the enemy anthill
     */
    void generateWarAntSoldier();

    /*!
     *  @brief generates an ant kamikaze made for war in the environment
     *
     *  @note costs a certain amount of food, if it doesn't have enough it will not spawn it
     *  @note sets its condition to KillTarget with the target being the anthill's enemy
     */
    void generateWarAntKamikaze();

    /*!
     *  @brief generates an ant out of the four different types using probabilities from app.json
     *
     *  @note uses uniform() from Random.hpp
     *  @note probabilities of each ant types depend on the state of the anthill:
     *  if it is prospering it will generate more workers and scouts
     *  if it is decaying it can only generate ant workers because it is necessary to fing food
     *  if it in war mode it will focus on attacking and generate more kamikazes and soldier ready to attack
     */
    void generateAnt();

    /*!
     *  @brief generates a pair of kamikaze and soldier ants to begin to try to destroy the enemy anthill
     *
     *  @note only called once at the beginning of the war
     *  @note costs a certain amount of food, if it doesn't have enough it will not spawn them
     */
    void generateSoldierKamikazePair();
};

#endif // ANTHILL_HPP
