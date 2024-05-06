#ifndef RECEIVEIRCONTROL_HPP
#define RECEIVEIRCONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "RunGameControl.hpp"
#include "RegisterGameParamControl.hpp"

/**
 * @brief
 *  The Receive Control Class
 * @details
 *  This is an very straight forwars class. It has a high priority, because it just
 *  has te wait for any signal. This class is used everywhere and is always active.
 *  Just to don't miss any signals/shots etc. etc.
 */
class ReceiveIRControl : public rtos::task<> {
public:
    /**
     * @brief
     *  The "ReceiveControl" constructor
     * @details
     *  The ReceiveControl constructor needs a virtual arduino pin to receive any signal.
     *  This class controls every dat sent to the arduino. Which means. it needs to detect wheter the actual game needs to start
     *  or something else. The second and third parameter are to get a link to the other classes which needs to get initialized 
     *  @param signal       A virtual input pin
     *  @param run          The RunGameControl class. If there's a specific signal received. the .startGame function will get called to initialize the game
     *  @param paramControl If the class receives a specific signal, the .startSettingUp() function of this class will get called to start initializing this class.
     */
    ReceiveIRControl(hwlib::pin_in& signal, RunGameControl& run, RegisterGameParamControl& paramControl) :                 // const RunGameControl *gameController
        task( 2, "ReceiveControlTaak" ),
        signal( signal ),
        run(run),
        paramControl(paramControl)
    {}

private:
    enum state_t : int {WAIT_FOR_SIGNAL, DECODE};

    state_t state = WAIT_FOR_SIGNAL;

    hwlib::pin_in& signal;

    unsigned timings[16];

    RunGameControl& run;
    RegisterGameParamControl& paramControl;

    void main() override;
};

#endif