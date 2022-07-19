#include "catch2/catch_test_macros.hpp"
#include "../src/utils.h"

extern int test();

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE("test link dll function", "[test-dll]") {
    REQUIRE( test() == 1234 );
}

TEST_CASE("test third test", "[third]") {
    REQUIRE( test() == 1234 );
}

TEST_CASE("test region", "[region]") {
    Region r("test region");
    REQUIRE( Region::level == 1);
    Region s("test region");
    REQUIRE( Region::level == 2);
}
