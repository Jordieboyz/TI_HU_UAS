// project-includes
#include "hwlib.hpp"
#include "rtos.hpp"

// lib-includes
#include "../../include/RunGameControl.hpp"

int main()
{
    namespace target = hwlib::target;
    hwlib::wait_ms( 500 );

    auto diode = target::d2_36kHz();
    auto led = target::pin_out( target::pins::d4);
    auto button = target::pin_in( target::pins::d5);
    auto spk = target::pin_out( target::pins::d6);

    GameSettings g;
    g.startTime.write(2);
    g.gameTime.write(3000);
    
    PlayerInfo p;
    p.playerID.write( 31 );
    p.players[30].firePower.write(15);

    RunGameControl run = RunGameControl( led, button, spk, g, p, diode);
    run.startGame();

    rtos::run();
}