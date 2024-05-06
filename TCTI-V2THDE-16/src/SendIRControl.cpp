#include "../include/SendIRControl.hpp"

void SendIRControl::main()
{
    while(true)
    {
        auto event = wait(fireFlag + initFlag);

        if(event == fireFlag)
        {
            uint8_t ctrlBits = 0;
            for(int i = 14; i > 9; i--)
            {
                bool bit = ((bool)(fireBits & (0x01 << i)) ^ (bool)(fireBits & (0x01 << (i - 5))));
            
                ctrlBits = ctrlBits << 1;
                ctrlBits |= bit;                 
            }
            fireBits |= ctrlBits;

            for( int i = 15; i >= 0; i-- )
            {
                if(fireBits & 1 << i)
                {

                    diode.write( 1 );
                    hwlib::wait_us_busy( 1600 );
                    diode.write( 0 );
                    hwlib::wait_us_busy( 800 );
                } 
                else
                {
                    diode.write( 1 );
                    hwlib::wait_us_busy( 800 );
                    diode.write( 0 );
                    hwlib::wait_us_busy( 1600 );
                }
            }
        }
        if(event == initFlag)
        {
            fireBits = 0;
            fireBits |= playerInfo.playerID.read();
            fireBits = fireBits << 5;
            fireBits |= playerInfo.players[playerInfo.playerID.read() - 1].firePower.read();
            fireBits = fireBits << 5;
            
            //TODO: debug
            hwlib::cout << fireBits << '\n';
        }
    }
}

void SendIRControl::fire()
{        
    // if(((bits >> 10) & 0x1F) == 0)
    //     fireBits = bits;
    fireFlag.set();
}

void SendIRControl::init()
{
    initFlag.set();
}