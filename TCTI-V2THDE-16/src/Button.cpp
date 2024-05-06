#include "../include/Button.hpp"

void Button::main()
{
    while(true)
    {
        wait(buttonClock);

        while(!inputPin.read()){
            hwlib::wait_ms(50);
            if(inputPin.read()){
                for(unsigned i = 0; i < atIndex; i++)
                {
                    listeners[i]->ButtonRegister(buttonID);
                }
                break;
            }
        }
    }
}

void Button::AppendButtonListener(ButtonListener* buttonListener)
{
    if(atIndex < (sizeof(listeners) >> 3))
    {
        listeners[atIndex] = buttonListener;
        atIndex++;
    }
}