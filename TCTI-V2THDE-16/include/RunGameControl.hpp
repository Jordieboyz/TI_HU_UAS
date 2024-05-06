#ifndef RUNGAMECONTROL_HPP
#define RUNGAMECONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

// classes
#include "SpeakerControl.hpp"
#include "SendIRControl.hpp"
#include "DisplayControl.hpp"
#include "ButtonListener.hpp"
#include "Button.hpp"


// struct headers
#include "../include/headers/GameSettings.hpp"
#include "../include/headers/PlayerInfo.hpp"

/**
 * @brief
 *  The RunGame Control Class
 * @details
 *  This is the most important class. It just doest almoast everything. like, it glues everything together.
 *  Most of the actions are being performed in combination with this class. This class knows about the gameTime, startTime, hits and much more.
 *  It is kinda the brain of our program.
 */
class RunGameControl : public rtos::task<>, public ButtonListener {
public:
    /**
     * @brief
     *  The "RunGameControl" constructor
     * @details
     *  The constructor of this class needs a lot of things. It is the biggest and most important class.
     *  @param fireLed          A LED to indicate the firing cooldown
     *  @param hitLed           A LED to indicate that you've been hit
     *  @param button           A button mainly for shooting
     *  @param spkPin           The pin the speaker needs to output sounds
     *  @param gSet             A struct to save f.e. gameTime and startTime in
     *  @param pInf             A struct to save data from yourself and other players in
     *  @param diode            The IR-diode to send 36Khz signals
     *  @param displycontrol    The class which provides usage of the display
     */
    RunGameControl( hwlib::pin_out &fireLed,
                    hwlib::pin_out &hitLed,
                    Button &button,
                    hwlib::pin_out &spkPin,
                    GameSettings &gSet,
                    PlayerInfo &pInf,
                    hwlib::pin_out &diode,
                    DisplayControl& displayControl
                    ) :
        task(1, "GameControlTaak"),
        ButtonListener(this),
        fireLed(fireLed),
        hitLed(hitLed),
        button(button),
        speaker(spkPin),
        IRSend(diode, pInf),
        displayControl(displayControl),
        HitReceivedChannel(this, "HitReceivedChannel"),
        HitReceivedFlag(this, "hitReceivedFlag"),
        RunGameFlag(this, "RunGameFlag"),
        gameClock(this, 1000 * rtos::ms, "blink"),
        cooldownTimer(this, "CooldownTimer"),
        gameSettings(gSet),
        p(pInf)
    {
        button.AppendButtonListener(this);
    }

    /**
	 * @brief
	 *  Set the flag to start game.
	 */
    void startGame();

    /**
	 * @brief
	 *  Set the flag to inform the program that the player got hit.
	 */
    void HitReceived( uint16_t bits ){
        HitReceivedChannel.write(bits);
        HitReceivedFlag.set();
    }
    
private:
    enum state_t : int { START_COUNTDOWN, NORMAL, IDLE };

    state_t state = IDLE;

    hwlib::pin_out &fireLed;
    hwlib::pin_out &hitLed;

    Button &button;

    SpeakerControl speaker;
    SendIRControl IRSend;
    DisplayControl& displayControl;
    

    rtos::channel<uint16_t, 1> HitReceivedChannel;

    rtos::flag HitReceivedFlag;    
    rtos::flag RunGameFlag;
    rtos::clock gameClock;
    rtos::timer cooldownTimer;

    GameSettings &gameSettings;
    PlayerInfo &p;

    bool onCooldown = false;

    void main() override;
};

#endif