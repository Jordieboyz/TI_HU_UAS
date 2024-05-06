// example:
// declaration of a rectangle object that is contains four line objects

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "line.hpp"

class rectangle {
private:
   hwlib::window & w;
   line left, right, top, bottom;
public:
   rectangle( hwlib::window & w, int start_x, int start_y, int end_x, int end_y );
   void print();
};

class filled_rectangle {
private:
      hwlib::window & w;
      int LB, LO, RB, RO, R, G,B;
public:
   filled_rectangle(hwlib::window & w, int start_x, int start_y, int end_x, int end_y): w( w )
   {
    LB = start_x;
    LO = start_y;
    RB = end_x;
    RO = end_y;
   }
   void draw(int R, int G, int B);

};



#endif // RECTANGLE_HPP
