#pragma once

#include <iostream>

using move = std::array<int, 2>;

class player {
private:
    std::string name;
    int playerNumber;

public:
    player(){};
    
    player( std::string name, int playerNumber) :
        name( name ), playerNumber( playerNumber )
    {}

    move chooseMove(){
        int row, column;
        std::cout << "\nWelke positie wil je je symbool neerzetten?\nRij: ";
        std::cin >> row;

        std::cout << "Kolom: ";
        std::cin >> column;

        return { row, column };
    }

    int getPlayerNumber(){
        return playerNumber;
    }

    std::string getName(){
        return name;
    }


};