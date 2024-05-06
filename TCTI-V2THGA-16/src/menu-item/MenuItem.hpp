/*
 * MenuItem.hpp
 *
 *  Created on: Jan 13, 2021
 *      Author: jort
 */

#ifndef SRC_MENUITEM_HPP_
#define SRC_MENUITEM_HPP_

#include "Definitions.hpp"
#include "GameData.hpp"

class MenuItem {
public:

	/**
	 * @brief
	 * Constructor for MenuItem
	 */
	MenuItem( GameData * pGameData ) : pGameData( pGameData ){}

	/**
	 * @brief
	 * Destructor for MenuItem
	 */
	virtual ~MenuItem() = default;

	/**
	 * @brief
	 * The update method updates all the
	 * characteristics of the class to the relevant window
	 */
	virtual void update(void) = 0;

	/**
	 * @brief
	 * Move the object given the delta
	 * @details
	 * This function moves the object delta.x on the x-as and delta.y on the y-as
	 * @Param av2fDelta
	 */
	virtual void move(sf::Vector2f av2fDelta) = 0;

	/**
	 * @brief
	 * Directly set the position of the object
	 * @Param av2fPos
	 */
 	virtual void set_pos(sf::Vector2f av2fPos) = 0;

 	/**
 	 * @brief
 	 * This function returns the center of the object
 	 */
	virtual sf::Vector2f get_pos(void) = 0;

	/**
	 * @brief
	 * This function checks if the specified button is pressed
	 * while hovering on the object
	 */
	virtual bool button_pressed(void) = 0;

	/**
	 * @brief
	 * Set the opacity of the object
	 */
	virtual void set_opacity(uint8_t au8Opacity) = 0;

protected:
 	GameData * pGameData;
};

#endif /* SRC_MENUITEM_HPP_ */
