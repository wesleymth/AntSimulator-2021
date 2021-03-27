/*
 * prjsv 2020
 *
 * Marco Antognini & Jamila Sam
 */

#include <Application.hpp>
#include <Environment/Positionable.hpp>
#include <Random/Random.hpp>
#include <Environment/ToricPosition.hpp>
#include <Tests/UnitTests/CheckUtility.hpp>
#include <iostream>
#include <catch.hpp>


class TestPositionable : public Positionable 
{
public:
	// to access the protected members
	TestPositionable(const ToricPosition& tp)
		:Positionable(tp)
		{}
	TestPositionable()
		:Positionable()
		{}
	
	void setPosition(ToricPosition const& position)
		{
			Positionable::setPosition(position);
		}
};


SCENARIO("Constructors", "Positionable ")
{
    GIVEN("A positionable created by default constructor")
    {
		TestPositionable pos;

        THEN("coordinates must be zero (checked with getPosition)")
        {
			CHECK_APPROX_EQUAL(pos.getPosition()[0], 0.0);
			CHECK_APPROX_EQUAL(pos.getPosition()[1], 0.0);
        }
    }
	

    GIVEN("A positionable with ToricPosition(simulation_size/2 and simulation_size/2)")
    {
		auto const width  = getAppConfig().simulation_size;
		auto const height = getAppConfig().simulation_size;
		TestPositionable pos(ToricPosition(width/2, height/2));
		std::cerr << "simulation_size = " << width << std::endl;
        THEN("coordinates must be simulation_size/2 and simulation_size/2")
        {
			CHECK_APPROX_EQUAL(pos.getPosition()[0], width/2);
			CHECK_APPROX_EQUAL(pos.getPosition()[1], height/2);

        }
    }
}

SCENARIO("Getters/Setters", "Positionable")
{
   auto const width  = getAppConfig().simulation_size;
   auto const height = getAppConfig().simulation_size;

    GIVEN("A positionable pos created at random position (x,y)")
    {
        ToricPosition tp(uniform(width,height), uniform(width,height));
        TestPositionable pos(tp);

        THEN("pos.getPosition() must be equal to ToricPosition(x,y)")
        {
            CHECK(pos.getPosition()==tp);
        }
    }

    GIVEN( " a Positionable pos constructed by default Ctor\n"\
		   " a ToricPosition tp with random coordinates (x,y) \n")
	{
        THEN ("The coordinates of pos after the call pos.setPosition(tp)"\
			  "must be \n (x,y)")
        {
            for (size_t i(0); i < 50; ++i){
                TestPositionable pos;
                ToricPosition tp(uniform(width,height), uniform(width,height));
                pos.setPosition(tp);
                CHECK(pos.getPosition() == tp);
            }
        }
    }
}



SCENARIO("operator<<", "Positionable")
{
    GIVEN("A Positionable p constructed at (10., 10.)")
    {
        ToricPosition tp (10,10);
        TestPositionable pos(tp);
        std::ostringstream out;
        std::ostringstream expected_out;
        THEN("The output of display() must be the same as the one \n produced by operator<< ToricPosition(10, 10)")
        {
            out.str(""); out.clear();
            pos.display(out);
            expected_out << tp;
            CHECK(out.str()==expected_out.str());
        }
        THEN("display of p with operator<< must be [10, 10]")
        {
            out.str(""); out.clear();
            out << pos;
            expected_out << tp;
            CHECK(out.str()==expected_out.str());
        }
    }

}



