#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "hwlib.hpp"

class circle {

    private:
        hwlib::window & w;
        uint_fast16_t radius;
        int startY, startX;
    public:
        circle(hwlib::window & w, int start_x, int start_y, uint_fast16_t radius1): 
        w( w )
        {
            startY = start_y;
            startX = start_x;
            radius = radius1;
        } 
    void print();
  
};

#endif // CIRCLE_HPP