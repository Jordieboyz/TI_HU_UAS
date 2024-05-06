#ifndef LINE_HPP
#define LINE_HPP

#include <hwlib.hpp>
#include "drawable.hpp"

class line : public drawable {
private:

   hwlib::xy end;
   
public:

   line( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & end ):
      drawable( w, location, end - location),
      end( end )
   {}
   
   void draw() override;
};


#endif // LINE_HPP