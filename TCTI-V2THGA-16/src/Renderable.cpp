/*
 * Renderable.cpp
 *
 *  Created on: Jan 11, 2021
 *      Author: jort
 */

#include "Renderable.hpp"

Renderable::Renderable( sf::Vector2f av2fPosition, sf::Vector2f av2fSize, const char * astrTexturePath,
		                GameData * apData, const bool abTileable ) :
	v2fPos( av2fPosition ),
	v2fSize( av2fSize ),
	pData( apData )
{
	texture.loadFromFile(astrTexturePath);
	texture.setRepeated(true);

	sprite.setTexture(texture);
	sprite.setPosition(av2fPosition);

	if(abTileable){
		sprite.setTextureRect(sf::IntRect(sf::Vector2i(av2fPosition), sf::Vector2i(av2fSize)));
	} else {
		v2fscale = sf::Vector2f((av2fSize.x / texture.getSize().x), (av2fSize.y / texture.getSize().y));
		sprite.setScale( v2fscale );
	}
}


void Renderable::update( void ) {
	if(pData->pRenderWindow != nullptr)
		pData->pRenderWindow->draw( sprite );
}

void Renderable::move(sf::Vector2f av2fPos) {
	v2fPos = av2fPos;
	sprite.setPosition(v2fPos);
}

void Renderable::set_size(sf::Vector2f av2fSize) {
	v2fSize = av2fSize;
}

sf::Vector2f Renderable::get_size(void){
	return v2fSize;
}

void Renderable::set_pos(sf::Vector2f av2fPos) {
	v2fPos = av2fPos;
}

sf::Vector2f Renderable::get_pos(void) {
	return v2fPos;
}
