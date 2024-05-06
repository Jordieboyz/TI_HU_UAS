#pragma once

#include "SFML/Graphics.hpp"
#include "exceptions.hpp"

extern sf::Vector2f window_size;

//superclass
class Object {
public:
    virtual void draw( sf::RenderWindow& window) = 0;
    virtual sf::Vector2f getPosition() = 0;
    virtual sf::Vector2f getSize() = 0;
    virtual void setPos( sf::Vector2f position ) = 0;

    bool contains( sf::Vector2f mousePosition );

    void move( sf::Vector2f delta );

    void move( float x, float y );
};