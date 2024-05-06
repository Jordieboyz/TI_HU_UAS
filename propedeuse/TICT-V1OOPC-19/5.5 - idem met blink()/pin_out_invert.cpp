#include "pin_out_invert.hpp"

void pin_out_invert::write(bool x){
    slave.write(!x);
}
