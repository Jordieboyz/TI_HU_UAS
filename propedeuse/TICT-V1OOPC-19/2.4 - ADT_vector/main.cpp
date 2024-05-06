#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "vector.hpp"

TEST_CASE(){
   vector x( 3, 4 );
   std::stringstream s;
   s << x;
   REQUIRE( s.str() == "[3, 4]" );
}

TEST_CASE(){
   vector x(2, 3);
   REQUIRE( x == vector(2, 3));
}

TEST_CASE(){
   vector x;
   REQUIRE( x == vector(0, 0));
}

TEST_CASE(){
   vector x(2, 3);
   vector a = + x;
   REQUIRE( a == vector(2, 3));
}

TEST_CASE(){
   vector x(2);
   vector a = x + vector(3, 4);
   REQUIRE( a == vector(5, 4));
}

TEST_CASE(){
   vector x(0);
   REQUIRE( x == vector(0, 0));
}

TEST_CASE(){
   vector x(2, 3);
   vector a = x + vector(3, 4);
   REQUIRE( a == vector(5, 7));
}

TEST_CASE(){
   vector x(2, 3);
   vector a = (x += vector(3, 4));
   REQUIRE(a == vector(5, 7));
   REQUIRE(x == vector(5, 7));
}

TEST_CASE(){
   vector x(2, 3);
   vector a = x * 3;
   REQUIRE( a == vector(6, 9));
}

TEST_CASE(){
   vector x(2, 3);
   vector a = (x *= 3);
   REQUIRE( a == vector(6, 9));
   REQUIRE( x == vector(6, 9));
}

TEST_CASE(){
   vector x(2, 3);
   vector a = (x *= 0);
   REQUIRE( a == vector(0, 0));
   REQUIRE( x == vector(0, 0));
}

TEST_CASE(){
   vector x(1);
   REQUIRE( x == vector(1, 0));
}


TEST_CASE(){
 vector x(2, 3);
 vector a = 2 * x;
 REQUIRE( a == vector(4, 6));   
}

TEST_CASE(){
   vector x(1, 1);
   vector y(2, 2);
   vector c = (((x += vector(4, 2)) *= 2)-((y += vector(6))+vector(0,4)));
   REQUIRE( x == vector(10, 6));
   REQUIRE( y == vector(8, 2));
   REQUIRE( c == vector(2));
}