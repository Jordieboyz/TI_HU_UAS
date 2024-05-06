#ifndef RECT_HPP
#define RECT_HPP

#include <hwlib.hpp>
#include "drawable.hpp"
#include "line.hpp"

class rectangle : public drawable {
protected:
   hwlib::window & w;
private:
   line left, right, top, bottom;
public:
   rectangle( hwlib::window & w, int start_x, int start_y, int end_x, int end_y, hwlib::xy bounceRec) :
      drawable( w, hwlib::xy(start_x, start_y), hwlib::xy(end_x-start_x, end_y-start_y), bounceRec),
      w( w ),
      left(   w, hwlib::xy(start_x, start_y), hwlib::xy(start_x, end_y + 1) ),
      right(  w, hwlib::xy(end_x,   start_y), hwlib::xy(end_x, end_y + 1) ),
      top(    w, hwlib::xy(start_x, start_y), hwlib::xy(end_x + 1, start_y) ),
      bottom( w, hwlib::xy(start_x, end_y),   hwlib::xy(end_x + 1, end_y) )
     
   {}
   void draw() override; 
};

#endif // RECT_HPP