#pragma once

#include "SFML/Graphics.hpp"
#include "object.hpp"
#include <iostream>

class line : public Object {
private:
    sf::Vector2f begin, end;
    sf::Color color;
    float length;
public:
    line( sf::Vector2f begin, float length, sf::Color color = sf::Color::White):
        begin(begin), end(sf::Vector2f{begin.x+=length, begin.y+length}), color( color), length( length)
    {}


    void draw( sf::RenderWindow& window ){
        sf::Vertex lines[2] =
        {
            sf::Vertex( begin, sf::Color::White ),
            sf::Vertex( end, color ) 
        };

        window.draw(lines, 2, sf::Lines);
    }

    sf::Vector2f getPosition(){
        return begin;
    }

    sf::Vector2f getSize(){
        return sf::Vector2f{length, length};
    }

    void setPos( sf::Vector2f position ){
        begin = position;
        end = sf::Vector2f{position.x+length, position.y+length};
    }

};