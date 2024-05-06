#include "hwlib.hpp"
#include "st7789_commands.hpp"


class  st7789_black_white : public _st7789, public hwlib::window {
private:
   int i = 0;
   hwlib::spi_bus & bus;
   hwlib::pin_out & dc;
   hwlib::pin_out & cs;
   hwlib::pin_out & rst;

   static auto constexpr wsize = hwlib::xy( 240, 240 );
   uint8_t buffer[ (wsize.x * wsize.y)/8 ];
        
   void write_implementation( hwlib::xy pos, hwlib::color col ) override {

      if( col != hwlib::black ){ 
         buffer[ pos.x + wsize.x * (pos.y/8) ] |=  ( 0x01 << (pos.y % 8 ));  
      } else {
         buffer[ pos.x + wsize.x * (pos.y/8) ] &= ~( 0x01 << (pos.y % 8 )); 
      }
   }

public:

   void command( commands c )
   {
      dc.write( 0 ); dc.flush();
      auto transaction = bus.transaction( cs );
      transaction.write( static_cast< uint8_t >( c ) );      
      dc.write( 1 ); dc.flush();
   }

   void command( commands  c, uint8_t d0 )
   {
      dc.write( 0 ); dc.flush();
      auto transaction = bus.transaction( cs );
      transaction.write( static_cast< uint8_t >( c ) );
      dc.write( 1 ); dc.flush();
      transaction.write( d0 );           
   } 
   
   void command( commands c, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3 )
   {
      dc.write( 0 ); dc.flush();
      auto transaction = bus.transaction( cs );
      transaction.write( static_cast< uint8_t >( c ) );      
      dc.write( 1 ); dc.flush();
      transaction.write( d0 );    
      transaction.write( d1 );    
      transaction.write( d2 );    
      transaction.write( d3 );    
   } 	
   
   st7789_black_white( hwlib::spi_bus & bus, hwlib::pin_out & dc, hwlib::pin_out & cs, hwlib::pin_out & rst ):
      window( wsize, hwlib::white, hwlib::black ),
      bus( bus ), dc( dc ), cs( cs ), rst( rst )
   {       
      rst.write( 0 );rst.flush();
      hwlib::wait_ms( 200 );
      rst.write( 1 );rst.flush();
      hwlib::wait_ms( 200 );
      
      command( commands::SWRESET );
      hwlib::wait_ms( 150 );
      
      command( commands::SLPOUT );
      hwlib::wait_ms( 10 );
      
      command( commands::COLMOD, 0x66 );
      hwlib::wait_ms( 10 );
      
      command( commands::MADCTL, 0x10 );                      
      command( commands::CASET, 0, 0, wsize.x >> 8, wsize.x & 0xFF );
      command( commands::RASET, 0, 0, wsize.y >> 8, wsize.y & 0xFF );
      
      command( commands::INVON );
      hwlib::wait_ms( 10 );
      command( commands::NORON );
      hwlib::wait_ms( 100 );
      command( commands::DISPON );
      hwlib::wait_ms( 100 );
   }     

   void flush() override 
   {
      dc.write( 0 ); dc.flush();
      auto transaction = bus.transaction( cs );
      transaction.write( static_cast< uint8_t >( commands::RAMWR ) );     
      dc.write( 1 ); dc.flush();

      uint8_t clr = 0;
      for( int i = 0; i < (wsize.x * wsize.y)/8; i++ ){
         for(unsigned int j = 0; j < 8; j++){

            (buffer[i] >> j)? clr = 0xFF : clr = clr;
            
            transaction.write( clr );
            transaction.write( clr );
            transaction.write( clr );
         } 
      }
   }      
}; // class st7789_spi_dc_cs_rst1
