#include "auto.hpp"
#include "hwlib.hpp"

car::car(hwlib::window & w, int start_x, int start_y, int end_x, int end_y, int windowOpen) :
    w(w),
    line1( w, start_x, start_y, end_x, end_y ),
    line2( w, start_x-10, start_y, end_x-50, end_y ),
    line3( w, start_x-20, start_y, end_x-54, end_y-4 ),
    line4(w, start_x-24, start_y-4, end_x-54, end_y-9),
    line5(w, start_x-24, start_y-9, end_x-50, end_y-13),
    line6(w, start_x-20, start_y-13, end_x-37, end_y-13),
    line7(w, start_x-7, start_y-13, end_x-28, end_y-22),
    line8(w, start_x+2, start_y-22, end_x-3, end_y-22),
    line9(w, start_x+27, start_y-22, end_x+6, end_y-13),
    line10(w, start_x+36, start_y-13, end_x+15, end_y-13),
    line11(w, start_x+45, start_y-13, end_x+15, end_y),
    line12(w, start_x+45, start_y, end_x+10, end_y),
    line13(w, start_x-24, start_y-7, end_x-44, end_y-7),
    line14(w, start_x-14, start_y-7, end_x-40, end_y-11),
    line15(w, start_x-11, start_y-11, end_x-41, end_y-13),
    wheel1(w, start_x-5, start_y, 5),
    wheel2(w, start_x+35, start_y, 5),
    window(w, start_x+4, start_y-19, end_x-4, end_y-9),
    raam(w, start_x+5, start_y-windowOpen-10, end_x-5, end_y-10)
{}

void car::print(){
    line1.print();
    line2.print();
    line3.print();
    line4.print();
    line5.print();
    line6.print();
    line7.print();
    line8.print();
    line9.print();
    line10.print();
    line11.print();
    line12.print();
    line13.print();
    line14.print();
    line15.print();
    wheel1.print();
    wheel2.print();
    window.print();
    raam.draw(128,128,128);
};