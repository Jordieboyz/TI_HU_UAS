#include "TicTacToe.hpp"


void TicTacToe::add_move( move _move ){
        list_of_commands[(list_of_commands[0][0])+1] = _move;
        list_of_commands[0][0]++;
    }

void TicTacToe::remove_move( int index ){
    if( list_of_commands[0][0] != 0 ){
        list_of_commands[index] = { 0, 0 };
        list_of_commands[0][0]--;
    }
}

void TicTacToe::apply_moves( board& state, move& move, int player){
    state[move[0]][move[1]] = player;
}

board TicTacToe::after(){
    std::array<std::array<int, 3>, 3> start = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};
    wrongMove = false;
    for( int move = 1; move <= list_of_commands[0][0]; move++){
        if (isPossibleMove( start, list_of_commands[move] )){
            apply_moves(start, list_of_commands[move], !(move%2)+1);
        } else {
            std::cout << "Dit is een ongelid command!\n";
            remove_move( move );
            wrongMove = true;
            return start;
        }
    }
    return start;
}

bool TicTacToe::isFullBoard( const board& board ){
    for(unsigned int i = 0; i < board.size(); i++){
        for(unsigned int j = 0; j < board[i].size(); j++){
            if( board[i][j] == 0 ){
                return 0;
            }
        }
    }
    return 1;
}

bool TicTacToe::isPossibleMove( board& board, move& move){
    // out of bounds
    if( move[0] > (int)board.size()-1 || 
        move[1] > (int)board.size()-1 ||
        move[0] < 0 ||
        move[1] < 0 ){ 
        return 0; 
    }

    // empty spot on board
    for(unsigned int i = 0; i < board.size()-1; i++){
        for(unsigned int j = 0; j < board[i].size()-1; j++){
            if (board[move[0]][move[1]] == 0){
                return 1;
            }
        }
    }
    return 0;   
}

int TicTacToe::checkWinner( const board& board ){
    for(int i = 0; i < 3; i++){
        //horizontal
        if( board[i][0] != 0 &&
            board[i][0] == board[i][1] && 
            board[i][1]==board[i][2] ){
                return board[i][0]; 
        }
        //vertical
        else if( board[0][i] != 0 &&
                board[0][i] == board[1][i] &&
                board[1][i] == board[2][i] ){
            return board[0][i];
        }
        //diagonal starting upper left
        else if( board[0][0] != 0 &&
                board[0][0] == board[1][1] &&
                board[1][1] == board[2][2]){
            return board[0][0];
        }
        //diagonal starting upper right
        else if( board[0][2] != 0 &&
                board[0][2] == board[1][1] &&
                board[1][1] == board[2][0]){
            return board[0][2];
        }                    
    }
    //tie
    if( isFullBoard( board ) ){
        return -1;
    }
    // no full board neither a winner
    return 0;
}
