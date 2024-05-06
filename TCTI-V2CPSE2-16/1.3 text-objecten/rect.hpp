#pragma once

#include "SFML/Graphics.hpp"
#include "object.hpp"

class rect : public Object {
public:
    rect( sf::Vector2f position, sf::Color color, sf::Vector2f size);

    void draw( sf::RenderWindow& window) override;

    sf::Vector2f getPosition() override;

    sf::Vector2f getSize() override;

    void setPos( sf::Vector2f position )override;
private:
    sf::RectangleShape rectangle;
};