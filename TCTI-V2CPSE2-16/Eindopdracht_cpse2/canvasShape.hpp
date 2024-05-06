#pragma once

#include "object.hpp"

class circle : public Object {
public:
    circle( sf::Color _color, float _radius);
    circle( sf::Vector2f _position, sf::Color _color, float _radius );
    
    void draw( sf::RenderWindow& window) override;

    void setPosition( sf::Vector2f position ) override;

    sf::Vector2f getPosition() override;

    sf::Vector2f getSize() override;

    sf::Color getColor() override;

    void setColor( sf::Color _color ) override;

    bool contains( sf::Vector2f point ) override;
    
    void turnBorder( float thickness, sf::Color color ) override;

    void setScale( sf::Vector2f factor ) override;

    sf::Vector2f getScale() override;

private:
    sf::CircleShape circ;
};


class rect : public Object {
public:
    rect( sf::Color _color, sf::Vector2f _size );
    rect( sf::Vector2f _position, sf::Color _color, sf::Vector2f _size );
    
    void draw( sf::RenderWindow& window) override;

    void setPosition( sf::Vector2f position ) override;

    sf::Vector2f getPosition() override;

    sf::Vector2f getSize() override;

    sf::Color getColor() override;

    void setColor( sf::Color color ) override;

    bool contains( sf::Vector2f point ) override;

    void turnBorder( float thickness, sf::Color color ) override;

    void setScale( sf::Vector2f factor ) override;

    sf::Vector2f getScale() override;

private:
    sf::RectangleShape rectangle;
};