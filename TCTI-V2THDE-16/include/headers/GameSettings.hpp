#ifndef GAMESETTINGS_HPP
#define GAMESETTINGS_HPP

#include "rtos.hpp"


struct GameSettings
{
    rtos::pool<int> gameTime;
    rtos::pool<int> startTime;

    GameSettings(){
        startTime.write( 0 );
        gameTime.write( 0 );
    }
};

#endif