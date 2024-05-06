#pragma once

#include "SFML/Graphics.hpp"
#include "object.hpp"

class picture : public Object {
public:
    picture( sf::Vector2f position, std::string name);

    void draw( sf::RenderWindow& window) override;

    sf::Vector2f getPosition() override;

    sf::Vector2f getSize() override;

    void setPos( sf::Vector2f position ) override;
private:
    sf::Image pic;
    sf::Texture texture;
    sf::Sprite sprite;
};