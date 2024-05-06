#include "hud.hpp"
#include <iostream>

hud::hud(){
    _hud.setSize( sf::Vector2f{ HUD_length, HUD_height } );
    _hud.setPosition( sf::Vector2f{ 0.f, 0.f });
    _hud.setFillColor( sf::Color(25, 25, 25) );
}

void hud::init( std::vector<hudButton*>& hudButtons ){
    _colorStruct colours[]{
        { "blue",   sf::Color::Blue     },
        { "red",    sf::Color::Red      },
        { "yellow", sf::Color::Yellow   },
        { "green",  sf::Color::Green    },
        { "magenta",sf::Color::Magenta  },
        { "cyan",   sf::Color::Cyan     },
        { "white",   sf::Color::White   },
    };

    auto position = sf::Vector2f{ 20, 20 };
    for( auto a : colours ){
        auto s = shape( sf::RectangleShape( colorButtonSize ), a.name );
        s.setPosition( position );
        s.setFillColor( a.color );
        hudButtons.push_back( new hudButton( s ));
        position.y += colorButtonSize.y + 5.0;
    }

    position.y += 10.f;
    for( unsigned int i = 0; i < functionButtons.size(); i++){
        if( i % 2 == 0 && i != 0){ 
            position.y += (shapeButtonSize.y + 10.0); 
            position.x = 20.0;
        }
        functionButtons[i]->setPosition( position );
        functionButtons[i]->setFillColor( sf::Color::White ); 
        hudButtons.insert( hudButtons.begin(), new hudButton( *functionButtons[i] ) );
        position.x += shapeButtonSize.x + 20.0;
    };
}

void hud::draw( sf::RenderWindow& window ){
    window.draw( _hud );
}