#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "ostream"
#include "vector.hpp"


TEST_CASE("OPTELLING"){
    vector v(3, 6);
    vector x = v += vector(5, 7);
    REQUIRE( x == vector(8, 13));
}