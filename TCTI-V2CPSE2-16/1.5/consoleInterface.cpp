#include "consoleInterface.hpp"

void clearScreen(){
    std::cout << "\x1B[2J\x1B[H";
}

std::ostream& operator<<( std::ostream& lhs, std::array<int, 2> rhs){
    return lhs << "( " << rhs[0] << " , " << rhs[1] << " )";
}

void consoleInterface::main(){

    clearScreen();
    drawBoard( after() );

    for(;;){
        bool currentPlayer = list_of_commands[0][0]%2;
        std::cout << "\n\x1B[33m" << players[currentPlayer].getName() << "\033[0m is aan de beurt!\n";

        move playerMove = players[currentPlayer].chooseMove();
        add_move( playerMove );

        clearScreen();
        drawBoard( after());

        if (!wrongMove){
            char undo;
            std::cout   << "\nWeet je zeker dat je deze zet " << playerMove << " wil zetten? typ de overeenkomstige letter: " << std::endl;
            std::cout   << " ___________________   ____________________ \n"
                        << "|                   | |                    |\n"
                        << "|      undo( u )    | |    continue( c )   |\n"
                        << "|___________________| |____________________|\n";

            while(true){
                std::cin >> undo;
                if ( undo == 'u' || undo == 'U' )
                {
                    remove_move( list_of_commands[0][0] );
                    clearScreen();
                    drawBoard( after() );
                    break;
                } 
                if( undo == 'c' || undo == 'C'){
                    clearScreen();
                    drawBoard( after() );
                    break;
                }
            }
        }
        
        if( list_of_commands[0][0] > 4){
            int winner = checkWinner( after() );
            if( winner != 0){
                for (auto a : players){
                    if( winner == a.getPlayerNumber()){
                        std::cout << "\n\x1B[32m" << a.getName() << " heeft gewonnen!!\033[0m\n";   
                    }
                }
                if( winner == -1 ){
                    std::cout << "\n\x1B[31m" << "Helaas, niemand heeft gewonnen, het is gelijkspel..." << "\033[0m";
                }
            break;
            }
        }
    }
}
