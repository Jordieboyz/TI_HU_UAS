#pragma once

#include "SFML/Graphics.hpp"
#include "object.hpp"

class circle : public Object {
public:
    circle( sf::Vector2f position, sf::Color color, float radius = 30);
    
    void draw( sf::RenderWindow& window) override;

    void setPos( sf::Vector2f position ) override;

    sf::Vector2f getPosition() override;

    sf::Vector2f getSize() override;
    
private:
    sf::CircleShape circ;
};