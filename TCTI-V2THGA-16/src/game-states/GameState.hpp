/*
 * GameState.hpp
 *
 *  Created on: 11 Jan 2021
 *      Author: lucasw00079
 */

#ifndef SRC_GAME_STATES_GAMESTATE_HPP_
#define SRC_GAME_STATES_GAMESTATE_HPP_

#include "GameData.hpp"
#include "Definitions.hpp"
#include "game-sounds/GameSound.hpp"

#include "menu-item/TextMenuItem.hpp"
#include "menu-item/SpriteMenuItem.hpp"

class GameState {
public:
	GameState(GameData *apGameData, const char * astrName = "UNDEFINED");
	virtual ~GameState() = default;

	/**
	 * @Brief
	 * Return the "name" of a certain state
	 * @Details
	 * This way we can differentiate between states easier
	 */
	std::string get_name();

	/**
	 * @Brief
	 * Returns a new state (from a specific object)
	 */
	virtual GameState* reset_state();

	/**
	 * @Brief
	 * Draws the objects to the screen
	 */
	virtual void update(void) = 0;

	/**
	 * @Brief
	 * Handle incoming input
	 */
	virtual void handle_input(void) = 0;

protected:
	GameData * pGameData;

	std::string strName;

	sf::Clock clock;
	int iGameScore = 0;

	sf::Text scoreText;
	sf::Font scoreFont;

	sf::SoundBuffer soundEffectBuffer;
	sf::Sound soundEffect;
};

#endif /* SRC_GAME_STATES_GAMESTATE_HPP_ */
