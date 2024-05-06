/*
 * PauseMenuState.hpp
 *
 *  Created on: Jan 22, 2021
 *      Author: jort
 */

#ifndef SRC_GAME_STATES_PAUSEMENUSTATE_HPP_
#define SRC_GAME_STATES_PAUSEMENUSTATE_HPP_

#include "game-states/GameStateMachine.hpp"

class PauseMenuState : public GameState {
public:
	PauseMenuState(GameData *apGameData, sf::Image *apImg);
	virtual ~PauseMenuState() = default;

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
	sf::Sprite sprite, backgroundSprite;
	sf::Texture texture, backgroundTexture;

	textMI pauseText= { pGameData, "PAUSE", {WINDOW_LENGTH/2, 100}, 60 };
	textMI resumeButton = { pGameData, "resume", {WINDOW_LENGTH/2, 400}, 35 };
	textMI restartButton = { pGameData, "restart level", {WINDOW_LENGTH/2, 450}, 35 };
	textMI exitButton = { pGameData, "exit", {WINDOW_LENGTH/2, 500}, 35 };

	std::array<MenuItem*, 4> pMIarr = {
		&pauseText,
		&resumeButton,
		&restartButton,
		&exitButton
	};
};

#endif /* SRC_GAME_STATES_PAUSEMENUSTATE_HPP_ */
