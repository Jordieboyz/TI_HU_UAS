// example:
// a rectangle object that is contains four line objects

#include "hwlib.hpp"
#include "rectangle.hpp"

int main(int argc, char **argv){
    
   // the window in which we want to print the line
   hwlib::target::window w( hwlib::xy( 128 ,64 ));    
    
   filled_rectangle rechthoek(w, 5,5, 55, 20);
   rechthoek.draw(255, 0, 0);

   filled_rectangle rechthoek2(w, 40, 5, 120, 20);
   rechthoek2.draw(0, 255, 0);

   for(;;){ w.poll(); }       
}
