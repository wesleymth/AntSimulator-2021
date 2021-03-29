/*
 * POOSV
 * 2020-21
 * Marco Antognini & Jamila Sam
 */
#include <Config.hpp>
#include <Environment/Environment.hpp>
#include <Environment/Animal.hpp>
#include "AnimalTest.hpp"


IMPLEMENT_MAIN(AnimalTest)

void AnimalTest::onRun()
{
    // Basic setup
    Application::onRun();
	// add graphs for statistics
	setStats(false);
	populate();
}
std::string AnimalTest::getHelpTextFile() const
{
	 return RES_LOCATION + "animal-test-help.txt";
}

void AnimalTest::populate()
{
	getAppEnv().reset(); // starts with an empty environment
}


void AnimalTest::onEvent(sf::Event event, sf::RenderWindow& window)
{

	if(event.type==sf::Event::KeyPressed)
    {
      switch(event.key.code)
	  {
                  case sf::Keyboard::A:
			  // UNCOMMENT WHEN ANIMAL Ctor IS CODED
              /*
              getAppEnv().addAnimal(new Animal(getCursorPositionInView(),
                                               1.0,
											   getAppConfig().animal_default_lifespan
											   ));
              */
			  break;
		  default: /*nothing to do*/
			  break;
	  }
	  
	}
	
}



