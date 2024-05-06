#ifndef SCREEN_OBJECT_HPP_
#define SCREEN_OBJECT_HPP_

#include "SFML/Graphics.hpp"
extern sf::Vector2f window_size;

// super objecten klasse
class screen_object {
protected:
    sf::Vector2f size;                                  //or radius in case of a circle!
public:
    screen_object( sf::Vector2f size ) :
        size( size )
    {}

    virtual void draw( sf::RenderWindow & window ) const = 0;
    virtual sf::Vector2f getPosition() = 0;

    sf::Vector2f getSize(){
        return size;
    }
};

#endif // SCREEN_OBJECT_HPP_