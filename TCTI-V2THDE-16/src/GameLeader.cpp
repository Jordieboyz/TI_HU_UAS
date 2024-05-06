#include "../include/GameLeader.hpp"


void gameLeader::main()
{
    while(true)
    {
        switch(state)
        {
            case IDLE:
            {
                wait(initGameLeaderFlag);
                state = INIT;
                break;
            }
            //TODO: andere naam voor INIT?
            case INIT:
            {
                display.write_data((char*)"\f\nsetGameTime (A) \n     or     \nsendCommand (B) ");
                
                wait( keyPressedFlag );
                char c = keyChannel.read();

                if(c == 'A')
                {
                    // display.write_data((char*)"\f\ngame time (A)   \n     or     \nstart time (B)  \n");
                
                    // wait( keyPressedFlag );
                    // char initType = keyChannel.read();

                    // if(!(initType == 'A' || initType == 'B'))
                    // {
                    //     display.write_data((char*)"wrong input     \ntry again       \n(press any key  \nto continue)    \n");
                    //     wait( keyPressedFlag );
                    //     keyChannel.read();
                    //     state = INIT;
                    //     break;
                    // }

                    char time[3] = {};
                    int n = 0;

                    display.write_data((char*)"\f   Time: \t1002min\n(max 31)");

                    char * cmd = (char*)"\t0602";
                    while(true){
                        wait( keyPressedFlag );
                        char a = keyChannel.read();
                        
                        if(a == '#'){
                            uint16_t total = 0;
                            if(n == 2)
                                total = (time[0] - '0')*10 + time[1] - '0';
                            else 
                                total = time[0] - '0';

                            if(total > 0 && total < 32)
                            {
                                g.gameTime.write(total);
                            }
                            else
                            {
                                display.clear();
                                display.write_data((char*)"\f\nwrong input     \n(max 31)");
                            }
                            state = INIT;
                            break;
                        }
                        if( a >= 48 && a <= 57)
                        {
                            time[n] = a;
                            display.write_digit(cmd, a - '0');
                            // TODO: WORKING ON THIS
                            // hwlib::cout << cmd[2] << hwlib::endl;

                            n++;
                            // cmd[2] = (int)cmd[2] + 1;
                            cmd = (char*)"\t0702";
                            // hwlib::cout << cmd[2] << hwlib::endl;
                            // hwlib::cout << (int)cmd[2]+1 << hwlib::endl;
                            // hwlib::cout << cmd << hwlib::endl;
                        }
                        if(n > 2 ){
                            display.clear();
                            display.write_data((char*)"\f\nwrong input     ");
                            hwlib::wait_ms(2000);
                            state = INIT;
                            break;
                        }
                    }
                }
                else if(c == 'B'){
                    state = START;
                    break;
                }
                break;
            }
            case START:
            {
                display.write_digit((char*)"\f Send a Command\n (A)    |   (B) \n game   |  start\n time   |        \nstart time: ", g.startTime.read());

                auto event = wait( keyPressedFlag + startTimeClock );

                if(event == keyPressedFlag)
                {
                    char c2 = keyChannel.read();
                    
                    if(c2 == 'A')
                    {
                        p.players[p.playerID.read() - 1].firePower.write(g.gameTime.read());
                    }
                    if(c2 == 'B')
                    {
                        if(g.startTime.read() == 0 ) {g.startTime.write(310);}
                        p.players[p.playerID.read() - 1].firePower.write((g.startTime.read() / 10));
                    }
                    if(c2 == 'C')
                    {
                        state = INIT;
                        break;
                    }
                    sendIR.init();
                    sendIR.fire();
                    break;
                }
                if(event == startTimeClock){
                    if(g.startTime.read() != 0 )
                    {
                        g.startTime.write( g.startTime.read() - 1 );
                    }
                    break;
                }
            }
        }
    }
}

void gameLeader::initGameLeader()
{
    initGameLeaderFlag.set();
}

void gameLeader::keyPressed( char keyID )
{
    keyChannel.write( keyID );
    keyPressedFlag.set();
}