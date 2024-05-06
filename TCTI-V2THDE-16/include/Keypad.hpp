#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

//classes
#include "KeypadListener.hpp"

/**
 * @brief
 *  The Keypad Class
 * @details
 *  This class is a virtual keypad. It represents a fysical keypad in the circuit.
 *  It is pretty usefull to have a keypad, but realisticly, you dont need it. You could just initialize everything before 
 *  the game and you're fine as well. But we had to use it and it worked out just fine. It makes hand-free initializing just a 
 *  little bit easier.
 */
class Keypad : public rtos::task<> {
public:
    /**
     * @brief
     *  The "Keypad" constructor
     * @details
     *  The Keypad constructor only needes a inputstream so data (in our case [0-9] and [A-D]), AKA the 8 analog pins on the arduino
     *  @param keypad           The inputstream for the keypad.
     * 
     */
    Keypad(hwlib::istream& keypad) :
        task(10, "Keypad"),
        keypad(keypad)
    {}

    /**
     * @brief
     *  Add a ButtonListener to the Button
     * @details
     *  To use a keypad in other classes, you use a keypadListener and this function adds one to "this" keypad.
     */
    void AppendKeypadListener(KeypadListener* keypadListener);

private:
    hwlib::istream& keypad;

    KeypadListener* listeners[5];
    unsigned atIndex = 0;

    void main() override;

};

#endif