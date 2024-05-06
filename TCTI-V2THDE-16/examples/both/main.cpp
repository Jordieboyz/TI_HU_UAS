// project-includes
#include "hwlib.hpp"
#include "rtos.hpp"

// lib-includes
#include "../../include/RunGameControl.hpp"
#include "../../include/ReceiveIRControl.hpp"
#include "../../include/RegisterGameParamControl.hpp"
#include "../../include/Button.hpp"

int main()
{
    namespace target = hwlib::target;
    hwlib::wait_ms( 1000 );

    auto out0       = target::pin_oc( target::pins::a0 );
    auto out1       = target::pin_oc( target::pins::a1 );
    auto out2       = target::pin_oc( target::pins::a2 );
    auto out3       = target::pin_oc( target::pins::a3 );

    auto in0        = target::pin_in( target::pins::a4 );
    auto in1        = target::pin_in( target::pins::a5 );
    auto in2        = target::pin_in( target::pins::a6 );
    auto in3        = target::pin_in( target::pins::a7 );

    auto out_port   = hwlib::port_oc_from( out0, out1, out2, out3 );
    auto in_port    = hwlib::port_in_from( in0,  in1,  in2,  in3  );
    auto matrix     = hwlib::matrix_of_switches( out_port, in_port );
    auto key        = hwlib::keypad< 16 >( matrix,  "147*2580369#ABCD"  );

    auto diode      = target::d2_36kHz();
    //auto diode       = target::pin_out( target::pins::d2);

    auto fireLed    = target::pin_out( target::pins::d4);
    auto buttonPin  = target::pin_in( target::pins::d5);
    auto spk        = target::pin_out( target::pins::d6);
    auto hitLed     = target::pin_out( target::pins::d7);

    auto receiver   = target::pin_in( target::pins::d8 );

    auto scl     = target::pin_oc( target::pins::scl );
    auto sda     = target::pin_oc( target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
    auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c );

    //TODO: temp
    auto gnd        = target::pin_out( target::pins::d9 );
    auto vcc        = target::pin_out( target::pins::d10 );

    gnd.write( 0 );
    vcc.write( 1 );
    gnd.flush();
    vcc.flush();


    GameSettings g;
    PlayerInfo p;
    // init gameLeader
    //p.playerID.write( 0 );

    Button button = Button(buttonPin);
    Keypad keypad = Keypad(key);
    DisplayControl display = DisplayControl(oled);
    RunGameControl run = RunGameControl( fireLed, hitLed, button, spk, g, p, diode, display);
    RegisterGameParamControl paramControl = RegisterGameParamControl(run, display, g, p, keypad);
    ReceiveIRControl IRReceive = ReceiveIRControl(receiver, run, paramControl);

    //TODO: debug
    paramControl.startSettingUp(1010);

    rtos::run();
}