#include "hwlib.hpp"

extern "C" void uart_put_char( char c);
extern "C" void application( const char * p );
extern "C" char upper_lower_case( char c);

void uart_put_char( char c ){
   hwlib::cout << c;
}

char upper_lower_case( char c){
   if(c >= 65 && c <= 90) {
      c += 32;
   } 
   else if(c >= 97 && c <= 122) {
      c -= 32;
   }
   return c;
}

int main( void ){	
   
   namespace target = hwlib::target;   
    
   // wait for the PC console to start
   hwlib::wait_ms( 2000 );

   application( "hELLO WORLD, THE answer IS 42! @[]`{}~\n" );
}