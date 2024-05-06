#ifndef FURNI_HPP
#define FURNI_HPP

#include "meubels.hpp"

class furniture{
private:
    stool stoel1;
    stool stoel2;
    stool stoel3;
    stool stoel4;
    table tafel;
public:
    furniture(stool stoel1, stool stoel2, stool stoel3, stool stoel4, table tafel) :
        stoel1(stoel1), 
        stoel2(stoel2),
        stoel3(stoel3),
        stoel4(stoel4),
        tafel(tafel){
        }
    void print();
    void makeMoreHipster();
};


#endif // FURNI_HPP