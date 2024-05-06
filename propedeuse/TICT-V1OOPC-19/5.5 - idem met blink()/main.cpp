#include "hwlib.hpp"
#include "pin_out_invert.hpp"

void kitt( hwlib::all_from_port_out_t & leds, int ms = 250 ){
   for(;;){
      leds.write(1);
      leds.flush();
      hwlib::wait_ms( ms );
      leds.write(0);
      leds.flush();
      hwlib::wait_ms( ms );
   }
}


int main( void ){	
   
   namespace target = hwlib::target;

   auto ds       = target::pin_out( target::pins::d8 );
   auto shcp     = target::pin_out( target::pins::d9 );
   auto stcp     = target::pin_out( target::pins::d10 );
   
   auto spi_bus  = hwlib::spi_bus_bit_banged_sclk_mosi_miso(stcp, ds, hwlib::pin_in_dummy);
   auto hc = hwlib::hc595( spi_bus, shcp );

   auto LEDInvert0 = pin_out_invert(hc.p0);
   auto LEDInvert1 = pin_out_invert(hc.p1);
   auto LEDInvert2 = pin_out_invert(hc.p2);
   auto LEDInvert3 = pin_out_invert(hc.p3);
   

   auto LEDGroup = hwlib::port_out_from(LEDInvert0, LEDInvert1, LEDInvert2, LEDInvert3, hc.p4, hc.p5, hc.p6, hc.p7);

   auto LEDALLGroup = hwlib::all_from_port_out_t(LEDGroup);

   hwlib::blink( LEDALLGroup );
}
