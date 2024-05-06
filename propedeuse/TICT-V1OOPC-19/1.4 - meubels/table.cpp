#include "table.hpp"

void table::print(){
        std::cout << "Een tafel met " << n_legs << " poten en een lengte van " << length << " meter en een breedte van " << width << " meter!" << std::endl;
}

void table::changeLegs(int aantalStoelen){
        n_legs = n_legs+aantalStoelen;
}