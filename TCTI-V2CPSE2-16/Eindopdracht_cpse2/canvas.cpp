#include "canvas.hpp"

canvas::canvas(){
    _HUD.init( hudButtons );
}

void canvas::draw( sf::RenderWindow& window ){
    _HUD.draw( window );
}

bool canvas::checkTouch( Object* Object, sf::RenderWindow& window ){
        if( Object->contains( static_cast<sf::Vector2f>( sf::Mouse::getPosition( window )))){
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                return true;
            }
        }
    return false;
}

std::vector<hudButton*> * canvas::getButtonList(){
    return &hudButtons;
}