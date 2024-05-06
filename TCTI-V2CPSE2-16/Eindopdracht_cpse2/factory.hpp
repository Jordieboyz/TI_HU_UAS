#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>

#include "exceptions.hpp"
#include "defines.hpp"
#include "buttonIdentifier.hpp"

std::ostream& operator<<(std::ostream& os, sf::Vector2f rhs){
    return os << "( " << rhs.x << ", " << rhs.y << " )"; 
}


std::ifstream & operator>>( std::ifstream & input, sf::Vector2f & rhs ){
    char c;
    if( ! (input >> c)){ throw eof; }
    if( c != '(' ){ throw invalid_pos( c );}
    if( ! (input >> rhs.x)){}
    if(rhs.x > window_length-10.0 || rhs.x < 0){throw out_of_bnd(rhs.x); };
    if( ! (input >> c)){}
    if (c != ','){ throw invalid_pos( c ); }
    if( ! (input >> rhs.y)){}
    if(rhs.y > window_length-10.0 || rhs.y < 0){throw out_of_bnd(rhs.y); };
    if( ! (input >> c)){}
    if( c != ')' ){ throw invalid_pos( c );}
    return input;
};

std::ifstream & operator>>( std::ifstream & input, sf::Color & rhs ){
    std::string s;
    input >> s;
    const struct { const char * name; sf::Color color; }colors[]{
        { "blue",   sf::Color::Blue     },
        { "red",    sf::Color::Red      },
        { "yellow", sf::Color::Yellow   },
        { "black",  sf::Color::Black    },
        { "white",  sf::Color::White    },
        { "green",  sf::Color::Green    },
        { "magenta",sf::Color::Magenta  },
        { "cyan",   sf::Color::Cyan     },
    };

    for( auto const & color : colors ){
        if( color.name == s){
            rhs = color.color;
            return input;
        }
    }

    if( s == ""){
        throw eof;
    }
    throw uknown_clr( s );
    return input;
};

buttonIdentifier* create_screen_object( std::ifstream& input ){
    sf::Vector2f position, size;
    std::string shape, name;
    float radius;
    sf::Color color;

    input >> position >> shape;

    if(shape == "RECT"){
        input >> color >> size;
        return new buttonIdentifier{ new rect( position, color, size), "RECT", false };
    }
    else if(shape == "CIRCLE"){
        input >> color >> size;
        if(!(size.x > 0.0)){ throw invalid_rad(radius); }
        return new buttonIdentifier{ new circle( position, color, size.x ), "CIRCLE", false };
    }
    else if(shape == ""){
        throw eof;
    }
    throw uknown_shp( shape );
}

void getShapeFile( std::vector<buttonIdentifier*> &canvasObjects, std::ifstream& file ){
    try {
        for(;;){
            canvasObjects.push_back( create_screen_object(file) );
        } 
    } catch( end_of_file& ){}   
    catch( std::exception & problem ){
        std::cout << problem.what();
    }
    file.close();
}