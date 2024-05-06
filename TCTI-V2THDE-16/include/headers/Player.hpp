#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "rtos.hpp"

struct Player
{
    rtos::pool<int> firePower;
    rtos::pool<int> hits;
    
    Player(){
        firePower.write( 1 );
        hits.write( 0 );
    }
};

#endif