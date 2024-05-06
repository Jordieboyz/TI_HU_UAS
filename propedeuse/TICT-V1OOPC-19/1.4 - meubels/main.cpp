#include "meubels.hpp"

int main(){
    furniture huis = {stool(4, 1), stool(4, 1), stool(4,1), stool(4,1), table(4, 2.5, 4.5)};
    std::cout << "DE HUISKAMER HEEFT: "  << std::endl << std::endl;
    huis.print();
    std::cout << std::endl << "ER IS IETS GEKS GEBEURD MET DE POTEN!"  << std::endl << std::endl;
    huis.makeMoreHipster();
    huis.print();
}