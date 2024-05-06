#include "picture.hpp"

picture::picture( sf::Vector2f position, std::string name)
{
    if (!(pic.loadFromFile( name )))
        throw failed_img( name ); 
    texture.loadFromImage(pic); 
    sprite.setTexture(texture); 
    sprite.setPosition( position );
}

void picture::draw( sf::RenderWindow& window){
    window.draw( sprite );
}

sf::Vector2f picture::getPosition(){
    return sprite.getPosition();
}

sf::Vector2f picture::getSize(){
    return sf::Vector2f{ sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
}

void picture::setPos( sf::Vector2f position ){
    sprite.setPosition( position );
}