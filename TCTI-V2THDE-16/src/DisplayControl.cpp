#include "../include/DisplayControl.hpp"

void DisplayControl::main(){
    while(true)
    {
        switch( state )
        {
            case FORMAT :
            {  
                auto f =  hwlib::font_default_8x8();
                auto p1 = hwlib::part( display, hwlib::xy( 0, 0 ), hwlib::xy( 128, 24));
                auto d1 = hwlib::terminal_from( p1, f );
                display.clear();
                
                if(write_for_gameleader){
                    d1 << "\f"
                       << "\n   GAMELEADER   \n"
                       << "=================" << hwlib::flush;
                } else {
                    d1 << "\f"
                       << "\n   LASER TAG   \n"
                       << "=================" << hwlib::flush;
                }
                state = WAIT;
                break;
            }

            case WAIT :
            {   
                auto f =  hwlib::font_default_8x8();
                auto p2 = hwlib::part( display, hwlib::xy( 0, 24 ), hwlib::xy( 128, 64));
                auto d2 = hwlib::terminal_from( p2, f );

                auto event = wait( dataStringFlag + digitFlag + clearFlag);


                if(event == dataStringFlag)
                    d2 << dataStringPool.read() << hwlib::flush;
                if(event == digitFlag){
                    d2 << dataStringPool.read() << digitPool.read() << hwlib::flush;
                }
                if(event == clearFlag){
                    d2 << "                \n                \n                \n                \n" << hwlib::flush;
                }
                state = WAIT;
                break;
            }
        }
    }
}

void DisplayControl::write_digit(char * pos, int digit){
    // position = pos;
    dataStringPool.write(pos);
    digitPool.write(digit);
    digitFlag.set();
}

void DisplayControl::write_data( char * data_string){
    dataStringPool.write(data_string);
    dataStringFlag.set();
}

void DisplayControl::clear(){
    clearFlag.set();
}