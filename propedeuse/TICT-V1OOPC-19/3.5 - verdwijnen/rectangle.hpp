#ifndef RECT_HPP
#define RECT_HPP

#include <hwlib.hpp>
#include "drawable.hpp"
#include "line.hpp"

class rectangle : public drawable {
protected:
   hwlib::window & w;
   int start_x = 0;//drawable::location.x;
   int start_y = 0;//drawable::location.y;
   int end_x = 0;//drawable::size.x+drawable::location.x; 
   int end_y = 0;//drawable::size.y+drawable::location.y;
   
public:
   rectangle( hwlib::window & w, int start_x, int start_y, int end_x, int end_y, hwlib::xy bounceRec = {1, 1}) :
      drawable( w, hwlib::xy(start_x, start_y), hwlib::xy(end_x-start_x, end_y-start_y), bounceRec),
      w( w ),
      start_x( start_x), start_y(start_y), end_x(end_x), end_y(end_y)
         {}
   
   void draw() override; 
};

#endif // RECT_HPP