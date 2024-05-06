#include "hwlib.hpp"

void kitt( hwlib::port_out & leds){
   unsigned int count = 0;
   for(;;){
      if (( PIOC->PIO_PDSR & ( 0x01 << 28)) == 0 ){ 
         if(count < 5){
            count++;
         }
         else{
            count = 1;
         }
         hwlib::wait_ms(200);
         }
      if ((PIOB->PIO_PDSR & (0x01 << 25)) == 0){
         if(count > 1){
            count--;
         }
         else{
            count = 5;
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
         leds.write(0x01 << 5);
         leds.flush();
      }
   }
}

int main( void ){	  
   auto led0 = hwlib::target::pin_out( hwlib::target::pins::d7 );
   auto led1 = hwlib::target::pin_out( hwlib::target::pins::d6 );
   auto led2 = hwlib::target::pin_out( hwlib::target::pins::d5 );
   auto led3 = hwlib::target::pin_out( hwlib::target::pins::d4 );

   auto leds = hwlib::port_out_from( led0, led1, led2, led3);
   ::kitt( leds );


}