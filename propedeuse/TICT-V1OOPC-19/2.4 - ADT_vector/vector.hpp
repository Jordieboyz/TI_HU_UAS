#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "ostream"
#include <iomanip>

/// @file

///\brief
///Vector class
///\details
///This vector class implements a vector with 2 values in it.
///The vector consits of 2 integers as elements in the vector.
class vector {
private:
///\brief
///private member's vector class
///\details
//the x and the y are the 2 private members of the vector class.
    int x;
    int y;
public:
///\brief
///Constructor of vector class
///\details
///The constructor asks for 2 integers (x and y).
///The vector had a deafulat "y-value" of 0.
vector(int x = 0, int y = 0) :
    x ( x ), 
    y ( y )
{};

///\brief
//\Add two vectors up
///\details
///This operator+ adds up 2 vectors and returns a new vector with the addes values.
vector operator+( const vector & rhs ) const;

///\brief
///unary+ for vector
///\details
///This operator+ returns himself if there is not another vector on the other side of the operator.
vector operator+() const;

///\brief
///add one vector to another one
///\details
///The operator+= adds two vectors up 
///and returns the existing vector which the given vector has been added.
vector & operator+=( const vector & rhs );

///\brief
///substract one vector to another one
///\details
///The operator- substracts two vectors and returns a new vector with the substracted values.
vector operator-( const vector & rhs ) const;

///\brief
///substract one vector to another one
///\details
///The operator-= subtracts two vectors
///and returns the existing vector which the given vector has been subtracted.
vector & operator-=( const vector & rhs );

///\brief
///multiplies a vector with an integer
///\details
///the given vector can get multiplied with an integer if the integer
///is on the left side of the operator.
friend vector operator* (const int lhs, vector & rhs){
    return vector(rhs *= lhs);
}

///\brief
///multiplies a vector wwith an integer
///\details
///The operator* multiplies a vector with an integer 
///and returns a new vector wich has been multiplied with the given interger.
vector operator*( const int & rhs ) const;

///\brief
///multiply a vector with an integer
///\details
///The operator*= multiplies a vector with an integer 
///and returns the existing vector which is multiplied with the given integer.
vector & operator*=( const int & rhs );

///\brief
///compare two "vector-values"
///\details
///The operator== compares the two values in the "vector" 
///and returns true if those are equal to each other.
bool operator==( const vector & rhs ) const;

///\brief
///output vector as a list
///\details
///The operator<< prints a vector in a hexadecicmal format [0x0000, 0xAaBb].
friend std::ostream & operator<< (std::ostream & lhs, const vector & rhs){
    return lhs << "[" << rhs.x << ", " << rhs.y << "]";
    }
};

#endif // VECTOR_HPP