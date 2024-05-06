#include "hwlib.hpp"
#include "clock.hpp"
#include "sine.hpp"


int main( void ){
    namespace target = hwlib::target;
    hwlib::wait_ms(1000);

    auto change_hours = target::pin_in( target::pins::d7 );
    auto change_minutes = target::pin_in( target::pins::d8 );

    auto scl     = target::pin_oc( target::pins::scl );
    auto sda     = target::pin_oc( target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
    auto display = hwlib::glcd_oled( i2c_bus, 0x3c );

    auto font = hwlib::font_default_8x8();
    auto oled = hwlib::terminal_from( display, font );

    auto clk = clock();
    auto coor_sine = sine();
    auto coor_cosine = cosine();
    
    int minute_counter = 45; int hour_counter = 9; int second_counter = 0;

    for(;;){
        if( change_minutes.read() == 0){
            minute_counter++;
            if( minute_counter == 60 ){ minute_counter = 0; }
            clk.update( display, minute_counter, hour_counter);
            second_counter = 0;
        }
        else if( change_hours.read() == 0){
            hour_counter++;
            if( hour_counter == 12 ){ hour_counter = 0; }
            clk.update( display, minute_counter, hour_counter);
            second_counter = 0; 
        }
        else{
            uint_fast64_t start = hwlib::now_us();

            clk.show_clock( display );
            clk.show_clock_hands( display, minute_counter*6, hour_counter*30);

            second_counter++;
            if( second_counter == 60){
                minute_counter++;
                if( minute_counter == 45 ){
                    hour_counter++;
                    if(hour_counter == 12){
                        hour_counter = 0;
                    }
                }
                else if( minute_counter == 60){
                    minute_counter = 0;
                }
                second_counter = 0;
            }        

            display.flush();
            display.clear();

            uint_fast64_t eind = hwlib::now_us();
            hwlib::wait_us_busy(1E6 -(eind-start));
        }
    }
}