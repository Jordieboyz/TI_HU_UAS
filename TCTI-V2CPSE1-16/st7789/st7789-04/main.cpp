#include "hwlib.hpp"
#include "spi_object.hpp"

namespace target = hwlib::target;

int main( void ){
   
   // wait for the terminal emulator to start up
   hwlib::wait_ms( 2'000 );
   hwlib::cout << "ST7789 demo\n" << hwlib::flush;   
   
   uint_fast8_t port_pin_clk = 28;
   uint_fast8_t port_pin_mosi = 21;

   auto spi  = spi_object( port_pin_clk, port_pin_mosi );
      
   auto dc    = hwlib::target::pin_out{ hwlib::target::pins::d6 };
   auto & cs  = hwlib::pin_out_dummy;
   auto blk   = hwlib::target::pin_out{ hwlib::target::pins::d7 };
   auto rst   = hwlib::target::pin_out{ hwlib::target::pins::d5 };
   
   blk.write( 1 ); 
   blk.flush();

   auto display     = hwlib::st7789_spi_dc_cs_rst( spi, dc, cs, rst );   
   
   for(;;){

      uint_fast64_t start = hwlib::now_us();
      display.clear( hwlib::red );

      uint_fast64_t mid = hwlib::now_us();
      display.flush();
      
      uint_fast64_t end = hwlib::now_us();
      hwlib::cout << ((mid-start)/1'000) << " ms\n";
      hwlib::cout << ((end-mid)/1'000) << " ms\n";
      hwlib::cout << "total: " << ((end-start)/1'000) << "\n\n";

      uint_fast64_t start2 = hwlib::now_us();
      display.clear( hwlib::green);

      uint_fast64_t mid2 = hwlib::now_us();
      display.flush();

      uint_fast64_t end2 = hwlib::now_us();
      hwlib::cout << ((mid2-start2)/1'000) << "\n";
      hwlib::cout << ((end2-mid2)/1'000) << "\n";
      hwlib::cout << "total: " << ((end2-start2)/1'000) << "\n\n";
   }
}