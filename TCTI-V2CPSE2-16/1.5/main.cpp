#include <iostream>
#include <array>
#include "consoleInterface.hpp"
#include "graphicInterface.hpp"
#include "player.hpp"


int main(){
    char choice;
    std::string name1;
    std::string name2;

    std::cout << "Geef de naam van speler 1 op: ";
    std::cin >> name1;
    
    std::cout << "Geef de naam van speler 2 op: ";
    std::cin >> name2;

    player player1( name1, 1 );
    player player2( name2, 2 );

    for(;;){
        std::cout << "\nKies de letter \"G\" voor de grafische versie en \"C\" voor de console versie!" << std::endl;
        std::cin >> choice;
    
        if (choice == 'G' || choice == 'g'){
            graphicInterface graphic( player1, player2 );
            graphic.main();
            continue;
        }
        if (choice == 'C' || choice == 'c'){
            consoleInterface console( player1, player2 );
            console.main();
            continue;
        } else {
            std::cout << "Je hebt een verkeerde input opgegeven! Kies uit \"G\" of \"C\"." << std::endl; 
        }
    }
}

