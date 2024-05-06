#ifndef _SOUND_HPP
#define _SOUND_HPP


struct sound {
    
    void play( hwlib::pin_out& sp ){
        auto t = hwlib::now_us();    
        auto end = t + d;
        while( end > hwlib::now_us() ){
            auto p = 500'000 / f;
            f = f * fd / 1000;
            sp.write( 1 );
            sp.flush();
            hwlib::wait_us( p );
            sp.write( 0 );
            sp.flush();
            hwlib::wait_us( p );
        }
    }

    const char * name;
    int f, d, fd; 
    
public:
    sound() 
    {
        name = "";
        f = 0;
        d = 0;
        fd = 1000; 
    }

    void shoot( hwlib::pin_out& sp ){
        name = "shoot"; f = 20'000; d = 200'000; fd = 990;
        play( sp );
    }

    void hit( hwlib::pin_out& sp ){
        name = "hit"; f = 1'000; d = 50'000;
        for( int i = 0; i < 3; i++ ){
            play( sp );
            hwlib::wait_us( 20'000 );
        }
    }
};




#endif