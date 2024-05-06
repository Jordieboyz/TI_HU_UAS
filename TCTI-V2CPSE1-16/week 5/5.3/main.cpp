#define CATCH_CONFIG_MAIN 

#include "catch.hpp"
#include "set.hpp"


TEST_CASE(){
    set<int, 10> x;
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "{ }" );
}

TEST_CASE(){
    set<int, 10> x;
    x.add(4);
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "{ 4, }" );
}

TEST_CASE(){
    set<int, 10> x;
    x.add(4);
    x.add(7);
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "{ 4, 7, }" );
}

TEST_CASE(){
    set<int, 10> x;
    x.add(4);
    x.add(7);
    x.add(2);
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "{ 4, 7, 2, }" );
}

TEST_CASE(){
    set<int, 10> x;
    x.add(4);
    x.add(7);
    x.add(2);
    x.remove(4);
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "{ 7, 2, }" );
}

TEST_CASE(){
    set<int, 10> x;
    x.add(4);
    x.add(7);
    x.add(2);
    x.remove(4);
    REQUIRE( x.max() == 7 );
}

TEST_CASE(){
    set<int, 10> x;
    x.add(4);
    x.add(7);
    x.add(2);
    x.remove(7);
    REQUIRE( x.max() == 4 );
}

TEST_CASE(){
    set<char, 10> x;
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "{ }" );
}

TEST_CASE(){
    set<char, 10> x;
    x.add('A');
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "{ A, }" );
}

TEST_CASE(){
    set<char, 10> x;
    x.add('A');
    x.add('a');
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "{ A, a, }" );
}

TEST_CASE(){
    set<char, 10> x;
    x.add('A');
    x.add('a');
    x.add('B');
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "{ A, a, B, }" );
}

TEST_CASE(){
    set<char, 10> x;
    x.add('A');
    x.add('a');
    x.add('B');
    REQUIRE( x.max() == 'a');
}

TEST_CASE(){
    set<char, 10> x;
    x.add('A');
    x.add('a');
    x.add('B');
    x.remove('a');
    REQUIRE( x.max() == 'B');
}
