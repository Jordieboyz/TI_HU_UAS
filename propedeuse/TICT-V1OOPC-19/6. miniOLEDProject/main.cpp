#include "hwlib.hpp"

void make_border(hwlib::window & w, hwlib::xy start, hwlib::xy end){
   auto rectangle = hwlib::rectangle(start, end);
   rectangle.draw(w);
   w.flush();
}

void make_line(hwlib::window & w, hwlib::xy start, hwlib::xy end){
   auto line = hwlib::line(start, end);
   line.draw(w);
   w.flush();
}

void make_circle(hwlib::window & w, hwlib::xy start, uint_fast16_t radius){
   auto circle = hwlib::circle( start, radius);
   circle.draw(w);
   w.flush();
}

void make_rectangle(hwlib::window & w, hwlib::xy start, hwlib::xy end){
   auto rectangle = hwlib::rectangle(start, end);
   rectangle.draw( w );
   w.flush();  
}

void make_smiley(hwlib::window & w){
   make_circle( w, hwlib::xy(64, 30), 30);
   make_circle( w, hwlib::xy(49, 17), 8);
   make_circle( w, hwlib::xy(67, 17), 8);
   make_circle( w, hwlib::xy(46, 17), 1);
   make_circle( w, hwlib::xy(63, 17), 1);
   make_circle( w, hwlib::xy(60, 39), 10);
   make_line( w, hwlib::xy(74, 58), hwlib::xy(90, 58));
   make_line( w, hwlib::xy(54, 58), hwlib::xy(38, 58));
   make_line( w, hwlib::xy(38, 58), hwlib::xy(30, 64));
   make_line( w, hwlib::xy(90, 58), hwlib::xy(98, 64));
   w.flush();
}


int main( void ){

   namespace target = hwlib::target;

   auto scl     = target::pin_oc( target::pins::scl );
   auto sda     = target::pin_oc( target::pins::sda );
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
   auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c );

   auto part1 = hwlib::part( oled, hwlib::xy( 0, 0 ), hwlib::xy( 64, 32));
   auto part2 = hwlib::part( oled, hwlib::xy( 64, 0 ), hwlib::xy(128, 32));
   auto part3 = hwlib::part( oled, hwlib::xy( 30, 32 ), hwlib::xy( 70, 64));

   auto font1 = hwlib::font_default_8x8();

   auto wholeScreen = hwlib::terminal_from(oled, font1);
   auto screenDown = hwlib::terminal_from( part1, font1);
   auto screenLeftUp = hwlib::terminal_from( part2, font1);
   auto screenRightUp = hwlib::terminal_from( part3, font1); 

   int a = 0;
   oled.clear();
for(;;){
   screenDown << "\f" << "  LINE" << hwlib::flush;
   make_border( part1, hwlib::xy( 0, 9 ), hwlib::xy( 62, 30));
   make_line( part1, hwlib::xy(14, 15), hwlib::xy(58, 25));
   hwlib::wait_ms(200);
   screenDown << "\f" << "   " << a << hwlib::flush;
   a++;
   hwlib::wait_ms(200);


   screenLeftUp << "\f" << " CIRCLE" << hwlib::flush;
   make_border( part2, hwlib::xy( 1, 9 ), hwlib::xy(63, 30));
   make_circle( part2, hwlib::xy(32, 20), 6);
   hwlib::wait_ms(200);
   screenLeftUp << "\f" << "   " << a << hwlib::flush;
   a++;
   hwlib::wait_ms(200);

   screenRightUp << "\f" << "  RECT" << hwlib::flush;
   make_border( part3, hwlib::xy(0, 9), hwlib::xy(69, 31));
   make_rectangle( part3, hwlib::xy(10, 15), hwlib::xy(60, 25));
   hwlib::wait_ms(200);
   screenRightUp << "\f" << "    " << a << hwlib::flush;
   a++;
   hwlib::wait_ms(200);
   oled.clear();

   wholeScreen << "\f" << a << hwlib::flush;
   a++;
   make_smiley(oled);
   hwlib::wait_ms(500);
   oled.clear();
}

}

