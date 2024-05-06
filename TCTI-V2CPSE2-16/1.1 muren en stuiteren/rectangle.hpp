#ifndef WALL_HPP_
#define WALL_HPP_

#include <SFML/Graphics.hpp>
#include "screen_objects.hpp"

class rectangle : public screen_object {
public:
    rectangle( sf::Color color, sf::Vector2f position, sf::Vector2f size);

    void draw( sf::RenderWindow & window ) const override;

    void move( sf::Vector2f delta );

    bool collisionX( screen_object& other );
    
    bool collisionY( screen_object& other );

    sf::Vector2f getPosition();

private:
    sf::RectangleShape rect;
};

#endif