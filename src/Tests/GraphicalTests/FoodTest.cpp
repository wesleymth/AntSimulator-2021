/*
 * POOSV
 * 2020-21
 * Marco Antognini & Jamila Sam
 */
#include <Config.hpp>
#include <Environment/Environment.hpp>
#include <Environment/Food.hpp>
#include "FoodTest.hpp"


IMPLEMENT_MAIN(FoodTest)

void FoodTest::onRun()
{
    // Basic setup
    Application::onRun();
    // add graphs for statistics
    setStats(false);
    populate();
}
std::string FoodTest::getHelpTextFile() const
{
    return RES_LOCATION + "food-test-help.txt";
}

void FoodTest::populate()
{
    getAppEnv().reset(); // starts with an empty environment
}

void FoodTest::onEvent(sf::Event event, sf::RenderWindow& window)
{

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // UNCOMMENT WHEN CLASS FOOD IS CODED

        lastCreated = new Food(getCursorPositionInView(), 50);
        getAppEnv().addFood(lastCreated);

    }


    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        default:
            break;

        case sf::Keyboard::T:
            // UNCOMMENT WHEN CLASS FOOD IS CODED

            if (lastCreated != nullptr)
                lastCreated->takeQuantity(15);

            break;
        }

    }

}



