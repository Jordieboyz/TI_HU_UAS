/*
 * TextMenuItem.cpp
 *
 *  Created on: Jan 20, 2021
 *      Author: jort
 */

#include "menu-item/TextMenuItem.hpp"

TextMenuItem::TextMenuItem( GameData * apGameData, const char * astrString, sf::Vector2f av2fPos, float afCharSize ) :
	MenuItem(apGameData)
{
	textFont.loadFromFile( TEXT_BUTTON_FONT );

	text.setString(astrString);
	text.setFont(textFont);
	text.setCharacterSize(afCharSize);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(1.0f);
	this->set_pos(av2fPos);
}

bool TextMenuItem::button_pressed(){
	if(text.getGlobalBounds().contains( static_cast<sf::Vector2f>(sf::Mouse::getPosition(*pGameData->pRenderWindow)))){
		text.setOutlineThickness(3.f);
		if(pGameData->key_released){
			pGameData->key_released = false;
			return true;
		}
	} else {
		text.setOutlineThickness( 1.f);
	}
	return false;
}

void TextMenuItem::update(){
	pGameData->pRenderWindow->draw( text );
}

void TextMenuItem::set_pos(sf::Vector2f av2fPos){
	av2fPos.x -= text.getGlobalBounds().width/2.f;
	av2fPos.y -= text.getGlobalBounds().height/2.f;
	text.setPosition(av2fPos);
}

sf::Vector2f TextMenuItem::get_pos(){
	return sf::Vector2f{text.getPosition().x+(text.getGlobalBounds().width/2), text.getPosition().y+(text.getGlobalBounds().height/2) };
}

void TextMenuItem::move( sf::Vector2f av2fDelta ) {
	text.setPosition( text.getPosition() + av2fDelta );
}

void TextMenuItem::set_opacity( uint8_t au8Opacity ){
	sf::Color tmpColor;

	tmpColor = text.getFillColor();
	tmpColor.a = std::min((uint8_t)255, au8Opacity);
	text.setFillColor(tmpColor);

	tmpColor = text.getOutlineColor();
	tmpColor.a = std::min((uint8_t)255, au8Opacity);
	text.setOutlineColor(tmpColor);
}

