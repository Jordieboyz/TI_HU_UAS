#ifndef AUTO_HPP
#define AUTO_HPP

#include "hwlib.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "Cirkel.hpp"

class car {
    private:
        hwlib::window & w;
        line line1, line2, line3, line4, line5, line6, line7, line8, line9, line10, line11, line12, line13, line14, line15;
        circle wheel1, wheel2;
        rectangle window;
        filled_rectangle raam;
    public:
        car(hwlib::window & w, int start_x, int start_y, int end_x, int end_y, int windowOpen);
        void print();
};


#endif // AUTO_HPP