/*
 * MainMenu.hpp
 *
 *  Created on: Jan 13, 2021
 *      Author: jort
 */

#ifndef SRC_GAME_STATES_MAINMENUSTATE_HPP_
#define SRC_GAME_STATES_MAINMENUSTATE_HPP_


#include "game-states/GameStateMachine.hpp"


class MainMenuState : public GameState {
public:
	MainMenuState(GameData *apGameData);
	virtual ~MainMenuState() = default;

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
	/**
	 * The next 3 functions  a little transition between states/screens
	 */
	void to_level();
	void to_level_selection(void);
	void to_main_menu(void);

	GameState* nextLevel = nullptr;

	//transitions booleans
	bool toMainMenu = false;
	bool toLevelSelection = false;
	bool toLevel = false;

	sf::Sprite sprite;
	sf::Texture texture;
	sf::RectangleShape loadingBarRect;

	uint8_t u8Opacity = 255;

	// main menu buttons
	spriteMI gameLogo		 = 	{ pGameData, {WINDOW_LENGTH/2, 150}, LOGO_TEXTURE };;
	textMI startButton		 = 	{ pGameData, "start game", {WINDOW_LENGTH/2, 400}, 35 };
	textMI selectLevelButton =	{ pGameData, "select level", {WINDOW_LENGTH/2, 450}, 35 };
	textMI multiplayerButton = 	{ pGameData, "multiplayer", {WINDOW_LENGTH/2, 500}, 35 };
	textMI exitButton 		 = 	{ pGameData, "exit game", {WINDOW_LENGTH/2, 550}, 35 };
	textMI loading 			 = 	{ pGameData, "Loading map...", {WINDOW_LENGTH/2, WINDOW_HEIGHT/2}, 35 };

	// levelSelection buttons
	textMI mainMenuButton 	 = 	{ pGameData, "main menu", {WINDOW_LENGTH+450, 600}, 35 };
	textMI playGameButton	 = 	{ pGameData, "play game", {WINDOW_LENGTH+800, 600}, 35 };
	textMI levelsText 		 = 	{ pGameData, "LEVELS", {WINDOW_LENGTH+630, 155}, 60 };
	spriteMI level1Button  	 = 	{ pGameData, {WINDOW_LENGTH+500, 330}, LEVEL_1_TEXTURE, LEVEL_1_TEXTURE_HOVER };
	spriteMI level2Button	 = 	{ pGameData, {WINDOW_LENGTH+640, 330}, LEVEL_2_TEXTURE, LEVEL_2_TEXTURE_HOVER };
	spriteMI level3Button	 = 	{ pGameData, {WINDOW_LENGTH+780, 330}, LEVEL_3_TEXTURE, LEVEL_3_TEXTURE_HOVER };

	std::array<MenuItem*, 10> pMIarr = {
			// main_menu page
			&startButton,
			&selectLevelButton,
			&multiplayerButton,
			&exitButton,

			// select_level page
			&mainMenuButton,
			&playGameButton,
			&levelsText,
			&level1Button,
			&level2Button,
			&level3Button
	};
};

#endif /* SRC_GAME_STATES_MAINMENUSTATE_HPP_ */
