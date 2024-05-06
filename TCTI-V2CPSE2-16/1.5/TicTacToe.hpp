#pragma once

#include <array>
#include <iostream>
#include "player.hpp"

using board = std::array<std::array<int, 3>, 3>;
using move = std::array<int, 2>;
using moves = std::array<move, 10>;


class TicTacToe {
protected:

    moves list_of_commands = {};
    player players[2] = {};
    bool gameOver = false;
    bool wrongMove = false;
public:
    TicTacToe( player player1, player player2 ) :
        players( { player1, player2 } )
    {}

    void add_move( move _move );
    void remove_move( int index );
    void apply_moves( board& state, move& cmd, int player);
    board after(); 

    int checkWinner( const board& board );
    bool isPossibleMove( board& board, move& move);
    bool isFullBoard( const board& board );

    virtual void drawBoard( const board& state ) = 0;
};