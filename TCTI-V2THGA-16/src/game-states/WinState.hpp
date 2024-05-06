/*
 * WinState.hpp
 *
 *  Created on: Jan 14, 2021
 *      Author: sua
 */

#ifndef SRC_GAME_STATES_WINSTATE_HPP_
#define SRC_GAME_STATES_WINSTATE_HPP_

#include "game-states/GameStateMachine.hpp"
#include <fstream>

/** @file **/

class WinState : public GameState {
public:
	/**
	 * @brief
	 * Constructor for WinState.
	 * @details
	 * new_score used to display a integer on the
	 * game over screen.
	 * @param apGameData
	 * @param new_score
	 */
	WinState(GameData *apGameData, int iGameScore = 0 , int kill_count = 0 , int time = 0, int iGameTimeOflevel = 0);
	/**
	 * @brief Destructor for WinState.E
	 */
	virtual ~WinState(){};

	/**
	 * @brief
	 * updates GameOverState.
	 * @details
	 * draw background.
	 * draw scoreText.
	 */
	void update() override;

	/**
	 * @brief
	 * handles input of user.
	 * @details
	 *	next level button and main menu button
	 *	can be pressed.
	 */
	void handle_input() override;

private:
	int iHighScore = 0;
	uint8_t u8Opacity = 0;
	sf::Text playerName;
	std::string FilepathOfHS;
	sf::Text tHighScore;
	sf::Event event;
	std::string playerInput;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Text killCount;
	textMI mainMenuButton = { pGameData, "main menu", {350, 550}, 55 };
	textMI nextLevelButton = { pGameData, "next level", {850, 550}, 55 };

	std::array<MenuItem*, 2> pMIarr = {
			&mainMenuButton,
			&nextLevelButton
	};
};

#endif /* SRC_GAME_STATES_WINSTATE_HPP_ */
