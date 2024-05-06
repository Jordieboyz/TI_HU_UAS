// example:
// definition of the functions of a line class 


#include "line.hpp"

void line::print(){
   hwlib::line lines(hwlib::xy(start_x, start_y), hwlib::xy(end_x, end_y));
   lines.draw(w);
   w.flush();
}