#pragma once

#include "Button.hpp"
#include "defines.hpp"

class hud {
public:
    hud();
    
    void init( std::vector<hudButton*>& hudButtons );

    void draw( sf::RenderWindow& window );
    
private:
    sf::RectangleShape _hud;

    shape circle =       shape( sf::CircleShape( shapeButtonSize.y/2 ), "circleButton" );
    shape rectangle =    shape( sf::RectangleShape( shapeButtonSize ), "rectButton" );
    shape deleteButton = shape( sf::RectangleShape( shapeButtonSize ), "deleteButton", "res/delete.png" );
    shape selectButton = shape( sf::RectangleShape( shapeButtonSize ), "selectButton", "res/select.png" );
    shape moveButton =   shape( sf::RectangleShape( shapeButtonSize ), "moveButton", "res/move.png" );
    shape saveButton =   shape( sf::RectangleShape( shapeButtonSize ), "saveButton", "res/save.png" );
    shape borderButton = shape( sf::RectangleShape( shapeButtonSize ), "borderButton", "res/square.png" );
    shape plusButton =   shape( sf::RectangleShape( shapeButtonSize ), "plusButton", "res/plus.png" );
    shape minusButton =  shape( sf::RectangleShape( shapeButtonSize ), "minusButton", "res/minus.png" );
    shape openButton =   shape( sf::RectangleShape( shapeButtonSize ), "openButton", "res/open.png" );

    std::vector<shape*> functionButtons = {
        &circle,
        &rectangle,
        &deleteButton,
        &selectButton,
        &moveButton,
        &borderButton,
        &plusButton,
        &minusButton,
        &saveButton,
        &openButton
    };
};