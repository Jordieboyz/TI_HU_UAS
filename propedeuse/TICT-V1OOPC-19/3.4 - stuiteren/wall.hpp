#ifndef WALL_HPP
#define WALL_HPP

#include <hwlib.hpp>
#include "rectangle.hpp"

class wall : public rectangle {
private:
   bool filled = false;
   int update_interval;
   int update_count = 0;
   hwlib::xy location, end;
   
public:
   wall(hwlib::window & w, hwlib::xy location, hwlib::xy end, int update_interval, hwlib::xy bounceWall) :
      rectangle(w, location.x, location.y, end.x, end.y, bounceWall),
      update_interval( update_interval), location( location ), end( end )
   {}

   void update() override;
   void draw() override;
};


#endif // WALL_HPP