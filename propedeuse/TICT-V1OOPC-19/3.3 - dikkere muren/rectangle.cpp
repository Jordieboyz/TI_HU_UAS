#include "rectangle.hpp"

void rectangle::draw(){
      left.draw();  
      right.draw();
      top.draw();
      bottom.draw();
      w.flush();
}