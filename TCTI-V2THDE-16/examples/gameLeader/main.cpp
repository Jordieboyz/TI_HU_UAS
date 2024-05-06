// project-includes
#include "hwlib.hpp"
#include "rtos.hpp"

// lib-includes
#include "../../include/SendIRControl.hpp"
#include "../../include/GameLeader.hpp"

int main()
{
    namespace target = hwlib::target;
    hwlib::wait_ms( 500 );

    auto out0     = target::pin_oc( target::pins::a0 );
    auto out1     = target::pin_oc( target::pins::a1 );
    auto out2     = target::pin_oc( target::pins::a2 );
    auto out3     = target::pin_oc( target::pins::a3 );

    auto in0      = target::pin_in( target::pins::a4 );
    auto in1      = target::pin_in( target::pins::a5 );
    auto in2      = target::pin_in( target::pins::a6 );
    auto in3      = target::pin_in( target::pins::a7 );

    auto out_port = hwlib::port_oc_from( out0, out1, out2, out3 );
    auto in_port  = hwlib::port_in_from( in0,  in1,  in2,  in3  );
    auto matrix   = hwlib::matrix_of_switches( out_port, in_port );
    auto key      = hwlib::keypad< 16 >( matrix,  "147*2580369#ABCD"  );

    auto scl     = target::pin_oc(target::pins::scl);
    auto sda     = target::pin_oc(target::pins::sda);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
    auto oled    = hwlib::glcd_oled(i2c_bus, 0x3c);

    
    auto diode    = target::d2_36kHz();
    auto button   = target::pin_in( target::pins::d5);

    GameSettings g;
    PlayerInfo p;

    // init gameLeader
    p.playerID.write( 0 );

    Keypad keypad = Keypad(key);

    SendIRControl send = SendIRControl(diode, p);
    gameLeader GameLeader = gameLeader(keypad, send, g, p, oled);
    GameLeader.initGameLeader();

    rtos::run();
}