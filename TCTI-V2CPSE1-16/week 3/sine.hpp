#ifndef SINE_HPP
#define SINE_HPP

#include "gonio.hpp"


class sine : sine_cosine_calc {
    private:
        int minute_hand[360] = {};
        int hour_hand[360] = {};
    public:
        constexpr sine() {
            for(int i = 0; i < 360; ++i){
                minute_hand[i] = siny(i, 25);
                hour_hand[i] = siny(i, 15);
            }
        }

        constexpr int get_minute( int n ) const {
            return minute_hand[ n ]; 
        }

        constexpr int get_hour( int n ) const {
            return hour_hand[ n ];    
        }


};

class cosine : sine_cosine_calc {
    private:
        int minute_hand[360] = {};
        int hour_hand[360] = {};
    public:
        constexpr cosine(){
            for(int i = 0; i < 360; ++i){
                minute_hand[i] = cosinx(i, 25);
                hour_hand[i] = cosinx(i, 15);
            }
        }

        constexpr int get_minute( int n ) const {
            return minute_hand[ n ]; 
        }

        constexpr int get_hour( int n ) const {
            return hour_hand[ n ];    
        }


};



#endif