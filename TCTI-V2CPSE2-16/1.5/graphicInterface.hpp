#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <iostream>
#include "player.hpp"
#include "TicTacToe.hpp"

using windowBoard = std::array<std::array<sf::RectangleShape, 3>, 3>;

class graphicInterface : public TicTacToe {
private:

    unsigned int window_sizeX = 640;
    unsigned int window_sizeY = 480;
    windowBoard bstate;

    sf::Texture kruis, circle;
    sf::Font font;
    sf::Text text, t;

public:
    graphicInterface( player& player1, player& player2 ) :
       TicTacToe( player1, player2 )  
    {
        newGame();
        if( !kruis.loadFromFile( "res/cross.png" )){ std::cout << "kruis niet ingeladen!\n"; }
        if( !circle.loadFromFile( "res/white_circle.png" )){ std::cout << "circle niet ingeladen!\n"; }
        if( !font.loadFromFile( "res/OpenSans-Bold.ttf" )){ std::cout << "font niet ingeladen!\n"; }

        text.setFont( font );
        text.setFillColor( sf::Color::Magenta );

        t.setFont( font );
        t.setFillColor( sf::Color:: White );
        t.setCharacterSize( 10 );
    }

    void main();

    void newGame(){
        auto position = sf::Vector2f{0, 0};
        auto marges = sf::Vector2f{ (float)window_sizeX/3, (float)window_sizeY/3 };
        for( unsigned int i = 0; i < bstate.size(); i++){
            position.x = 0;            
            for( unsigned int j = 0; j < bstate[i].size(); j++){
                auto rectangle = sf::RectangleShape( marges );
                rectangle.setPosition( position );
                rectangle.setFillColor( sf::Color::Black );
                rectangle.setOutlineColor( sf::Color::White );
                rectangle.setOutlineThickness( 1 );

                bstate[i][j] = rectangle;
                position.x += marges.x;
            }
            position.y += marges.y;
        }        
    }

    void drawBoard( const board& state ) override {
        for(unsigned int i = 0; i < state.size(); i++){
            for(unsigned int j = 0; j < state[i].size(); j++){
                int symbol = state[i][j];
                switch(symbol){
                    case 1 : bstate[i][j].setFillColor( sf::Color::White); bstate[i][j].setTexture( &kruis ); break;
                    case 2 : bstate[i][j].setFillColor( sf::Color::White); bstate[i][j].setTexture( &circle ); break;
                    default: bstate[i][j].setFillColor( sf::Color::Black ); break;
                }
            }
        }
    }
};