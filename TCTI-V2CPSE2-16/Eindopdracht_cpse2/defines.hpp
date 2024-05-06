#include <vector>
#include "SFML/Graphics.hpp"

#define window_length    640
#define window_height    640

#define grid_length      window_length-HUD_length
#define grid_height      window_height

#define HUD_length      150 
#define HUD_height      window_height

#define colorButtonSize sf::Vector2f{ 100, 30 }
#define shapeButtonSize sf::Vector2f{ 40, 40 }

#define _colorStruct    struct{ const char * name; sf::Color color;}

    