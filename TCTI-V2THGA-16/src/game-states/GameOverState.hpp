/*
 * GameOver.hpp
 *
 *  Created on: Jan 12, 2021
 *      Author: sua
 */

#ifndef SRC_GAME_STATES_GAMEOVERSTATE_HPP_
#define SRC_GAME_STATES_GAMEOVERSTATE_HPP_

#include "game-states/GameStateMachine.hpp"

/** @file **/

class GameOverState: public GameState {
public:
	/**
	 * @brief
	 * constructor for GameOverState.
	 * @details
	 * new_score used to display a integer on the
	 * game over screen.
	 * @param apGameData
	 * @param new_score
	 */
	GameOverState(GameData *apGameData, unsigned aiNewScore = 0);

	/**
	 * @brief
	 * destructor for GameOverState
	 */
	virtual ~GameOverState(){};

	/**
	 * @brief
	 * updates GameOverState.
	 * @details
	 * draw background.
	 * draw scoreText.
	 */
	void update(void) override;

	/**
	 * @brief
	 * handles input of user.
	 * @details
	 *	Restart button and main menu button
	 *	can be pressed.
	 */
	void handle_input() override;

private:
	sf::Texture texture;
	sf::Sprite background;

	spriteMI gameLogo = { pGameData, {WINDOW_LENGTH/2,  100}, LOGO_GAME_OVER_TEXTURE };
	spriteMI mainMenuText = { pGameData, {250,  (WINDOW_HEIGHT/2)+100}, TEXT_MAIN_MENU_TEXTURE, TEXT_MAIN_MENU_TEXTURE_HOVER };
	spriteMI restartText = { pGameData, {1050,  (WINDOW_HEIGHT/2)+100}, TEXT_RESTART_TEXTURE, TEXT_RESTART_TEXTURE_HOVER};

	std::array<MenuItem*, 3> pMIarr = {
			&gameLogo,
			&mainMenuText,
			&restartText
	};
};

#endif /* SRC_GAME_STATES_GAMEOVERSTATE_HPP_ */
