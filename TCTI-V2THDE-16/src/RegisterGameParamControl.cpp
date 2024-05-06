#include "../include/RegisterGameParamControl.hpp"

void RegisterGameParamControl::main()
{
    while(true)
    {
        switch( state )
        {
            case IDLE : 
            {
                //TODO: ???
                //displayControl.write_data((char*)"waiting for     \ngametime...     \n");

                wait(startGameFlag);

                // not yet initialized
                if(g.gameTime.read() == 0)
                {
                    //TODO: check dit na, klopt dit??
                    g.gameTime.write((((startGamePool.read() >> 5) & 0x1F) * 60));

                    state = START;
                }
                //wait until gametime is received
                else
                {
                    g.startTime.write((((startGamePool.read() >> 5) & 0x1F) * 10));
                    runGame.startGame();
                    state = IDLE;
                }
                break;
            }
            case START :
            {
                displayControl.write_data((char*)"select:         \nplayerID (A)    \nFirepower (B)   \nReady (C)       ");

                wait( keyPressedFlag );
                char keyID = keyChannel.read();

                if( keyID == 'A' || keyID == 'B')
                {
                    initType = keyID;
                    state = FIRST;
                    break;
                }
                else if(keyID == 'C')
                {
                    initType = keyID;
                    state = FINAL;
                    break;
                }
                else
                {
                    displayControl.write_data((char*)"wrong input     \ntry again       \n(press any key  \nto continue)    \n");
                    wait( keyPressedFlag );
                    keyChannel.read();
                    state = START;
                    break;
                }
            }
            case FIRST :
            {
                displayControl.write_data((char*)"specify value   \n(2 digits)      \n                \n                \n");

                wait( keyPressedFlag );
                char keyID = keyChannel.read();
                
                if( keyID >= 48 && keyID <= 57)
                {
                    //TODO: debug
                    hwlib::cout << keyID;
                    
                    keyNumbers[0] = keyID;
                    state = SECOND;
                }
                else 
                {
                    state = FIRST;
                }
                break;
            }
            case SECOND: 
            {
                wait( keyPressedFlag );
                char keyID = keyChannel.read();

                if( keyID >= 48 && keyID <= 57)
                {
                    hwlib::cout << keyID << "\n";
                    keyNumbers[1] = keyID;
                    state = FINAL;
                    break;
                }
                else if( keyID == '#')
                {
                    keyNumbers[1] = keyNumbers[0];
                    keyNumbers[0] = '0';
                    state = FINAL;
                    break;
                }
                break;
            }
            case FINAL :
            {
                if(initType == 'A')
                {
                    int playerAIDIE = (((keyNumbers[0] - 48) * 10) + (keyNumbers[1] - 48));
                    if( playerAIDIE >= 32)
                    {
                        playerAIDIE = 31;
                    }
                    p.playerID.write( playerAIDIE );

                    state = START;
                    break;
                }
                else if(initType == 'B')
                {
                    int faierPouwer = (((keyNumbers[0] - 48) * 10) + (keyNumbers[1] - 48));
                    if( faierPouwer >= 32)
                    {
                        faierPouwer = 31;
                    }
                    p.players[p.playerID.read() - 1].firePower.write( faierPouwer );

                    state = START;
                    break;
                }
                else if(initType == 'C')
                {
                    if((p.playerID.read() == 0) || (p.players[p.playerID.read() - 1].firePower.read() == 0))
                    {
                        displayControl.write_data((char*)"specify your    \npID & firepower \n(press any key  \nto continue)    \n");
                        wait( keyPressedFlag );
                        keyChannel.read();

                        state = START;
                        break;
                    }
                }

                //TODO: tmp
                hwlib::cout << "playerID : " << p.playerID.read() << "\n";
                hwlib::cout << "firePower : " << p.players[p.playerID.read() - 1].firePower.read() << "\n";
                
                displayControl.clear();

                displayControl.write_data((char*)"wait until you  \nhave receive the\ngame starting   \ntime            \n");

                //TODO:debug
                startSettingUp(32);

                state = IDLE;
                break;
            }
        }
    }
}



void RegisterGameParamControl::startSettingUp(uint16_t gameTime)
{
    startGamePool.write(gameTime);
    startGameFlag.set();
}