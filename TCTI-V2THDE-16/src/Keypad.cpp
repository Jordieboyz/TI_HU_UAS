#include "../include/Keypad.hpp"

void Keypad::main()
{
    while(true)
    {
        char a = keypad.getc();

        for(unsigned i = 0; i < atIndex; i++)
        {
            listeners[i]->keyPressed( a );
        }
    }
}

void Keypad::AppendKeypadListener(KeypadListener* keypadListener)
{
    if(atIndex < (sizeof(listeners) >> 3))
    {
        listeners[atIndex] = keypadListener;
        atIndex++;
    }
}