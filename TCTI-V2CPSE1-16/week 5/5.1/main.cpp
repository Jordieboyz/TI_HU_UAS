
#define CATCH_CONFIG_MAIN 

#include "catch.hpp"
#include "set.hpp"


TEST_CASE(){
    set x;
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "[ 0, 0 ]" );
}

TEST_CASE(){
    set x;
    x.add(5);
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "[ 0, 5 ]" );
}

TEST_CASE(){
    set x;
    x.add(5);
    x.add(4);
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "[ 0, 5 ]" );
}

TEST_CASE(){
    set x;
    x.add(5);
    x.add(4);
    x.set_index(1);
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "[ 1, 4 ]" );
}

TEST_CASE(){
    set x;
    x.add(5); 
    x.add(4);
    x.set_index(4);
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "[ 4, 0 ]" );
}

TEST_CASE(){
    set x;
    for(int i = 1; i < 10; i++){
        x.add(i);
    }
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "[ 0, 1 ]" );
}

TEST_CASE(){
    set x;
    for(int i = 1; i < 10; i++){
        x.add(i);
    }
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "[ 0, 1 ]" );
}

TEST_CASE(){
    set x;
    for(int i = 1; i < 10; i++){
        x.add(i);
    }
    x.set_index(3);
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "[ 3, 4 ]" );
}

TEST_CASE(){
    set x;
    for(int i = 0; i < 10; i++){
        x.add(i);
    }
    x.remove(3);
    x.set_index(2);
    std::stringstream s;
    s << x;
    REQUIRE( s.str() == "[ 2, 0 ]" );
}

TEST_CASE(){
    set x;
    x.add(1);
    REQUIRE( x.contains(1) == true );
}

TEST_CASE(){
    set x;
    x.add(1);
    REQUIRE( x.contains(2) == false );
}

TEST_CASE(){
    set x;
    x.add(1);
    REQUIRE( x.get_size() == 1 );
}

TEST_CASE(){
    set x;
    x.add(1);
    x.add(1);
    REQUIRE( x.get_size() == 1 );
}

TEST_CASE(){
    set x;
    x.add(1);
    x.add(4);
    REQUIRE( x.get_size() == 2 );
}

TEST_CASE(){
    set x;
    x.add(1);
    x.add(4);
    REQUIRE( x.get_size() == 2 );
}

TEST_CASE(){
    set x;
    x.add(1);
    x.add(4);
    x.add(7);
    x.remove(2);
    REQUIRE( x.get_size() == 3 );
}

TEST_CASE(){
    set x;
    x.add(1);
    x.add(4);
    x.add(7);
    x.remove(4);
    REQUIRE( x.get_size() == 2 );
}

TEST_CASE(){
    set x;
    for(unsigned int i; i < 10; i++){
        x.add(i);
    }
    REQUIRE( x.get_size() == 10 );
}

TEST_CASE(){
    set x;  
    for(unsigned int i = 0; i < 10; i++){ 
        x.add(i);
    }  
    x.add(3);
    x.add(9);
    x.remove(3);
    x.remove(4);
    x.remove(3);
    x.remove(4);
    x.remove(9);
    REQUIRE( x.get_size() == 6 );
}
