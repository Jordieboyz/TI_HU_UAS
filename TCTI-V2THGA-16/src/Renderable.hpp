/*
 * Renderable.hpp
 *
 *  Created on: Jan 11, 2021
 *      Author: jort
 */



#ifndef SRC_RENDERABLE_HPP_
#define SRC_RENDERABLE_HPP_

#include <SFML/Graphics.hpp>
#include "GameData.hpp"

/** @file **/

class Renderable {
public:
	Renderable( sf::Vector2f av2fPosition, sf::Vector2f av2fSize, const char * astrTexturePath,
			    GameData * apData, const bool abTileable = false );

	virtual ~Renderable() = default;

	/**
	 * @brief
	 *  Updates internal state of class and draws sprite to window.
	 */
	virtual void update(void);

	/**
	 * @brief
	 *  Moves object to new (absolute)position, changes visible after call to
	 *  update.
	 * @details
	 *  If a object needs to update other internals this function
	 *  should be used. If the position should be updated without any
	 *  side effects set_pos should be used.
	 * @param av2fPos New (absolute)position
	 */
	virtual void move( sf::Vector2f av2fPos );

	/**
	 * @brief
	 * 	Setter for the size, also visible after next call to update.
	 * @param av2fSize new size
	 */
	virtual void set_size( sf::Vector2f av2fSize );

	virtual sf::Vector2f get_size(void);

	/**
	 * @brief
	 *  Updates position without side effects.
	 * @param av2fPos
	 */
	virtual void set_pos( sf::Vector2f av2fPos );

	virtual sf::Vector2f get_pos(void);

protected:
	sf::Vector2f v2fPos, v2fSize, v2fscale;
	sf::Texture texture;
	sf::Sprite sprite;
	GameData * pData;
};

#endif /* SRC_RENDERABLE_HPP_ */
