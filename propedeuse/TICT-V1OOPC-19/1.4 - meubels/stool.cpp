#include "stool.hpp"

void stool::print(){
        std::cout << "Een stoel met " <<  n_legs << " poten en " << n_seats << " zitvlak(ken)" << std::endl;
}

void stool::changeLegs(){
        n_legs = n_legs-1;
}