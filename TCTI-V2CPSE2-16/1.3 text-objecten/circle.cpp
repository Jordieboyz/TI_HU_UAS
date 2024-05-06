#include "circle.hpp"

circle::circle( sf::Vector2f position, sf::Color color, float radius) : 
    circ( radius )
{
    circ.setPosition( position );
    circ.setFillColor( color );
}

void circle::draw( sf::RenderWindow& window){
    window.draw( circ );
}

sf::Vector2f circle::getPosition(){
    return circ.getPosition();
}

sf::Vector2f circle::getSize(){
    return sf::Vector2f{circ.getRadius()*2, circ.getRadius()*2};
}

void circle::setPos( sf::Vector2f position ){
    circ.setPosition( position );
}
