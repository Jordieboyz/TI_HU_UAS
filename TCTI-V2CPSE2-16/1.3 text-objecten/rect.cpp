#include "rect.hpp"

rect::rect( sf::Vector2f position, sf::Color color, sf::Vector2f size) :
    rectangle( size )
{
    rectangle.setPosition( position );
    rectangle.setFillColor( color );
}

void rect::draw( sf::RenderWindow& window){
    window.draw( rectangle );
}

sf::Vector2f rect::getPosition(){
    return rectangle.getPosition();
}

sf::Vector2f rect::getSize(){
    return rectangle.getSize();
}

void rect::setPos( sf::Vector2f position ){
    rectangle.setPosition( position );
}