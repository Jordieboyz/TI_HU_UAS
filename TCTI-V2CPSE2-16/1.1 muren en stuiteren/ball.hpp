#ifndef _BALL_HPP
#define _BALL_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "screen_objects.hpp"


class ball : public screen_object {
public:
	ball( sf::Color color, sf::Vector2f position, float radius = 20.0, float speed = 1);

	void draw( sf::RenderWindow & window ) const override;

	void move( sf::Vector2f delta );

	sf::Vector2f getPosition();

private:
	sf::CircleShape circle;
	sf::Vector2f direction;
};

#endif
