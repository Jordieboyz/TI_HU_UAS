#include "clock.hpp"

void clock::make_circle(hwlib::window & w, hwlib::xy start, uint_fast16_t radius){
    auto circle = hwlib::circle( start, radius);
    circle.draw(w);
}

void clock::show_clock(hwlib::window & w){
    make_circle(w,  hwlib::xy(64, 32), 1);

    make_circle( w,  hwlib::xy(64 + cosine().get_minute(0), 32 + sine().get_minute(0)), size_);
    make_circle( w,  hwlib::xy(64 + cosine().get_minute(30), 32 + sine().get_minute(30)), size_);
    make_circle( w,  hwlib::xy(64 + cosine().get_minute(60), 32 + sine().get_minute(60)), size_);
    make_circle( w,  hwlib::xy(64 + cosine().get_minute(90), 32 + sine().get_minute(90)), size_);
    ///
    make_circle( w,  hwlib::xy(64 + cosine().get_minute(120), 32 + sine().get_minute(120)), size_);
    make_circle( w,  hwlib::xy(64 + cosine().get_minute(150), 32 + sine().get_minute(150)), size_);
    make_circle( w,  hwlib::xy(64 + cosine().get_minute(180), 32 + sine().get_minute(180)), size_);
    ///
    make_circle( w,  hwlib::xy(64 - cosine().get_minute(30), 32 - sine().get_minute(30)), size_);
    make_circle( w,  hwlib::xy(64 - cosine().get_minute(60), 32 - sine().get_minute(60)), size_);
    make_circle( w,  hwlib::xy(64 - cosine().get_minute(90), 32 - sine().get_minute(90)), size_);
    ///
    make_circle( w,  hwlib::xy(64 - cosine().get_minute(120), 32 - sine().get_minute(120)), size_);
    make_circle( w,  hwlib::xy(64 - cosine().get_minute(150), 32 - sine().get_minute(150)), size_);
}


void clock::show_clock_hands(hwlib::window & w, int minutes, int hours){
        if( minutes <= 180 ){
            auto minute_hand = hwlib::line( hwlib::xy(64, 32), hwlib::xy(64 + cosine().get_minute(minutes), 32 + sine().get_minute(minutes)));
            minute_hand.draw( w );
        }
        else if( minutes < 360 ){
            auto minute_hand = hwlib::line( hwlib::xy(64, 32), hwlib::xy(64 - cosine().get_minute(minutes-180), 32 - sine().get_minute(minutes-180)));
            minute_hand.draw( w ); 
        }        
        if( hours <= 180 ){
            auto hour_hand = hwlib::line( hwlib::xy(64, 32), hwlib::xy(64 + cosine().get_hour(hours), 32 + sine().get_hour(hours)));
            hour_hand.draw( w );
        }
        else if( hours < 360){
            auto hour_hand = hwlib::line( hwlib::xy(64, 32), hwlib::xy(64 - cosine().get_hour(hours-180), 32 - sine().get_hour(hours-180)));
            hour_hand.draw( w );
        }
}

void clock::update( hwlib::window & w, int minute_counter, int hour_counter){
    show_clock( w );
    show_clock_hands( w, minute_counter*6, hour_counter*30);
    w.flush();
    w.clear();
}