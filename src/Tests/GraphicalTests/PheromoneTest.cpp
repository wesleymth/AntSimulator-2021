/*
 * POOSV
 * 2020-21
 * Marco Antognini & Jamila Sam
 */

#include <Config.hpp>
#include <Environment/Environment.hpp>
#include <Environment/Pheromone.hpp>
#include "PheromoneTest.hpp"


IMPLEMENT_MAIN(PheromoneTest)

void PheromoneTest::onRun()
{
    // Basic setup
    Application::onRun();
    // add graphs for statistics
    setStats(false);
//	resetStats();
    populate();
}

std::string PheromoneTest::getHelpTextFile() const
{
    return RES_LOCATION + "pheromon-test-help.txt";
}

void PheromoneTest::populate()
{
    getAppEnv().reset();
    delete mAnt;
    mAnt = nullptr;
    const auto x(getAppConfig().simulation_size);
    const auto y(x);
    ToricPosition pos(x/2,y/2);
    mAnt = new AntWorker(pos, mAntId);
}

void PheromoneTest::onUpdate(sf::Time dt)
{
    // When in «live» mode, update our «special» ant like the others
    if (mAnt!= nullptr and mLive) {
        mAnt->update(dt);
    }
}

void PheromoneTest::onDraw(sf::RenderTarget& target)
{
    if (mAnt != nullptr) {

        mAnt->drawOn(target); // add a debug mode
    }
}

void PheromoneTest::onEvent(sf::Event event, sf::RenderWindow&)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        default:
            break;

        case sf::Keyboard::P:
            getAppEnv().togglePheromoneDisplay();
            break;
        case sf::Keyboard::A:
            getAppEnv().addAnimal(new AntWorker(getCursorPositionInView(), createUid()));
            break;
        case sf::Keyboard::Return:
            mLive = !mLive; // toggle «live» mode
            break;

        case sf::Keyboard::S: {
            mAnt->update(sf::seconds(0.05f));
        }

        break;
        case sf::Keyboard::Q: {
            getAppConfig().switchProbaDebug();
        }

        break;
        }
    }

    // Generate segment of pheromones
    if (event.type == sf::Event::MouseButtonPressed) {
        if (mWasFirstClick) { // yes

            // Spawns enough pheromone between `end` and `start` based on
            // the pheromone density (with no handling of the toric world)
            auto const end = getCursorPositionInView();
            auto const start = mFirstClick;
            auto const NB_STEPS_PER_PIXEL = getAppConfig().pheromone_test_density;
            auto const direction = end - start;
            auto const nb_steps = direction.length() * NB_STEPS_PER_PIXEL;
            auto const step = direction / nb_steps;
            for (int i = 0; i < nb_steps; ++i) {
                getAppEnv().addPheromone(new Pheromone(start + i * step, 5.0));
            }

            // If shift key pressed then link the segment's start with this one's end.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
                mFirstClick = getCursorPositionInView();
            } else {
                mWasFirstClick = false;
            }
        } else { // no, first click only
            mWasFirstClick = true;
            mFirstClick = getCursorPositionInView();
        }
    }
}
