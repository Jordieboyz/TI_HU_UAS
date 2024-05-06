#ifndef VICTIM_HPP
#define VICTIM_HPP

#include <hwlib.hpp>
#include "drawable.hpp"
#include "rectangle.hpp"

class victim : public rectangle {
private:

   bool updateTime = false;
   
public:
   victim(hwlib::window & w, hwlib::xy location, hwlib::xy end) :
      rectangle(w, location.x, location.y, end.x, end.y)
   {}

   void update() override;
   void interact(drawable & other) override;
};

#endif // VICTIM_HPP
