#pragma once

#include "defines.hpp"

//superclass
class Object{
public:
    virtual ~Object(){};
    
    virtual sf::Color getColor() = 0;
    
    virtual void setColor( sf::Color _color ) = 0;

    virtual void draw( sf::RenderWindow& window) = 0;

    virtual sf::Vector2f getPosition() = 0;
    
    virtual void setPosition( sf::Vector2f position ) = 0;

    virtual sf::Vector2f getSize() = 0;

    virtual bool contains( sf::Vector2f mousePosition ) = 0;

    virtual void turnBorder( float thickness = 0, sf::Color color = sf::Color( 0, 0, 0, 0)) = 0;
    
    virtual std::string getName(){ return "ukown Object"; };
    
    virtual void setScale( sf::Vector2f factor ) = 0;

    virtual sf::Vector2f getScale() = 0;

    void move( sf::Vector2f delta );

};