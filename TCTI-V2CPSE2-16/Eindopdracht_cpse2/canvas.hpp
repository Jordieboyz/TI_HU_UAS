#pragma once


#include "hud.hpp"


class canvas {
public:
    canvas();

    void draw( sf::RenderWindow& window );

    bool checkTouch( Object* Object, sf::RenderWindow& window );

    std::vector<hudButton*> * getButtonList();

private:
    hud _HUD;
    std::vector<hudButton*> hudButtons;
};