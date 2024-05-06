#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "hwlib.hpp"
#include "sine.hpp"

class clock {
    private:
        int size_ = 2;
        void make_circle(hwlib::window & w, hwlib::xy start, uint_fast16_t radius);

    public:
        void show_clock(hwlib::window & w);
        void show_clock_hands( hwlib::window & w, int minutes, int hours );
        void update( hwlib::window & w, int minutes, int hours);
};



#endif