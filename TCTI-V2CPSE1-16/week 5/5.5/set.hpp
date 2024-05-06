#ifndef SET_HPP
#define SET_HPP

#include <array>
#include <iostream>
#include <string>

template< typename T, int N>
class set {
private:
    int size = 0; 
    std::array< T, N > set_ = {};
    
public:
 
    void add( T a ){
        if(size == N || contains( a )){}
        else{
            set_[size] = a; 
            size++;
        }
    }

    void remove( T a ){
        if(!contains( a )){}
        else{
            for(int i = 0; i < N; i++){
                if(set_[i] == a){
                    for(int j = i; j < N-1; j++){
                        set_[j] = set_[j+1];
                    }
                    size--;
                }  
            }
        }
    }   

    bool contains( T a ){
        for(int i = 0; i < size; i++){
            if( set_[i] == a ){
                return true;
            }
        }
        return false;
    }

    T max(){
        T tmp = set_[0];
        for(int i = 0; i < size; i++){
            if(set_[i] > tmp){ 
                tmp = set_[i];
            }
        }
        return tmp;
    }
 

    friend std::ostream & operator<<( std::ostream & lhs, const set & rhs){
        lhs << "{ " 
            << rhs.set_[0];
        for(int i = 1; i < rhs.size; i++){ 
            lhs << ", " << rhs.set_[i]; 
        }
        return lhs << "}";
    }
};

template<size_t N>
std::ostream & operator<<( std::ostream& os, const std::array<char, N> rhs){
      os << "{ ";
      for( unsigned int i = 0; i < N; i++){
         os << rhs[i];
      }
      return os << " }";
}; 

template< size_t n >
bool operator>( const std::array<char, n> & lhs , const std::array<char, n> & rhs ){
    int lhs_ = 0; int rhss = 0;
    for( unsigned int i = 0; i < lhs.size(); i++){
        lhs_ += lhs[i];
    }
    for( unsigned int j = 0; j < rhs.size(); j++){
        rhss += rhs[j];
    }
    return lhs_ > rhss;
}

#endif
