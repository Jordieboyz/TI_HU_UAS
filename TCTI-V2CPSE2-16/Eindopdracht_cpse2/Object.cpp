#include "object.hpp"

void Object::move( sf::Vector2f delta){
    setPosition( delta );

    //prevent objects to get out of the window!
    // left
    if( getPosition().x <= HUD_length){
        setPosition( sf::Vector2f{ HUD_length, getPosition().y});
    }
    // up
    if( getPosition().y <= 0.0){
        setPosition( sf::Vector2f{ getPosition().x , 0.f} );
    }
    // 
    if( getPosition().x + getSize().x >= window_length ){
        setPosition( sf::Vector2f{ window_length-getSize().x, getPosition().y } );
    }
    if( getPosition().y + getSize().y >= window_height){
        setPosition( sf::Vector2f{ getPosition().x, window_height-getSize().y });
    }
}
