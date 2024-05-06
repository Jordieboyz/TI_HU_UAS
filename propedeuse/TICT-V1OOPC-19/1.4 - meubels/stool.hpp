#ifndef STOOL_HPP
#define STOOL_HPP

#include "meubels.hpp"

class stool{
    private:
        int n_legs;
        int n_seats;
    public:
    stool(int poten, int zitvlak){
        n_legs = poten;
        n_seats = zitvlak;
    }
    void print();
    void changeLegs();
};



#endif //STOOL_HPP