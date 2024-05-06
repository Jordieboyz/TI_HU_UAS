#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "set.hpp"

TEST_CASE(){
   set<int, 10> x;
   x.add(8);
   x.add(2);
   x.add(0);
   x.remove(8);
   x.add(9);
   x.add(1);
   REQUIRE( x.max() == 9);
}

TEST_CASE(){
   set<std::array<char, 3>, 10> x;
   x.add('a');
   x.add('A');
   x.add('b');
   x.remove('a');
   x.add('x');
   x.add('X');
   REQUIRE( x.max() == 'x');
}

TEST_CASE(){
   set<std::string, 10> x;
   x.add("ab");
   x.add("AB");
   x.add("bc");
   x.remove("BC");
   x.add("XY");
   x.add("aa");
   REQUIRE( x.max() == "bc");
}