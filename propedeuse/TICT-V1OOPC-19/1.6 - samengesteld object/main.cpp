// example:
// a rectangle object that is contains four line objects

#include "auto.hpp"


int main(int argc, char **argv){
   hwlib::target::window w( hwlib::xy( 128 ,64 ));

   car car2(w, 40, 45, 70, 45, 2);
   car2.print();
   w.clear();
   hwlib::wait_ms(100);
   car car3(w, 40, 45, 70, 45, 3);
   car3.print();
   w.clear();
   hwlib::wait_ms(100);
   car car4(w, 40, 45, 70, 45, 4);
   car4.print();
   w.clear();
   hwlib::wait_ms(100);
   car car5(w, 40, 45, 70, 45, 5);
   car5.print();
   w.clear();
   hwlib::wait_ms(100);
   car car6(w, 40, 45, 70, 45, 6);
   car6.print();
   w.clear();
   hwlib::wait_ms(100);
   car car7(w, 40, 45, 70, 45, 7);
   car7.print();
   w.clear();
   hwlib::wait_ms(100);
   car car8(w, 40, 45, 70, 45, 8);
   car8.print();
   w.clear();
   hwlib::wait_ms(100);


   // keep the window around until we close it
   for(;;){ w.poll(); } 
          
}
