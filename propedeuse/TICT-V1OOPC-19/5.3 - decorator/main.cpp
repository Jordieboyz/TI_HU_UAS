
#include "hwlib.hpp"
#include <iostream>
#include "pin_in_and.hpp"


int main(){   
   auto pins = pin_in_and(hwlib::pin_in_dummy, hwlib::pin_in_dummy);
   pins.read();
}
