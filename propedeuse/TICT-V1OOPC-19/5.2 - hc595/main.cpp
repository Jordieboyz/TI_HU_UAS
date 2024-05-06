#include "hwlib.hpp"

void kitt( hwlib::port_out & leds){
   unsigned int count = 0;
   leds.write(0x01 << 8);
   leds.flush();
   for(;;){
      if (( PIOC->PIO_PDSR & ( 0x01 << 23)) == 0 ){ //pin 7
         if(count < 9){
            count++;
         }
         else{
            count = 1;
         }
         hwlib::wait_ms(200);
         }
      if ((PIOC->PIO_PDSR & (0x01 << 24)) == 0){   //pin 6
         if(count > 1){
            count--;
         }
         else{
            count = 9;
         }
         hwlib::wait_ms(200);
      }
      if(count == 1){
         leds.write( 0x01 << 0);
         leds.flush();
      }
      if(count == 2){
         leds.write(0x01 << 0 | 0x01 << 1);  
         leds.flush();
      }
      if(count == 3){
         leds.write(0x01 << 0 | 0x01 << 1 | 0x01 << 2);  
         leds.flush();
      }
      if(count == 4){
         leds.write(0x01 << 0 | 0x01 << 1 | 0x01 << 2 | 0x01 << 3);  
         leds.flush();
      }
      if(count == 5){
         leds.write(0x01 << 0 | 0x01 << 1 | 0x01 << 2 | 0x01 << 3 | 0x01 << 4);  
         leds.flush();
      }
      if(count == 6){
         leds.write(0x01 << 0 | 0x01 << 1 | 0x01 << 2 | 0x01 << 3 | 0x01 << 4 | 0x01 << 5);  
         leds.flush();
      }
      if(count == 7){
         leds.write(0x01 << 0 | 0x01 << 1 | 0x01 << 2 | 0x01 << 3 | 0x01 << 4 | 0x01 << 5 | 0x01 << 6);  
         leds.flush();
      }
      if(count == 8){
         leds.write(0x01 << 0 | 0x01 << 1 | 0x01 << 2 | 0x01 << 3 | 0x01 << 4 | 0x01 << 5 | 0x01 << 6 | 0x01 << 7);
         leds.flush();
      }
      if(count == 9){
         leds.write(0x01 << 8);  
         leds.flush();
      }
      
   }
}

int main( void ){	  

   namespace target = hwlib::target;

   auto ds       = target::pin_out( target::pins::d8 );
   auto shcp     = target::pin_out( target::pins::d9 );
   auto stcp     = target::pin_out( target::pins::d10 );

   auto spi_bus  = hwlib::spi_bus_bit_banged_sclk_mosi_miso(stcp, ds, hwlib::pin_in_dummy);
   auto hc = hwlib::hc595( spi_bus, shcp );

   auto led4 = hwlib::target::pin_out( hwlib::target::pins::d5 );
   auto led5 = hwlib::target::pin_out( hwlib::target::pins::d4 );
   auto led6 = hwlib::target::pin_out( hwlib::target::pins::d3 );
   auto led7 = hwlib::target::pin_out( hwlib::target::pins::d2 );

   auto leds = hwlib::port_out_from( hc.p0, hc.p1, hc.p2, hc.p3, led4, led5, led6, led7);

   hwlib::kitt( leds );


}