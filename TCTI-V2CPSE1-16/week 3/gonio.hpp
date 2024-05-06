#ifndef GONIO_HPP
#define GONIO_HPP


class sine_cosine_calc {
public:
    constexpr double pow( double g, int n ){
        double result = 1;
            while( n > 0 ){
                result *= g;
                --n;
            }
        return result;
        }

    constexpr double fac( int n ){
        double result = 1;
        while( n > 0 ){
            result *= n;
            --n;
        }
    return result;
    }

    constexpr double sin( double degrees ){
    return degrees 
        - pow( degrees, 3 ) / fac( 3 ) 
        + pow( degrees, 5 ) / fac( 5 ) 
        - pow( degrees, 7 ) / fac( 7 );
    }

    constexpr double cosin( double degrees ){
    return 1 
        - pow( degrees, 2 ) / fac( 2 ) 
        + pow( degrees, 4 ) / fac( 4 ) 
        - pow( degrees, 6 ) / fac( 6 );
    }

    constexpr double to_degrees(double degree){
        return ( degree / 180 ) * 3.14159265359;
    }

    constexpr double siny( double degree, int radius ){
        return radius * sin(to_degrees(degree)); 
    }

    constexpr double cosinx( double degree, int radius ){
        return radius * cosin(to_degrees(degree));
    }
};

#endif