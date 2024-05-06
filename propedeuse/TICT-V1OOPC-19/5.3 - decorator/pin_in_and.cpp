#include "pin_in_and.hpp"

bool pin_in_and::read(){
    if(pin1.read() && pin2.read()){
        return true;
    }
    else{
        return false;
    }
}

void pin_in_and::refresh(){
    pin1.refresh();
    pin2.refresh();
}
