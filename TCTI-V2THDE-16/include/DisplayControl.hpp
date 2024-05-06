#pragma once

#include "hwlib.hpp"
#include "rtos.hpp"

/**
 * @brief
 *  The Display Control Class
 * @details
 *  This class is a virtual Display. It represents a fysical display in the circuit.
 *  The use of the Display is vey important for the player experience. Without it, you can't play the game.
 *  All the messages need to flow through the display. This way, you're not chained to your laptop.
 */
class DisplayControl : public rtos::task<> {
public:
    /**
     * @brief
     *  The "DisplayControl" contructor
     * @details
     *  This is the contrustor for the DisplayControl class. The constructor needs a virtual window to write , AKA hwlib:::window.
     *  @param w                     the virtual window
     *  @param friend_of_gameleader  This controls whether the title of the display is "gameleader" or "Laser tag". 
     */
    DisplayControl( hwlib::window &w, bool friend_of_gameleader = 0 ) :
        task( 5, "displayControl" ),
        display( w ),
        dataStringFlag(this, "dataStringFlag"),
        digitFlag(this, "digitFlag"),
        clearFlag(this, "clearFlag"),
        dataStringPool("dataStringPool"),
        digitPool("digitPool"),
        write_for_gameleader( friend_of_gameleader)
    {}

    /**
     * @details
     *  This function writes a certain data string to the display. 
     * @param data_string       the data to be sent to the display
     */
    void write_data( char * data_string);

    /**
     * @details
     *  This function writes a certain digit at a certain point to the display. 
     *  @param pos              The position of the digit ont he display
     *  @param digit            Teh specified digit
     */
    void write_digit(char * pos, int digit);

    /**
     * @details
     *  This function clears the display.
     */
    void clear();

private:
    enum state_t : int { FORMAT, WAIT };

    state_t state = FORMAT;

    hwlib::window& display;

    rtos::flag dataStringFlag;
    rtos::flag digitFlag;
    rtos::flag clearFlag;

    rtos::pool<char *> dataStringPool;
    rtos::pool<int> digitPool;

    hwlib::string<5> position = "";

    bool write_for_gameleader;

    void main() override;
};