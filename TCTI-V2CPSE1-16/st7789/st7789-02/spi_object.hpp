#include "hwlib.hpp"

class spi_object : public hwlib::spi_bus {
private:

   hwlib::pin_direct_from_out_t sclk;
   hwlib::pin_direct_from_out_t mosi;
   hwlib::pin_direct_from_in_t  miso;
   
   void write_and_read( 
      const size_t n, 
      const uint8_t data_out[], 
      uint8_t data_in[] 
   ) override {

      for( uint_fast8_t i = 0; i < n; ++i ){
          
         uint_fast8_t d = 
            ( data_out == nullptr )
            ? 0 
            : *data_out++;
             
         for( uint_fast8_t j = 0; j < 8; ++j ){
            mosi.write( ( d & 0x80 ) != 0 );
            sclk.write( 1 );
            d = d << 1;
            if( miso.read() ){
               d |= 0x01;
            }
            sclk.write( 0 );              
         }
          
         if( data_in != nullptr ){
            *data_in++ = d;
         }
      }
   }      
   
public:
   spi_object( 
      hwlib::pin_out & _sclk, 
      hwlib::pin_out & _mosi, 
      hwlib::pin_in  & _miso 
   ):
      
      sclk( _sclk ), 
      mosi( _mosi ), 
      miso( _miso )   {
      sclk.write( 0 );
   }
   
}; // class spi_object