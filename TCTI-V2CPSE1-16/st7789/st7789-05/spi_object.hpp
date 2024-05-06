#include "hwlib.hpp"

class spi_object : public hwlib::spi_bus {
private:
   uint_fast8_t clk;
   uint_fast8_t mosi;

   void write_and_read( const size_t n, const uint8_t data_out[], uint8_t data_in[]) override 
   {       
      uint_fast8_t d = *data_out;
      for( uint_fast8_t j = 0; j < 8; ++j )
      {            
         if(( d & 0x80 ) != 0 )
         {
            PIOC->PIO_SODR = 0x01 << mosi;
         } else {
            PIOC->PIO_CODR = 0x01 << mosi; 
         }

         PIOC->PIO_CODR = 0x01 << clk;
         d = d << 1;
         PIOC->PIO_SODR = 0x01 << clk;    
      }
   }      
   
public:
   spi_object( uint_fast8_t _clk, uint_fast8_t _mosi ) : 
      clk( _clk ), mosi( _mosi )
   { 
      PIOC->PIO_OER = 0x01 << clk;
      PIOC->PIO_OER = 0x01 << mosi;
      PIOC->PIO_SODR = 0x01 << clk;
   }
   
}; // class spi_object   
