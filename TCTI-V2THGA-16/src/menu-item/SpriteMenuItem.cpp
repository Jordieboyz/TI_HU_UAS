/*
 * SpriteMenuItem.cpp
 *
 *  Created on: Jan 20, 2021
 *      Author: jort
 */

#include "menu-item/SpriteMenuItem.hpp"


SpriteMenuItem::SpriteMenuItem(GameData *apGameData, sf::Vector2f av2fPos, const char * astrTPathNormal, const char * astrTPathHover) :
	MenuItem( apGameData ),
	strTPathNormal( astrTPathNormal ),
	strTPathHover( astrTPathHover )
{
	tTexture.loadFromFile(astrTPathNormal);
	sprSprite.setTexture(tTexture);
	set_pos(av2fPos);
}

bool SpriteMenuItem::button_pressed(){
	if(sprSprite.getGlobalBounds().contains( static_cast<sf::Vector2f>(sf::Mouse::getPosition(*pGameData->pRenderWindow)) ) ){
		tTexture.loadFromFile(strTPathHover);
		sprSprite.setTexture(tTexture);
		if(pGameData->key_released){
			pGameData->key_released = false;
			return true;
		}
	} else {
		tTexture.loadFromFile(strTPathNormal);
		sprSprite.setTexture(tTexture);
	}
	return false;
}

void SpriteMenuItem::update(){
	pGameData->pRenderWindow->draw(sprSprite);
}

void SpriteMenuItem::move(sf::Vector2f av2fDelta){
	sprSprite.setPosition( sprSprite.getPosition() + av2fDelta);
}

sf::Vector2f SpriteMenuItem::get_pos(){
	return sf::Vector2f{ sprSprite.getPosition().x+(tTexture.getSize().x), sprSprite.getPosition().y+(tTexture.getSize().y) };
}

void SpriteMenuItem::set_pos(sf::Vector2f av2fPos){
	av2fPos.x -= tTexture.getSize().x/2.f;
	av2fPos.y -= tTexture.getSize().y/2.f;
	sprSprite.setPosition(av2fPos);
}

void SpriteMenuItem::set_opacity(uint8_t au8Opacity){
	sprSprite.setColor(sf::Color(255, 255, 255, std::min((uint8_t)255, au8Opacity)));
}
