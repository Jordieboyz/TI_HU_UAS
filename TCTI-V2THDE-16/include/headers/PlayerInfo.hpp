#ifndef PLAYERINFO_HPP
#define PLAYERINFO_HPP

#include "rtos.hpp"
#include "../headers/Player.hpp"

struct PlayerInfo
{
    rtos::pool<int> playerID;
    std::array< Player, 31> players;

    PlayerInfo()
    {
        playerID.write( 0 );
    }
};

#endif