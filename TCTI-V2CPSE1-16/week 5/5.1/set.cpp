#include "set.hpp"


void set::add( int a ){
    if(size == 10 || contains( a )){}
    else{
        for(int i = 0; i <= size; i++){
            if( set_[i] == 0 ) { set_[i] = a; }   
        }
        size++;
    }
}

void set::remove( int a ){
    if(!contains( a )){}
    else{
        for(int i = 0; i <= 10; i++){
            if(set_[i] == a){
                set_[i] = 0;
                size--; 
            }
        }
    }
}

bool set::contains( int a ){
    for(int contain : set_){
        if( contain == a ){
            return true;
        }
    }
    return false;
}