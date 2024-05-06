#ifndef KEYPADLISTENER
#define KEYPADLISTENER

#include "rtos.hpp"
#include "hwlib.hpp"

class KeypadListener
{
protected:

    rtos::channel<char, 3> keyChannel;
    rtos::flag keyPressedFlag;

public:
    KeypadListener(rtos::task_base* task) :
        keyChannel(task, "keyChannel"),
        keyPressedFlag(task, "keyPressedFlag")
    {}

    /**
	 * @brief
	 *  Set the flag to inform the program that there's a keypadKey is pressed.
	 */
    void keyPressed( char keyID )
    {
        keyChannel.write( keyID );
        keyPressedFlag.set();
    }
};

#endif