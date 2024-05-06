#include "../include/RunGameControl.hpp"

void RunGameControl::main()
{
    while(true)
    {
        switch(state)
        {
            case IDLE:
                wait(RunGameFlag);

                //init
                IRSend.init();

                state = START_COUNTDOWN;
                break;
            
            case START_COUNTDOWN:
                displayControl.clear();
                while(gameSettings.startTime.read() != 0)
                {
                    //TODO: display?? en dit is voor debug uiteraard
                    displayControl.write_digit((char*)"Starting in:    \n", gameSettings.startTime.read());

                    hwlib::wait_ms( 1000 );
                    gameSettings.startTime.write( gameSettings.startTime.read() - 1 );
                }
                displayControl.clear();
                state = NORMAL;
                break;

            case NORMAL:
                auto event = wait( HitReceivedFlag + buttonFlag + gameClock + cooldownTimer);
                if(event == HitReceivedFlag){
                    hitLed.write(1);

                    uint16_t rBits = HitReceivedChannel.read();
                    uint8_t fp = (rBits >> 5) & 0x1F;
                    uint8_t pID = (rBits >> 10) & 0x1F;

                    p.players[pID].firePower.write(fp);
                    p.players[pID].hits.write(p.players[pID].hits.read() + 1);

                    speaker.play("hit");

                    displayControl.write_digit((char*)"\nlast hit\nby player: ", (int)pID);

                    cooldownTimer.set(((fp * 100) + 100) * rtos::ms);
                }
                if(event == buttonFlag && !onCooldown){
                    fireLed.write( 1 );
                    IRSend.fire();
                    speaker.play("shoot");
                    hwlib::wait_ms(10);

                    cooldownTimer.set(((p.players[p.playerID.read() - 1].firePower.read() * 100) + 100) * rtos::ms);
                    onCooldown = true;

                    //TODO: debug
                    //hwlib::cout << "cd: " << ((p.players[p.playerID.read() - 1].firePower.read() * 100) + 500) << '\n';

                    //TODO: shitty debug code
                    //HitReceived(0x0000);
                }
                if(event == gameClock){
                    if(gameSettings.gameTime.read() != 0 ){
                        gameSettings.gameTime.write( gameSettings.gameTime.read() - 1 );

                        //TODO: debug code
                        //hwlib::cout << "t = " << gameSettings.gameTime.read() << '\n';

                        displayControl.write_digit((char*)"time: ", gameSettings.gameTime.read());
                    }
                    if(gameSettings.gameTime.read() == 0)
                    {
                        displayControl.write_data((char*)"The game is over\ngo to the\ngameleader to\nsee your score!  ");
                        state = IDLE;
                        break;
                    }
                }
                if(event == cooldownTimer) {onCooldown = false; fireLed.write( 0 ); hitLed.write(0);};

                break;
        }
    }
}

void RunGameControl::startGame()
{
    RunGameFlag.set();
}
