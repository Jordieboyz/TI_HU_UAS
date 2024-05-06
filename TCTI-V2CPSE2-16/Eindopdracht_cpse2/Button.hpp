#pragma once

#include "object.hpp"

class shape : public sf::Shape {
public:
    shape(){};
    shape( sf::RectangleShape rect, std::string name = "", std::string _texture = "" );
    shape( sf::CircleShape circle,  std::string name  = "", std::string _texture = "" );

    std::string getName();

    sf::Vector2f getSize();

    std::size_t getPointCount() const override;

    sf::Vector2f getPoint( std::size_t index ) const override;
    
private:
    std::string name;
    sf::Vector2f size;
    sf::Texture text;
};

class hudButton : public Object {
public:
    hudButton(){};
    hudButton( shape _shape );

    std::string getName() override;

    sf::Color getColor() override;

    void setColor( sf::Color _color ) override;

    void draw( sf::RenderWindow & window ) override;

    bool contains( sf::Vector2f mousePosition ) override;

    sf::Vector2f getSize() override;

    sf::Vector2f getPosition() override;
    
    void setPosition( sf::Vector2f position ) override;

    void turnBorder( float thickness, sf::Color color ) override;

    void setScale( sf::Vector2f factor ) override;

    sf::Vector2f getScale() override;
private:
    shape shap;
};