/*
 * Glass.cpp
 *
 *  Created on: 27 Jan 2021
 *      Author: Milo
 */

#include "game-objects/Glass.hpp"

Glass::Glass( sf::Vector2f av2fPos, sf::Vector2f av2fSize,
		GameData* pGameData )
 : GameObject(av2fPos, av2fSize, GLASS_TEXTURE, pGameData)

{
	if((av2fPos.x - av2fSize.x) > (av2fPos.y - av2fSize.y))
		strActiveTexture = GLASS_TEXTURE_ROTATED;

	v2fscale = sf::Vector2f((av2fSize.x / texture.getSize().x), (av2fSize.y / texture.getSize().y));
	sprite.setScale( v2fscale );
}

void Glass::collision_action(void) {
	bIsCollidable = false;
	if(strActiveTexture == "GLASS_TEXTURE_ROTATED"){
		texture.loadFromFile(GLASS_TEXTURE_BROKEN_ROTATED);
	} else {
		texture.loadFromFile(GLASS_TEXTURE_BROKEN);
	}
	sprite.setTexture(texture);
}

