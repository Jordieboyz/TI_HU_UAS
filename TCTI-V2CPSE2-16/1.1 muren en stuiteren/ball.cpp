#include "ball.hpp"

ball::ball( sf::Color color, sf::Vector2f position, float radius, float speed) :
    screen_object( sf::Vector2f{ radius, radius } ),
    circle( radius ), direction( sf::Vector2f{ -speed, speed } )
{
    circle.setFillColor( color );
    circle.setPosition( position );
}

void ball::draw( sf::RenderWindow & window ) const {
    window.draw( circle );
}

void ball::move( sf::Vector2f delta ){
    direction.x *= delta.x;
    direction.y *= delta.y;

    circle.setPosition(circle.getPosition() + direction);
}

sf::Vector2f ball::getPosition(){
    return circle.getPosition();
}
