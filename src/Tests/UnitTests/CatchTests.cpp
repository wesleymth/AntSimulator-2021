/*
 * prjsv 2015
 * 2014
 * Marco Antognini
 */

// Define the entry point for tests with Catch frameworks.

#define CATCH_CONFIG_RUNNER
#include <Application.hpp>
#include <catch.hpp>

int main(int argc, char const** argv)
{
	INIT_DEFAULT_APP(argc, argv);
	return Catch::Session().run();
}
