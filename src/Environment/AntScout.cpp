#include "AntScout.hpp"
#include "../Utility/Constants.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "InformationPheromone.hpp"
#include "RegularPheromone.hpp"

int AntScout::count = 0;

int AntScout::getCount()
{
    return count;
}

AntScout::AntScout()
    :AntScout(Vec2d(getAppConfig().world_size/2,getAppConfig().world_size/2), DEFAULT_UID)
{
    //Done
}

AntScout::~AntScout()
{
    --count;
    target = nullptr;
}

AntScout::AntScout(const ToricPosition& TP, Uid uid)
    :Ant::Ant(TP, ANT_SCOUT_HP, ANT_SCOUT_LIFE, uid),
      target(nullptr),
      targetPosition(getAppConfig().world_size/2,getAppConfig().world_size/2),
      condition(Roam),
      timeSpreadInpho(sf::Time::Zero)
{
    ++count;
}

AntScout::AntScout(const Vec2d& pos, Uid uid)
    :AntScout(ToricPosition(pos),uid)
{
    //Done
}

sf::Sprite AntScout::getSprite() const
{
    return buildSprite((getPosition()).toVec2d(),
                       DEFAULT_ANT_SIZE,
                       getAppTexture(ANT_SCOUT_SPRITE),
                       getDirection()/DEG_TO_RAD);
}

int AntScout::getStrength() const
{
    return ANT_SCOUT_STRENGTH;
}

bool AntScout::foundTarget() const
{
    return (target != nullptr);
}

bool AntScout::roaming() const
{
    return (condition == Roam);
}

void AntScout::saveTargetInfo(Anthill *victim)
{
    target = victim;
    targetPosition = victim->getPosition();
}

void AntScout::update(sf::Time dt)
{
    Anthill* closestAnthill(getAppEnv().getClosestAnthillForAnt(this));
    if (roaming())
    {
        if ((closestAnthill != nullptr and closestAnthill->getUid() != getAnthillUid()))
        {
            saveTargetInfo(closestAnthill);
            turnAround();
            timeSpreadInpho = sf::seconds(ANT_SCOUT_SPREAD_INPHO_TIME);
            condition = TargetAcquiered;
        }
    }
    else
    {
        if (timeSpreadInpho > sf::Time::Zero)
        {
            timeSpreadInpho -= dt;
        }
        else
        {
            condition = Roam;
        }
    }
    Animal::update(dt);
}

void AntScout::spreadPheromones()
{
    double dist(toricDistance(getPosition(),getLastPheromone()));
    Vec2d vect(getLastPheromone().toricVector(getPosition()));
    if(dist*getAppConfig().ant_pheromone_density>=1) {
        for(int i(1); i<=dist*getAppConfig().ant_pheromone_density; ++i) {
            setLastPheromone(getLastPheromone()+(i*vect/(dist*getAppConfig().ant_pheromone_density)));
            if (roaming())
            {
                getAppEnv().addPheromone(new RegularPheromone(getLastPheromone(),
                                    getAppConfig().ant_pheromone_energy));
            }
            else
            {
                getAppEnv().addPheromone(new InformationPheromone(getLastPheromone(),
                                                                  getAppConfig().ant_pheromone_energy,
                                                                  getAnthillUid(),
                                                                  target,
                                                                  targetPosition));
            }

        }
    }


}

void AntScout::drawOn(sf::RenderTarget& target) const
{
    Ant::drawOn(target);
    if (isDebugOn()) { //if debug on you can see the uid in magenta
        auto const uidText = buildText(to_nice_string(getAnthillUid()), getPosition().toVec2d()+Vec2d(0,40), getAppFont(), 15, sf::Color::Magenta);
        target.draw(uidText); //shows anthill uid via a text
        target.draw(buildAnnulus(getPosition().toVec2d(), getAppConfig().ant_smell_max_distance, sf::Color::Blue, 5)); //draws a ring around animal representing the perception distance
        auto const targetText = buildText("TARGET POS ("+ to_nice_string(targetPosition.x()) +"," + to_nice_string(targetPosition.y()) + ")",
                                          getPosition().toVec2d()+Vec2d(0,60), getAppFont(), 15, sf::Color::Magenta);
        target.draw(targetText); //shows anthill uid via a text
    }
}

