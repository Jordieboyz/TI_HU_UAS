#ifndef SET_HPP
#define SET_HPP

#include <array>
#include <iostream>

template< typename T, int N>
class set {
private:
    int size = 0; 
    std::array< T, N > set_ = {};
    
public:
    void add( T a ){
        if(size == N || contains( a )){}
        else{
            for(int i = 0; i <= size; i++){
                if( set_[i] == '\0' ) { set_[i] = a; }   
            }
            size++;
        }
    }

    void remove( T a ){
        if(!contains( a )){}
        else{
            for(int i = 0; i < N; i++){
                if(set_[i] == a){
                    set_[i] = '\0';
                    size--; 
                }
            }
        }
    }   

    bool contains( T a ){
        for(T contain : set_){
            if( contain == a ){
                return true;
            }
        }
        return false;
    }

    T get( int a ){
        return set_[ a ];
    }

    int max_size(){ return N; }

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