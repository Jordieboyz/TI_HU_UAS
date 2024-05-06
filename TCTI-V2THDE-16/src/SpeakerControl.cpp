#include "../include/SpeakerControl.hpp"

void SpeakerControl::main(){
    while(true)
    {
        switch ( state )
        {
            case PLAY :
            {   
                wait( playFlag );
                {
                    int size = 0; 
                    nameInt.write(0);
                    while ( name.read()[ size ] != '\0')
                    { 
                        nameInt.write((nameInt.read() + name.read()[ size ]));
                        size++;
                    }
                    state = SOUND;
                    break;
                }
                break;
            }
            case SOUND :
            {
                sound s;
                if( nameInt.read() == 557 )
                {
                    s.shoot( sp );
                    state = PLAY;
                    break;        
                }
                else if( nameInt.read() == 325 )
                {
                    s.hit( sp ); 
                    state = PLAY;
                    break; 
                }
                else {
                    state = PLAY;
                    break;
                }
            }
        }
    }
}

void SpeakerControl::play( const char * n)
{
    name.write( n );
    playFlag.set();
}