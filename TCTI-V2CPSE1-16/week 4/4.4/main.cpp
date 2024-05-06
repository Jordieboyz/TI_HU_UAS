#include "hwlib.hpp"

extern "C" void print_char( char c){ hwlib::cout << c;};
extern "C" void _start();

int main( void ){
   hwlib::wait_ms(1000);
   _start();
}