#include <hwlib.hpp>
#include <iostream>
#include "wall.hpp"
#include "ball.hpp"
#include "victim.hpp"

int main(){
   hwlib::target::window w( hwlib::xy( 128, 64 ), hwlib::white, hwlib::black, 7 );
   
   ball b      ( w, hwlib::xy(  50, 20 ), 9, hwlib::xy( 5, 2 ) );

   wall top    ( w, hwlib::xy(   0,  0 ), hwlib::xy( 127,  3 ), 2, hwlib::xy(1, -1) );
   wall right  ( w, hwlib::xy( 124,  0 ), hwlib::xy( 127, 63 ), 2, hwlib::xy(-1, 1) );
   wall bottom ( w, hwlib::xy(   0, 59 ), hwlib::xy( 127, 63 ), 2, hwlib::xy(1, -1) );
   wall left   ( w, hwlib::xy(   0,  0 ), hwlib::xy(   3, 63 ), 2, hwlib::xy(-1, 1) );

   victim middle(w, hwlib::xy(   80,   10), hwlib::xy(  90, 30 ) );

   std::array< drawable *, 6 > objects = { &bottom, &top, &right, &left, &b, &middle };

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
}
