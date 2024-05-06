#include "vector.hpp"

vector & vector::operator+=( const vector & rhs ){
    x += rhs.x;
    y += rhs.y;
    return *this;
}

vector vector::operator+( const vector & rhs) const {
    vector temp = *this;
    temp += rhs;
    return temp;
}

vector vector::operator+() const{
    return *this;
}

vector vector::operator-( const vector & rhs ) const {
    vector temp = *this;
    temp -= rhs;
    return temp;
}

vector & vector::operator-= ( const vector & rhs){
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

vector vector::operator* ( const int & rhs ) const{
    vector temp = *this;
    temp *= rhs;
    return temp;
}

vector & vector::operator*= ( const int & rhs ){
    x *= rhs;
    y *= rhs;
    return *this;
}

bool vector::operator==  (const vector & rhs ) const{
    return (x == rhs.x) && (y == rhs.y);
}