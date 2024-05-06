#include "hwlib.hpp"
#include "pin_out_invert.hpp"

int main( void ){	
   
   namespace target = hwlib::target;

   auto ds       = target::pin_out( target::pins::d8 );
   auto shcp     = target::pin_out( target::pins::d9 );
   auto stcp     = target::pin_out( target::pins::d10 );
   
   auto spi_bus  = hwlib::spi_bus_bit_banged_sclk_mosi_miso(stcp, ds, hwlib::pin_in_dummy);
   auto hc = hwlib::hc595( spi_bus, shcp );

   auto LEDGroup1 = hwlib::port_out_from(hc.p0 ,hc.p1, hc.p2, hc.p3);
   auto LEDGroup2 = hwlib::port_out_from(hc.p4, hc.p5, hc.p6, hc.p7);

   auto ALLport1 = hwlib::all_from_port_out_t(LEDGroup1);
   auto ALLport2 = hwlib::all_from_port_out_t(LEDGroup2);

   auto LEDPortAll = hwlib::port_out_from(ALLport1, ALLport2);
   hwlib::kitt( LEDPortAll , 200);
}
