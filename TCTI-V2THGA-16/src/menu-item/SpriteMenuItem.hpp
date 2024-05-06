/*
 * SpriteMenuItem.hpp
 *
 *  Created on: Jan 20, 2021
 *      Author: jort
 */

#ifndef SRC_MENU_ITEM_SPRITEMENUITEM_HPP_
#define SRC_MENU_ITEM_SPRITEMENUITEM_HPP_

#include "menu-item/MenuItem.hpp"

class SpriteMenuItem : public MenuItem {
public:
	SpriteMenuItem(GameData *apGameData, sf::Vector2f av2fPos, const char * astrTexturePathNormal, const char * astrTexturePathHover = "");

	virtual ~SpriteMenuItem() = default;

	/**
	 * @brief
	 * Updates the object to a defined window
	 */
	void update(void) override;

	/**
	 * @brief
	 * Moves the object given the @param
	 * @Param av2fDelta
	 */
	void move(sf::Vector2f av2fDelta) override;

 	/**
 	 * @brief
 	 * This function returns the center of the object
 	 */
	sf::Vector2f get_pos(void) override;

 	/**
 	 * @brief
 	 * Set the position based on the center of the object
 	 * @Param av2fPos
 	 */
	void set_pos(sf::Vector2f av2fPos) override;

	/**
	 * @brief
	 * This function checks if the specified button is pressed
	 * while hovering on the object
	 */
	bool button_pressed(void) override;

	/**
	 * @brief
	 * Set the opacity of the object(sprite)
	 * @Param au8Opacity
	 */
	void set_opacity(uint8_t au8Opacity) override;

private:
	sf::Sprite sprSprite;
	sf::Texture tTexture;

	const char * strTPathNormal;
	const char * strTPathHover;
};

using spriteMI = SpriteMenuItem;

#endif /* SRC_MENU_ITEM_SPRITEMENUITEM_HPP_ */
