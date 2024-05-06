#include "../include/ReceiveIRControl.hpp"

void ReceiveIRControl::main()
{
    while(true)
    {
        switch(state)
        {   
            case WAIT_FOR_SIGNAL :
            { 
                while(signal.read()){
                    hwlib::wait_ms(1);
                }
                int i = 0;
                while(i != 16)
                {
                    if(!signal.read())
                    {
                        uint64_t timer = hwlib::now_us();
                        while(!signal.read()){hwlib::wait_us(100);};
                        //auto time = (hwlib::now_us()-timer);

                        timings[i] = (hwlib::now_us() - timer);
                        i++;
                    }
                }
                state = DECODE;
                break;
            }
            case DECODE :
            {
                uint16_t receivedBits = 0;
                for(unsigned i = 0; i < 16; i++)
                {
                    receivedBits = receivedBits << 1;
                    if(timings[i] > 1200)
                    {
                        receivedBits |= 0x01;
                    }
                }
                
                if( ((receivedBits >> 10) & 0x1F) != 0)
                {
                    run.HitReceived(receivedBits);
                }
                else
                {
                    paramControl.startSettingUp(receivedBits);
                }

                //TODO:temp, print timings
                for(unsigned i = 0; i < (sizeof(timings) >> 2); i++)
                {
                    hwlib::cout << timings[i] << '\n';
                }
                //TODO

                state = WAIT_FOR_SIGNAL;
                break;
            }
        }
    }
}