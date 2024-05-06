#ifndef SENDIRCONTROL_HPP
#define SENDIRCONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "SpeakerControl.hpp"
#include "../include/headers/PlayerInfo.hpp"

/**
 * @brief
 *  The SendIR Control Class
 * @details
 *  This is a class which makes use of an 36Khz IR-diode. Which we use to send messages or better, "lasers" to other players.
 *  It is invincible for humans and very fast, but is still happens that you miss a byte or something. It's not perfect, but it works most of the time.
 *  This class also helps with a lot of other processes. Everyhting which involves shooting, this class is used.
 */
class SendIRControl : public rtos::task<> {
public:
    /**
     * @brief
     *  The "SendIRControl" class
     * @details
     *  The constructor of this class needs the IR-diode, or a virtual representation of an arduino pin where the diode is pinned.
     *  And the struct to send for example you're own data.
     *  @param diode        The IR-diode
     *  @param playerInfo   A struct to save data in.
     */
    SendIRControl(hwlib::pin_out& diode, PlayerInfo& playerInfo) :
        task(3, "send"),
        diode(diode),
        playerInfo(playerInfo),
        fireFlag(this, "fireFlag"),
        initFlag(this, "initFlag")
    {}

    //TODO: andere naam?
    /**
	 * @brief
	 *  Set the flag to inform the program that the player wants to shoot.
	 */
    void fire();
    
    /**
	 * @brief
	 *  Set the flag to start initializing the SendIRControl.
	 */
    void init();

private:
    
    uint16_t fireBits;

    hwlib::pin_out &diode;

    PlayerInfo& playerInfo;
    
    rtos::flag fireFlag;
    rtos::flag initFlag;
    
    void main() override;
};

#endif