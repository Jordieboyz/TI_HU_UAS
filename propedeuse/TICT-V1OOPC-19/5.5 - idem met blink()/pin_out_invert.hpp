#ifndef PIN_INVERT_HPP
#define PIN_INVERT_HPP

#include "hwlib.hpp"

class pin_out_invert : public hwlib::pin_out {
private:
    hwlib::pin_out & slave;
public:
    pin_out_invert(hwlib::pin_out & slave) :
        slave( slave )
    {}

    void write(bool x) override;
    void flush() override{};

};

#endif