/*
 * GameCompletedState.hpp
 *
 *  Created on: Jan 29, 2021
 *      Author: jort
 */

#ifndef SRC_GAME_STATES_GAMECOMPLETEDSTATE_HPP_
#define SRC_GAME_STATES_GAMECOMPLETEDSTATE_HPP_

#include "game-states/GameStateMachine.hpp"

class GameCompletedState : public GameState {
public:
	GameCompletedState(GameData * pGameData);
	virtual ~GameCompletedState() = default;


	/**
	 * @Brief
	 * Draws the objects to the screen
	 */
	void update(void) override;

	/**
	 * @Brief
	 * Handle incoming input
	 */
	void handle_input(void) override;

private:
	sf::Sprite sprite;
	sf::Texture texture;

	textMI congratulationsText	= 	{ pGameData, "CONGRATULATIONS", {WINDOW_LENGTH/2, 250}, 70 };
	textMI completedText		=	{ pGameData, "You completed all the levels!", {WINDOW_LENGTH/2, 325}, 40 };
	textMI mainMenuButton		= 	{ pGameData, "main menu", {320, 500}, 40 };
	textMI playAgainButton		= 	{ pGameData, "play again", {950, 500}, 40 };

	std::array<MenuItem*, 4> pMIarr = {
			&congratulationsText,
			&completedText,
			&mainMenuButton,
			&playAgainButton
	};

};

#endif /* SRC_GAME_STATES_GAMECOMPLETEDSTATE_HPP_ */
