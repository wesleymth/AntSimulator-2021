/*
 * POOSV
 * 2020-21
 * Marco Antognini & Jamila Sam
 */
#pragma once

#include <Application.hpp>
#include <Environment/Environment.hpp>


class Food;


class FoodTest : public Application
{
public:
    FoodTest(int argc, char const** argv)
        : Application(argc, argv)
    {
    }
    virtual ~FoodTest() = default;
    virtual void onRun() override final;
    virtual void onEvent(sf::Event event, sf::RenderWindow& window) override final;
protected:
    virtual std::string getHelpTextFile() const override final;
    void populate();
private:
    Food* lastCreated = nullptr;
};


