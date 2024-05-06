#ifndef _SPEAKER_CONTROL
#define _SPEAKER_CONTROL

#include "hwlib.hpp"
#include "rtos.hpp"

#include "../include/headers/sound.hpp"

/**
 * @brief
 *  The Button Class
 * @details
 *  This class is a virtual Speaker. It represents a fysical speaker in the circuit.
 *  Our program just needed 2 simple sound, shooting and getting hit. SO that is pretty much the only thing which is implemented.
 *  Nothing really special over here
 */
class SpeakerControl : public rtos::task<> {
public:
    /**
     * @brief
     *  The "SpeakerControl" constructor
     * @details
     *  The constructor of this class just needs a virtual arduino pin.
     *  @param sp       A virtual arduino pin
     */
    SpeakerControl( hwlib::pin_out& sp) :
        task( 4, "speakerControl"),
        sp( sp ),
        playFlag( this, "playFlag"),
        name( "namePool" ),
        nameInt( "nameIntPool" )
    {
        nameInt.write(0);
    }

    /**
	 * @brief
	 *  Set the flag to start playing a sound.
     *  @param name         A string representing which sound you want to play. {"shoot", "hit"}
	 */
    void play( const char * name );

private:
    enum state_t : int { PLAY, SOUND };
    
    state_t state = PLAY;

    hwlib::pin_out& sp;
    
    rtos::flag playFlag;
    
    rtos::pool<const char *> name;
    rtos::pool<int> nameInt;

    void main() override;
};


#endif // _SPEAKER_CONTROL