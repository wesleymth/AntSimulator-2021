/*
 * prjsv 2020-21
 *
 * Marco Antognini & Jamila Sam
 */

#include <Application.hpp>
#include <Utility/Vec2d.hpp>
#include <Environment/ToricPosition.hpp>
#include <Random/Random.hpp>
#include <Utility/Utility.hpp>
#include <sstream>
#include <Tests/UnitTests/CheckUtility.hpp>
#include <Config.hpp>
#include <catch.hpp>
#include <iostream>

using namespace std;
size_t test_count(0);

SCENARIO("ToricPosition Constructors", "ToricPosition")
{

    GIVEN("A ToricPosition constructed by default Ctor")
    {
		++test_count;
		std::cerr << "Test #" << test_count << ": " << "simulation_size ="
				  <<  getAppConfig().simulation_size
				  << std::endl;
        ToricPosition p;

        THEN("coordinates must be (0.0,0.0)")
        {
           CHECK_APPROX_EQUAL(p.x(), 0.0);
           CHECK_APPROX_EQUAL(p.y(), 0.0);
        }
    }
    GIVEN("A ToricPosition constructed at simulation_size/2 and simulation_size/2")
    {
		++test_count;
		auto const width  = getAppConfig().simulation_size/2;
        auto const height = width;
		std::cerr << "Test #" << test_count << ": " << "simulation_size/2 ="
				  <<  width
				  << std::endl;
      
        ToricPosition p(width,height);

        THEN("coordinates returned by x() and y() must be simulation_size/2 and simulation_size/2")
        {
           CHECK_APPROX_EQUAL(p.x(), width);
           CHECK_APPROX_EQUAL(p.y(), height);
        }
    }

    GIVEN("A ToricPosition constructed with a Vec2d(simulation_size/4 and simulation_size/4)")
    {
		++test_count;
		
		auto const width  = getAppConfig().simulation_size/4;
        auto const height = width;
		std::cerr << "Test #" << test_count << ": " << "simulation_size/4 ="
				  <<  width
				  << std::endl;
	
        Vec2d const v(width, height);

        ToricPosition p(v);

        THEN("coordinates returned by x() and y() must be simulation_size/4 and simulation_size/4")
        {
           CHECK_APPROX_EQUAL(p.x(), width);
           CHECK_APPROX_EQUAL(p.y(), height);
        }
    }
    GIVEN("A ToricPosition constructed with a Vec2d(simulation_size, simulation_size)")
    {
		auto const width  = getAppConfig().simulation_size;
        auto const height = width;
		++test_count;
		std::cerr << "Test #" << test_count << ": " << "simulation_size ="
				  <<  width
				  << std::endl;
        Vec2d const v(width, height);

        ToricPosition p(v);

        THEN("coordinates returned by x() and y() must be  0 and 0 due to clamping")
        {
           CHECK_APPROX_EQUAL(p.x(), 0);
           CHECK_APPROX_EQUAL(p.y(), 0);
        }
    }
}

SCENARIO("operator<<", "ToricPosition")
{
    GIVEN("A ToricPosition p constructed by default Ctor")
    {
        ToricPosition p;
		++test_count;
		std::cerr << "Test #" << test_count << ": " << "simulation_size ="
				  <<  getAppConfig().simulation_size
				  << std::endl;
        THEN("The display with operator<< must be [p.x(), p.y()]")
        {
            std::ostringstream out;
            std::ostringstream expected_out;
            out << p;
            expected_out << "[" << p.x() << ", " << p.y() << "]";
            CHECK(out.str()==expected_out.str());
        }
    }
    GIVEN("A ToricPosition p constructed at simulation_size/4 and simulation_size/4")
    {
		auto const width  = getAppConfig().simulation_size/4;
        auto const height = width;
		++test_count;
		std::cerr << "Test #" << test_count << ": " << "simulation_size/4 ="
				  <<  width
				  << std::endl;
        ToricPosition p(width,height);

        THEN("The display with operator<< must be [p.x(), p.y()]")
        {
            std::ostringstream out;
            std::ostringstream expected_out;
            out << p;
            expected_out << "[" << p.x() << ", " << p.y() << "]";

            CHECK(out.str()==expected_out.str());

        }
    }
}

SCENARIO("Addition of ToricPosition and Vec2d (without wrapping)", "ToricPosition")
{
    auto const width  = getAppConfig().simulation_size;
	auto const height = width;
	++test_count;
	std::cerr << "Test #" << test_count << ": " << "simulation_size ="
			  <<  width
			  << std::endl;
    double const x1 = uniform(0,width/2), y1 = uniform(0,height/2);
    double const x2 = uniform(0,width/2), y2 = uniform(0,height/2);
    ToricPosition tp(x1,y1);
    Vec2d const to_add(x2, y2);
    std::ostringstream scenario;
    scenario << "    a ToricPosition tp is constructed at (x1,y1) = (" << x1 << ", " << y1 << ")\n";
    scenario << "    then the  Vec2d (x2,y2) =" << "(" << x2 << ", " << y2 << ") is added using += \n";
	// Test#  7
    GIVEN("Two ToricPosition far from the limits")
    {
		std::cerr << scenario.str() << std::endl;
        tp += to_add;
        THEN("the coordinates of tp must be (x1+x2, y1+y2)")
        {
            CHECK_APPROX_EQUAL(tp.x(), x1+x2);
            CHECK_APPROX_EQUAL(tp.y(), y1+y2);
        }

    }
  }


SCENARIO("Addition of ToricPosition and Vec2d (with wrapping)", "ToricPosition")
{
    auto const width  = getAppConfig().simulation_size;
	auto const height = width;
	++test_count;
	std::cerr << "Test #" << test_count << ": " << "simulation_size ="
			  <<  width
			  << std::endl;
    double const x1(width), y1 =(height);
    double const x2 = 8., y2 = 8.;
    ToricPosition tp(x1,y1);
    Vec2d to_add(x2, y2);

    std::ostringstream scenario;
    scenario << "    a ToricPosition tp is constructed at (x1,y1) = (" << x1 << ", " << y1 << ")\n";
    scenario << "    then the  Vec2d (x2,y2) =" << "(" << x2 << ", " << y2 << ") is added using += \n";

	// Test# 8
    GIVEN("Two ToricPositions with one at [width,height]")
    {
		std::cerr << scenario.str() << std::endl;
        tp += to_add;
        THEN("the coordinates of tp must be (x2, y2)")
        {
            CHECK_APPROX_EQUAL(tp.x(), x2);
            CHECK_APPROX_EQUAL(tp.y(), y2);
        }
    }
}


SCENARIO("Toric distance", "ToricPosition")
{
    const Vec2d world_size(1000., 1000.);
    auto const width  = world_size.x();
    auto const height = world_size.y();

    std::ostringstream scenario;
    scenario << "ToricPositions constructed at posA = (100, 100), posB = (900, 100), \n";
    scenario << "posC=(900, 900), posD=(100, 900) and posF=(500, 500),\n";
    scenario << "   (with WORLD_WIDTH = " << width << " and WORLD_HEIGHT = " <<  height << ") \n";
    GIVEN("Five toric positions posA, posB, posC, posD and posF")
    {
        ToricPosition posA(Vec2d(100.,100.), world_size); 
        ToricPosition posB(Vec2d(900.,100.), world_size);
        ToricPosition posC(Vec2d(900.,900.), world_size);
        ToricPosition posD(Vec2d(100.,900.), world_size);
        ToricPosition posF(Vec2d(500.,500.), world_size);
        double expected(200.);
        std::string expected_msg(to_string(expected));
        double expected2(Vec2d(400., 400.).length());
        std::string expected_msg2(to_string(expected2));

        THEN("the toric distance between posA and posB must be 200")
        {
            CHECK_APPROX_EQUAL(toricDistance(posA,posB), expected);
        }
        THEN("the toric distance between posB and posC must be " + expected_msg)
        {
            CHECK_APPROX_EQUAL(toricDistance(posB, posC), expected);
        }
        THEN("the toric distance between posC and posD must be " + expected_msg)
        {
            CHECK_APPROX_EQUAL(toricDistance(posC, posD), expected);
        }
        THEN("the toric distance between posD and posA must be " + expected_msg)
        {
            CHECK_APPROX_EQUAL(toricDistance(posD,posA), expected);
        }
        THEN("the toric distance between posA and posF must be" + expected_msg2)
        {
            CHECK_APPROX_EQUAL(toricDistance(posA,posF), expected2);
        }
    }
}

SCENARIO("Toric vector", "ToricPosition")
{
    const Vec2d world_size(1000., 1000.);
    auto const width  = world_size.x();
    auto const height = world_size.y();

    std::ostringstream scenario;
    scenario << "ToricPositions constructed at posA = (100, 100), posB = (900, 100), \n";
    scenario << "posC=(900, 900), posD=(100, 900) and posF=(500, 500),\n";
    scenario << "   (with WORLD_WIDTH = " << width << " and WORLD_HEIGHT = " <<  height << ") \n";
	 GIVEN("Five toric positions posA, posB, posC, posD and posF")	
    {
        ToricPosition posA(Vec2d(100.,100.), world_size);
        ToricPosition posB(Vec2d(900.,100.), world_size);
        ToricPosition posC(Vec2d(900.,900.), world_size);
        ToricPosition posD(Vec2d(100.,900.), world_size);
        ToricPosition posF(Vec2d(500.,500.), world_size);
        std::ostringstream message;

        Vec2d expected(0,0);
        message << expected;

        //posA with all the others
        THEN("the toric vector between posA and posA must be " + message.str())
        {
            CHECK(posA.toricVector(posA)== expected);
        }
        expected = Vec2d(-200,0);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posA and posB must be " + message.str())
        {
            CHECK(posA.toricVector(posB)== expected);
        }
        expected = Vec2d(-200,-200);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posA and posC must be " + message.str())
        {
            CHECK(posA.toricVector(posC)== expected);
        }
        expected = Vec2d(0,-200);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posA and posD must be " + message.str())
        {
            CHECK(posA.toricVector(posD)== expected);
        }
        expected = Vec2d(400,400);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posA and posF must be " + message.str())
        {
            CHECK(posA.toricVector(posF)== expected);
        }

        //posB with all the others
        expected = Vec2d(200,0);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posB and posA must be " + message.str())
        {
            CHECK(posB.toricVector(posA)== expected);
        }

        expected = Vec2d(0,0);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posB and posB must be " + message.str())
        {
            CHECK(posB.toricVector(posB)== expected);
        }
        expected = Vec2d(0,-200);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posB and posC must be " + message.str())
        {
            CHECK(posB.toricVector(posC)== expected);
        }
        expected = Vec2d(200,-200);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posB and posD must be " + message.str())
        {
            CHECK(posB.toricVector(posD)== expected);
        }
        expected = Vec2d(-400,400);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posB and posF must be " + message.str())
        {
            CHECK(posB.toricVector(posF)== expected);
        }

        //posC with all the others
        expected = Vec2d(200,200);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posC and posA must be " + message.str())
        {
            CHECK(posC.toricVector(posA)== expected);
        }

        expected = Vec2d(0,200);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posC and posB must be " + message.str())
        {
            CHECK(posC.toricVector(posB)== expected);
        }

        expected = Vec2d(0,0);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posC and posC must be " + message.str())
        {
            CHECK(posC.toricVector(posC)== expected);
        }

        expected = Vec2d(200,0);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posC and posD must be " + message.str())
        {
            CHECK(posC.toricVector(posD)== expected);
        }

        expected = Vec2d(-400,-400);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posC and posF must be " + message.str())
        {
            CHECK(posC.toricVector(posF)== expected);
        }

        //posD with all the others
        expected = Vec2d(0,200);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posD and posA must be " + message.str())
        {
            CHECK(posD.toricVector(posA)== expected);
        }

        expected = Vec2d(-200,200);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posD and posB must be " + message.str())
        {
            CHECK(posD.toricVector(posB)== expected);
        }

        expected = Vec2d(-200,0);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posD and posC must be " + message.str())
        {
            CHECK(posD.toricVector(posC)== expected);
        }

        expected = Vec2d(0,0);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posD and posD must be " + message.str())
        {
            CHECK(posD.toricVector(posD)== expected);
        }

        expected = Vec2d(400,-400);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posD and posF must be " + message.str())
        {
            CHECK(posD.toricVector(posF)== expected);
        }

        //posF with all the others
        expected = Vec2d(-400,-400);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posF and posA must be " + message.str())
        {
            CHECK(posF.toricVector(posA)== expected);
        }

        expected = Vec2d(400,-400);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posF and posB must be " + message.str())
        {
            CHECK(posF.toricVector(posB)== expected);
        }

        expected = Vec2d(400,400);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posF and posC must be " + message.str())
        {
            CHECK(posF.toricVector(posC)== expected);
        }

        expected = Vec2d(-400,400);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posF and posD must be " + message.str())
        {
            CHECK(posF.toricVector(posD)== expected);
        }

        expected = Vec2d(0,0);
        message.str("");
        message.clear();
        message << expected;
        THEN("the toric vector between posF and posF must be " + message.str())
        {
            CHECK(posF.toricVector(posF)== expected);
        }
    }
}

SCENARIO("operator+ ", "ToricPosition")
{

	const Vec2d world_size(200., 200.);
    auto const width  = world_size.x();
    auto const height = world_size.y();
    std::ostringstream scenario;
    scenario << " A ToricPosition tp1 constructed at random position (0, h1), h1 <= WORLD_HEIGHT/2, \n";
    scenario << " A ToricPosition tp2 constructed at random position (w2,h2) <= (simulation_size/4,simulation_size/4)\n";
    scenario << "   (with simulation_size = " << width << ")";
    GIVEN("two random ToricPosition")
    {
        THEN("tp1 + tp2 must be equal (tp1.x() + tp2.x(), tp1.y()+tp2.y())")
        {
            for  (size_t i(0); i <20; ++i){
                ToricPosition const tp1(Vec2d(0, uniform(0.,height/2)), world_size);
                ToricPosition const tp2(Vec2d(uniform(0., width/4),
											  uniform(0., height/4)),
										world_size);
                ToricPosition expected(tp1.x() + tp2.x(), tp1.y()+tp2.y());
                CHECK((tp1+tp2) == expected);
            }
        }
    }
}

SCENARIO("Addition of ToricPositions (right clamping)", "ToricPosition")
{
	const Vec2d world_size(200., 200.);
    auto const width  = world_size.x();
    auto const height = world_size.y();
    

    std::ostringstream scenario;
    scenario << " A ToricPosition tp constructed at (10, 0), \n";
    scenario << " A ToricPosition w constructed at (WORLD_WITH, 0),\n";
    scenario << "   (with WORLD_WIDTH = " << width << " and WORLD_HEIGHT = " <<  height << ") \n";
    GIVEN("Two ToricPosition tp = (10,0) and w = (WORLD_WIDTH, 0)")
    {
        THEN("Then tp + w must be equal to tp")
        {
            ToricPosition  tp(Vec2d(10,0), world_size);
            ToricPosition  w(Vec2d(width, 0), world_size);
            CHECK( (tp + w) == tp);
        }
    }
}

SCENARIO("Addition of ToricPositions (left clamping)", "ToricPosition")
{
    
	const Vec2d world_size(200., 200.);
    auto const width  = world_size.x();
    auto const height = world_size.y();
    
    std::ostringstream scenario;
    scenario << " A ToricPosition tp constructed at (10, 0), \n";
    scenario << " A ToricPosition w constructed at (-WORLD_WITH, 0),\n";
    scenario << "   (with WORLD_WIDTH = " << width << " and WORLD_HEIGHT = " <<  height << ") \n";
	 GIVEN("Two ToricPosition tp = (10,0) and w = (-WORLD_WIDTH, 0)")
    {
        THEN("Then tp + w must be equal to tp")
        {
            ToricPosition  tp(Vec2d(10,0), world_size);
            ToricPosition  w(Vec2d(-width, 0), world_size);
            CHECK( (tp + w) == tp);
        }
    }
}

SCENARIO("Addition of ToricPositions (bottom clamping)", "ToricPosition")
{
	const Vec2d world_size(200., 200.);
    auto const width  = world_size.x();
    auto const height = world_size.y();

    std::ostringstream scenario;
    scenario << " A ToricPosition tp constructed at (0, 10), \n";
    scenario << " A ToricPosition w constructed at (0, -WORLD_HEIGHT),\n";
    scenario << "   (with WORLD_WIDTH = " << width << " and WORLD_HEIGHT = " <<  height << ") \n";
	GIVEN("Two ToricPosition tp = (10,0) and w = (0, -WORLD_HEIGHT)")
    {
        THEN("Then tp + w must be equal to tp")
        {
            ToricPosition  tp(Vec2d(0,10), world_size);
            ToricPosition  w(Vec2d(0, -height), world_size);
            CHECK( (tp + w) == tp);
        }
    }
}

SCENARIO("Addition of ToricPositions (top clamping)", "ToricPosition")
{
	const Vec2d world_size(200., 200.);
    auto const width  = world_size.x();
    auto const height = world_size.y();

    std::ostringstream scenario;
    scenario << " A ToricPosition tp constructed at (0, 10), \n";
    scenario << " A ToricPosition w constructed at (0, WORLD_HEIGHT),\n";
    scenario << "   (with WORLD_WIDTH = " << width << " and WORLD_HEIGHT = " <<  height << ") \n";
   	GIVEN("Two ToricPosition tp = (10,0) and w = (0, WORLD_HEIGHT)")
    {
        THEN("Then tp + w must be equal to tp")
        {
            ToricPosition  tp(Vec2d(0,10), world_size);
            ToricPosition  w(Vec2d(0, height),world_size);
            CHECK( (tp + w) == tp);
        }
    }
}

