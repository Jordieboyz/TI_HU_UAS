#include "rectangle.hpp"

void rectangle::draw(){
      line left(   w, hwlib::xy(drawable::location.x, drawable::location.y), hwlib::xy(drawable::location.x, (drawable::size.y+drawable::location.y) + 1) );
      line right(  w, hwlib::xy(drawable::size.x+drawable::location.x,   drawable::location.y), hwlib::xy(drawable::size.x+drawable::location.x, (drawable::size.y+drawable::location.y) + 1) );
      line top(    w, hwlib::xy(drawable::location.x, drawable::location.y), hwlib::xy((drawable::size.x+drawable::location.x) + 1,drawable::location.y) );
      line bottom( w, hwlib::xy(drawable::location.x, drawable::size.y+drawable::location.y),   hwlib::xy((drawable::size.x+drawable::location.x) + 1, drawable::size.y+drawable::location.y) );
      left.draw();
      right.draw();
      bottom.draw();
      top.draw();
      w.flush();
}
