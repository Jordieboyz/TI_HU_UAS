/*
 * LevelState.hpp
 *
 *  Created on: 21 Jan 2021
 *      Author: Milo
 */

#ifndef SRC_GAME_STATES_LEVELSTATE_HPP_
#define SRC_GAME_STATES_LEVELSTATE_HPP_

#include <array>
#include <vector>
#include "game-states/GameState.hpp"

//#include "game-objects/GameObject.hpp"/
#include "ObjectGenerator.hpp"
#include "game-objects/Collision.hpp"
#include "game-objects/Enemy.hpp"
#include "game-objects/Weapon.hpp"
#include "game-objects/Player.hpp"
#include "game-objects/Glass.hpp"

/**
 * @file
 *
 * @brief
 * LevelState Class
 * @details
 * This is a general level implementation class, it handles all
 * updates and input, the only thing you have to do in an actual level
 * is initialize the players location and the enemies.
 */
class LevelState: public GameState {
public:
	LevelState(GameData *apGameData, sf::Vector2f v2PlayerLocation,
			const char *sBackgroundFilePath, const char *sWallFilePath, const char * astrName);
	virtual ~LevelState() = default;

	/**
	 * @brief
	 * update
	 * @details
	 * This function handles all the game updates,
	 * it renders all the textures and handles all
	 * the collisions.
	 */
	void update() override;

	/**
	 * @brief
	 * handle_input
	 * @details
	 * This function handles all keyboard input and
	 * updates the time scalar accordingly.
	 */
	void handle_input() override;

private:
	sf::Image take_screenshot();
	sf::View currView = pGameData->pRenderWindow->getView();
	Collision col;

	GameMusic backgroundMusic = { BACKGROUND_MUSIC };
	int enemyCount = 0;
	int gameTime = 60000;
	sf::Texture backgroundTexture;
	sf::Sprite background;

	std::vector<GameObject*> walls;
	float fInitialTimeScaleParamter = 1.0f;

protected:
	std::array<WeaponStats, 5> arrWeaponInLevel = {
				WeaponStats({ -1000, -1000 }, pGameData, SHOTGUN),
				WeaponStats({ -1000, -1000 }, pGameData, M16),
				WeaponStats({ -1000, -1000 }, pGameData, MP5),
				WeaponStats({ -1000, -1000 }, pGameData, M16),
				WeaponStats({ -1000, -1000 }, pGameData, SHOTGUN)
		};
	std::vector<Enemy*> enemies;

};

#endif /* SRC_GAME_STATES_LEVELSTATE_HPP_ */
