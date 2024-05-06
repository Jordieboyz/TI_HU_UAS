#ifndef BUTTON_HPP
#define BUTTON_HPP

// project-includes
#include "rtos.hpp"
#include "hwlib.hpp"

// class-includes
#include "ButtonListener.hpp"

/**
 * @brief
 *  The Button Class
 * @details
 *  This class is a virtual button. It represents a fysical button in the circuit.
 *  This Button-class detects and informs the "ButtonListener" when a specific button is pressed.
 *  So, you also need a ButtonListener for this to work.
 */
class Button : public rtos::task<> {
public:
    /**
     * @brief
     *  The "Button" constructor
     * @details
     *  This is the Button constructor. This contructor needs a virtual representation of a Arduino-pin, AKA an hwlib::pin_in.
     *  The buttonID is for the most part important for the used ButtonListener, because it can distinguish the differenet buttons.
     *  @param input            The virtual-arduino-pin (hwlib::pin_in)
     *  @param buttonID         A given number for this button
     */
    Button(hwlib::pin_in &input, unsigned buttonID = 0) :
        inputPin(input),
        buttonClock(this, 100 * rtos::ms, "buttonClock2"),
        buttonID(buttonID)
    {}

    /**
     * @brief
     *  Add a ButtonListener to the Button
     * @details
     *  To use a button in other classes, you use a ButtonListener and this function adds one to "this button".
     */ 
    void AppendButtonListener(ButtonListener* buttonListener);


private:    
    hwlib::pin_in& inputPin;
    rtos::clock buttonClock;

    unsigned buttonID;

    ButtonListener* listeners[5];
    unsigned atIndex = 0;
    
    void main() override;
};

#endif