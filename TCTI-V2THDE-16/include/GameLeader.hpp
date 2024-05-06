#ifndef GAMELEADER_HPP
#define GAMELEADER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "SendIRControl.hpp"
#include "DisplayControl.hpp"
#include "Keypad.hpp"
#include "KeypadListener.hpp"

#include "headers/PlayerInfo.hpp"
#include "headers/GameSettings.hpp"

/**
 * @brief
 *  The GameLeader Class
 * @details
 *  This is one of the most important tasks in our whole program. Without the gameleader, you cannot initialize the game.
 *  The gameleader decides the length of the game (playtime) and when the game starts. It isn't a player, but is pretty much just 
 *  the startup for the game.
 */
class gameLeader : public rtos::task<>, public KeypadListener {
public:
    /**
     * @brief
     *  The "gameLeader" constructor
     * @details
     *  This is the gameLeader constructor. Teh gameLeader is not a player. It just decides the duration of the game and the time the game starts.
     *  It is able to send those data to the players to initialize them.
     *  @param k                A keypad to initialize the start an game time.
     *  @param send             The class which provides the tech to send an IR signal to the players.
     *  @param g                A struct where the data is saved.
     *  @param window           The display where to send data to             
     */
    gameLeader( Keypad& k, SendIRControl& send, GameSettings& g, PlayerInfo& p, hwlib::window& window) :
        task(11, "gameLeader"),
        KeypadListener(this),
        keypad(k),
        sendIR(send),
        display(window, true),
        g(g),
        p(p),
        startTimeClock(this, 1000 * rtos::ms, "StartTimeClock"),
        initGameLeaderFlag(this, "GLFlag")
    {
        keypad.AppendKeypadListener(this);
    }

    /**
	 * @brief
	 *  Set the flag to start initializing the gameLeader.
	 */
    void initGameLeader();
    
    /**
	 * @brief
	 *  Set the flag to inform the program that there's a button pressed.
	 */
    void keyPressed( char keyID );

private:
    enum state_t : int { IDLE, INIT, START };

    state_t state = IDLE;

    uint16_t commandBits = 0;

    Keypad& keypad;
    SendIRControl& sendIR;
    DisplayControl display;

    GameSettings& g;
    PlayerInfo& p;

    rtos::clock startTimeClock;

    rtos::flag initGameLeaderFlag;

    void main() override;
};

#endif