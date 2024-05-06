#ifndef TABLE_HPP
#define TABLE_HPP

#include "meubels.hpp"

class table{
    private:
        int n_legs;
        double width;
        double length;
    public:
    table(int poten, double breedte, double lengte){
        n_legs = poten;
        width = breedte;
        length = lengte;
    };
    void print();
    void changeLegs(int);
    
};

#endif //TABLE_HPP
