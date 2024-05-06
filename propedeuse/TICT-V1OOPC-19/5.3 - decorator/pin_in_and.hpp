#ifndef PIN_HPP
#define PIN_HPP

#include "hwlib.hpp"


class pin_in_and : public hwlib::pin_in{
private:
    hwlib::pin_in & pin1;
    hwlib::pin_in & pin2;
public:
    pin_in_and(hwlib::pin_in & pin1, hwlib::pin_in & pin2) : 
        pin1( pin1 ), pin2( pin2 )
    {}

    bool read() override;
    void refresh() override;
    


};

#endif