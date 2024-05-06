#ifndef BUTTONLISTENER_HPP
#define BUTTONLISTENER_HPP

#include "rtos.hpp"
#include "hwlib.hpp"

/** @file **/

class ButtonListener
{
protected:
    rtos::pool<int> ButtonRegisterPool;
    rtos::flag buttonFlag;
public:
    ButtonListener(rtos::task_base* task) :
        ButtonRegisterPool("ButtonRegisterPool"),
        buttonFlag(task, "buttonFlag")
    {}

    /**
	 * @brief
	 *  Register a Button based on a buttonID
	 */
    void ButtonRegister( int buttonID )
    {
        ButtonRegisterPool.write(buttonID);
        buttonFlag.set();
    }
};

#endif