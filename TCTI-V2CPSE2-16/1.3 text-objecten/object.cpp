#include "object.hpp"

bool Object::contains( sf::Vector2f mousePosition ){
        if( mousePosition.x > getPosition().x &&
            mousePosition.x <= getPosition().x + getSize().x &&
            mousePosition.y > getPosition().y &&
            mousePosition.y <= getPosition().y + getSize().y
        ){ 
            return true;
        }
        return false;
    }

void Object::move( sf::Vector2f delta ){
    
    setPos( getPosition() + delta );


    //prevent objects to get out of the window!
    if( getPosition().x <= 0.0){
        setPos( sf::Vector2f{ 0.f, getPosition().y});
    }
    if( getPosition().y <= 0.0){
        setPos( sf::Vector2f{ getPosition().x , 0.f} );
    }
    if( getPosition().x + getSize().x >= window_size.x ){
        setPos( sf::Vector2f{ window_size.x-getSize().x, getPosition().y } );
    }
    if( getPosition().y + getSize().y >= window_size.y){
        setPos( sf::Vector2f{ getPosition().x, window_size.y-getSize().y });
    }



}

void Object::move( float x, float y ){
    move( sf::Vector2f{x, y} );
}