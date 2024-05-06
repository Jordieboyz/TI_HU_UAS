/*
 * Player.hpp
 *
 *  Created on: 12 Jan 2021
 *      Author: lucasw00079
 */

#ifndef SRC_GAME_OBJECTS_PLAYER_HPP_
#define SRC_GAME_OBJECTS_PLAYER_HPP_

#include "game-objects/Character.hpp"

class Enemy;

/** @file **/

class Player: public Character {
public:
	Player(sf::Vector2f av2fPos, sf::Vector2f av2fSize,
		WeaponStats* apWeapon, GameData* pGameData);

	virtual ~Player();

	void set_last_location( sf::Vector2f av2fNewLocation );
	sf::Vector2f get_last_location();

protected:

	/**
	 * @brief
	 *  Overrides default implementation turns player to cursor location.
	 */
	virtual void update_rotation() override;

	/**
	 * @brief
	 *  Overrides default implementation, switches to game over state.
	 */
	virtual void shot_action() override;

	sf::Vector2f v2fLastLocation;

	friend class Enemy;
};

#endif /* SRC_GAME_OBJECTS_PLAYER_HPP_ */
