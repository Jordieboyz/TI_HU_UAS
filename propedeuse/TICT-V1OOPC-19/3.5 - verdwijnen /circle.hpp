#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <hwlib.hpp>
#include "drawable.hpp"

class circle : public drawable {
protected:
   int radius;
public:
   circle( hwlib::window & w, const hwlib::xy & midpoint, int radius ):
      drawable( w, midpoint - hwlib::xy( radius, radius ), hwlib::xy( radius, radius ) * 2 ), 
      radius( radius )
   {}
   
   void draw() override;
};

#endif // CIRCLE_HPP