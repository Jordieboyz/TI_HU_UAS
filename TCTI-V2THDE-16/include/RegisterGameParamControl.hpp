#ifndef REGISTERGAMEPARAMCONTROL_HPP
#define REGISTERGAMEPARAMCONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

//classes
#include "RunGameControl.hpp"
#include "Keypad.hpp"
#include "KeypadListener.hpp"

//structs
#include "headers/GameSettings.hpp"
#include "headers/PlayerInfo.hpp"

/**
 * @brief
 *  The RegisterGameParam Control Class
 * @details
 *  This class is only used when you're in the "inializing" state of the game.
 *  You need this class to setup every parameter, playerID or firePower. It is an important class,
 *  but it is not impossible to run the game without it. It's just a bit more hardcoding :();
 */
class RegisterGameParamControl : public rtos::task<>, public KeypadListener {
public:
    /**
     * @brief
     *  The "RegisterGameParamControl" constructor 
     * @details
     *  This Constructor is mainly for the player to set up their playerID or firePower etc etc.
     *  If every is set up, the runGame gets called to "start the game"
     *  @param runGame          Class which gets called to "start the game"
     *  @param displayControl   The Class which provides a display to write data to
     *  @param g                A struct where the data get saved
     *  @param p                A strcut where the data get saved
     *  @param k                A keypad used for user inputs
     */
    RegisterGameParamControl(RunGameControl& runGame, DisplayControl& displayControl, GameSettings& g, PlayerInfo& p, Keypad& k) :
        task(6, "RegisterGameParamTaak" ),
        KeypadListener(this),
        runGame( runGame ),
        displayControl(displayControl),
        keypad(k),
        g( g ),
        p( p ),
        startGamePool( "startGamePool" ),
        startGameFlag( this, "startGameFlag" )
    {
        keypad.AppendKeypadListener(this);
    }

    //TODO: andere naam kan handig zijn
    // void startGame( uint16_t gameTime );

    /**
	 * @brief
	 *  Set the flag to start initializing the RegisterParamControl.
	 */
    void startSettingUp( uint16_t gameTimeyy);

private:
    enum state_t : int  { IDLE, START, FIRST, SECOND, FINAL};

    state_t state = IDLE;

    char initType;
    char keyNumbers[2];

    RunGameControl& runGame;
    DisplayControl& displayControl;
    Keypad& keypad;

    GameSettings& g;
    PlayerInfo& p;

    rtos::pool<int> startGamePool;
    rtos::flag startGameFlag;

    void main() override;
};

#endif