#include "rectangle.hpp"


rectangle::rectangle( sf::Color color, sf::Vector2f position, sf::Vector2f size) :
    screen_object( size ),
    rect( size )
{
    rect.setPosition( position );
    rect.setFillColor( color );
}

void rectangle::draw( sf::RenderWindow & window ) const {
    window.draw( rect );
}

void rectangle::move( sf::Vector2f delta ){

    rect.setPosition( rect.getPosition() + delta );

    //prevent the rect to get out of the window
    if( rect.getPosition().x <= 0.0){ 
        rect.setPosition( 0.0, rect.getPosition().y); 
    }
    if( rect.getPosition().y <= 0.0){ 
        rect.setPosition( rect.getPosition().x , 0.0); 
    }
    if( rect.getPosition().x + rect.getSize().x >= window_size.x ){
        rect.setPosition( window_size.x-rect.getGlobalBounds().width, rect.getPosition().y);
    }
    if( rect.getPosition().y + rect.getSize().y >= window_size.y){
        rect.setPosition( rect.getPosition().x, window_size.y-rect.getGlobalBounds().height);
    }
}

bool rectangle::collisionX( screen_object& other ){
    if( &other != this){
        if( rect.getGlobalBounds().contains( other.getPosition().x + (other.getSize().x*2.0), (other.getPosition().y + other.getSize().x) ) || 
			rect.getGlobalBounds().contains( other.getPosition().x, (other.getPosition().y+(other.getSize().x)) ) )
        {
            return true;
        }
    }
    return false;
}

bool rectangle::collisionY( screen_object& other ){
    if( &other != this){ 
        if( rect.getGlobalBounds().contains( (other.getPosition().x + other.getSize().x), other.getPosition().y ) || 
			rect.getGlobalBounds().contains( (other.getPosition().x + other.getSize().x), (other.getPosition().y+(other.getSize().x*2.0))) )
        {
            return true;
        }
    }
    return false;
}

sf::Vector2f rectangle::getPosition(){
    return rect.getPosition();
}
