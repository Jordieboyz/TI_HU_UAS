#include <hwlib.hpp>
#include <iostream>
#include "wall.hpp"
#include "ball.hpp"

int main(){
   hwlib::target::window w( hwlib::xy( 128, 64 ), hwlib::white, hwlib::black, 7 );
   ball b      ( w, hwlib::xy(  50, 20 ), 9, hwlib::xy( 5, 2 ) );

   wall top    ( w, hwlib::xy(   0,  0 ), hwlib::xy( 127,  3 ) );
   wall right  ( w, hwlib::xy( 124,  0 ), hwlib::xy( 127, 63 ) );
   wall bottom ( w, hwlib::xy(   0, 59 ), hwlib::xy( 127, 63 ) );
   wall left   ( w, hwlib::xy(   0,  0 ), hwlib::xy(   3, 63 ) );

   std::array< drawable *, 5 > objects = { &bottom, &top, &right, &left, &b };

   for(;;){
      w.clear();
      for( auto & p : objects ){
         p->draw();
      }
      w.flush();
      hwlib::wait_ms( 75 );
      for( auto & p : objects ){
          p->update();
      }
      for( auto & p : objects ){
         for( auto & other : objects ){
            p->interact( *other );
         }
      }          
   } 
};