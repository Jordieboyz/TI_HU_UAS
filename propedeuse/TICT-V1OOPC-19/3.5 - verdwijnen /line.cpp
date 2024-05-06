#include "line.hpp"

void line::draw(){
    hwlib::line x( location, end );
    x.draw( w );;
}