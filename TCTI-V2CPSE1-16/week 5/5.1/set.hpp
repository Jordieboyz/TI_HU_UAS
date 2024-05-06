#ifndef SET_HPP
#define SET_HPP

#include <array>
#include <iostream>


class set {
private:
    int size = 0; 
    int index = 0;
    std::array<int, 10> set_ = {};
    
public:
    void add( int );
    void remove( int );
    bool contains( int );

    int get_size(){ 
        return size; 
    }

    void set_index( unsigned int a ){ 
        if( a < 10 ){ 
            index = a;  
        }
    }

    friend std::ostream & operator<<( std::ostream & lhs, const set & rhs){
        return lhs
            << "[ "
            << rhs.index
            << ", "
            << rhs.set_[rhs.index]
            << " ]";
    }
};

#endif