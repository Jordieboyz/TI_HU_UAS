/*
 * TextMenuItem.hpp
 *
 *  Created on: Jan 20, 2021
 *      Author: jort
 */

#ifndef SRC_MENU_ITEM_TEXTMENUITEM_HPP_
#define SRC_MENU_ITEM_TEXTMENUITEM_HPP_

#include "menu-item/MenuItem.hpp"

class TextMenuItem : public MenuItem {
public:
	TextMenuItem( GameData * apGameData, const char * astrString, sf::Vector2f av2fPos, float afCharSize = 40 );

	virtual ~TextMenuItem() = default;

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
	void move( sf::Vector2f av2fDelta ) override;

 	/**
 	 * @brief
 	 * This function returns the center of the object
 	 */
	sf::Vector2f get_pos() override;

	/**
 	 * @brief
 	 * Set the position based on the center of the object
 	 * @Param av2fPos
 	 */
	void set_pos( sf::Vector2f strTPathHover) override;

	/**
	 * @brief
	 * This function checks if the specified button is pressed
	 * while hovering on the object
	 */
	bool button_pressed() override;

	/**
	 * @brief
	 * Set the opacity of the object(sprite)
	 * @details
	 * Set the opacity of the text and the outline at the same time
	 * @Param au8Opacity
	 */
	void set_opacity( uint8_t au8Opacity ) override;

private:
	sf::Text text;
	sf::Font textFont;
};

using textMI = TextMenuItem;

#endif /* SRC_MENU_ITEM_TEXTMENUITEM_HPP_ */
