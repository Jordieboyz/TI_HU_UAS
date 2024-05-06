#pragma once

#include <array>
#include <iostream>
#include "TicTacToe.hpp"


class consoleInterface : public TicTacToe {
public:
    consoleInterface( player& player1, player& player2 ) :
       TicTacToe( player1, player2 )
    {}

    void main();

    void drawBoard( const board& state ) override { 
        for(unsigned int i = 0; i < state.size(); i++){
            for(unsigned int j = 0; j < state[i].size(); j++){
                int symbol = state[i][j];
                switch(symbol){
                    case 1 : std::cout << "x "; break;
                    case 2 : std::cout << "o "; break;
                    default: std::cout << "- "; break;
                }
            }
            std::cout << std::endl;
        }
    }

};
