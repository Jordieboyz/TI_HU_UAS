#include "circle.hpp"

void circle::draw(){
    hwlib::circle c( location + hwlib::xy( radius, radius ), radius );
    c.draw( w );
}