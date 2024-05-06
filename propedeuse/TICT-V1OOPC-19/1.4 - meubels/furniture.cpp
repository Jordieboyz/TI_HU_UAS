#include "furniture.hpp"

int aantalStoelen = 0;


void furniture::print(){
        stoel1.print();
        stoel2.print();
        stoel3.print();
        stoel4.print();
        tafel.print();
}


void furniture::makeMoreHipster(){
        stoel1.changeLegs();
        aantalStoelen++;
        stoel2.changeLegs();
        aantalStoelen++;
        stoel3.changeLegs();
        aantalStoelen++;
        stoel4.changeLegs();
        aantalStoelen++;
        tafel.changeLegs(aantalStoelen);
}