#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>

//super class
#include "object.hpp"

//objects
#include "line.hpp"
#include "rect.hpp"
#include "circle.hpp"
#include "picture.hpp"

//errors
#include "exceptions.hpp"

sf::Vector2f window_size;

std::ifstream & operator>>( std::ifstream & input, sf::Vector2f & rhs ){
    char c;
    if( ! (input >> c)){ throw eof; }
    if( c != '(' ){ throw invalid_pos( c );}
    if( ! (input >> rhs.x)){}
    if(rhs.x > window_size.x-10.0 || rhs.x < 0){throw out_of_bnd(rhs.x); };
    if( ! (input >> c)){}
    if (c != ','){ throw invalid_pos( c ); }
    if( ! (input >> rhs.y)){}
    if(rhs.y > window_size.x-10.0 || rhs.y < 0){throw out_of_bnd(rhs.y); };
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

Object* create_screen_object( std::ifstream& input ){
    sf::Vector2f position, size;
    std::string shape, name;
    float radius, p;
    sf::Color color;

    input >> position >> shape;

    if(shape == "RECT"){
        input >> color >> size;
        return new rect( position, color, size);
    }
    else if(shape == "CIRCLE"){
        input >> color >> radius;
        if(!(radius > 0.0)){ throw invalid_rad(radius); }
        return new circle( position, color, radius );
    }
    else if(shape == "PICTURE"){
        input >> name;
        return new picture( position, name);
    }
    else if(shape == "LINE"){
        input >> color >> p;
        return new line(position, p, color);
    }
    else if(shape == ""){
        throw eof;
    }
    throw uknown_shp( shape );
}


int main() {
    sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
    window_size = static_cast<sf::Vector2f>( window.getSize() );

    std::vector<Object*> screen_objects;
    std::ifstream file("srcs/objecten.txt");
    bool correct_screen_objects_flag = true;

    try {
        for(;;){
            screen_objects.push_back( create_screen_object(file) );
        } 
    } catch( end_of_file& ){}   
    catch( std::exception & problem ){
        correct_screen_objects_flag = false;
        std::cout << problem.what();
    }
    file.close();

    if(correct_screen_objects_flag){
        std::cout << "|*************************************|\n"
                  << "| Alle objecten zijn juist ingeladen! |\n"
                  << "|*************************************|\n";
    }

    sf::Vector2f LastMousePosition, currentMousePosition;
    
    while( window.isOpen()){
        
        window.clear();
        for(auto a : screen_objects){ 
            a->draw( window );
            if(a->contains( static_cast<sf::Vector2f>( sf::Mouse::getPosition( window )))){
                if( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    currentMousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition( window ));
                    a->move( currentMousePosition.x-LastMousePosition.x, currentMousePosition.y-LastMousePosition.y);
                }
                LastMousePosition = static_cast<sf::Vector2f>( sf::Mouse::getPosition( window ));
            }
        }

        window.display();

        sf::Event event;
        while( window.pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                    window.close();
            }
        }
    }

    std::string str;
    std::stringstream ss;
    std::ifstream iStream("srcs/objecten.txt");

    if(correct_screen_objects_flag){
        for( auto a : screen_objects){
            std::getline(iStream, str);
            int pos = str.find( ")" );
            auto substr = str.substr( pos + 1 );
            ss << "(" << a->getPosition().x << ", " << a->getPosition().y << ")" << substr << "\n";
        }

        iStream.close();
        std::ofstream oStream("srcs/objecten.txt");
        oStream << ss.str();
        oStream.close();
    }
}