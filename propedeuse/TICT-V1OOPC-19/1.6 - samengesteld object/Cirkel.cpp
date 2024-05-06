#include "Cirkel.hpp"

void circle::print(){
hwlib::circle c1(hwlib::xy(startX, startY), radius );
   c1.draw(w);
   w.flush();
}