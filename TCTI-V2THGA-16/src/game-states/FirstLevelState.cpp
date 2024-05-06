/*
 * FirstLevelState.cpp
 *
 *  Created on: 20 Jan 2021
 *      Author: Milo
 */

#include "game-states/FirstLevelState.hpp"

FirstLevelState::FirstLevelState(GameData *apGameData) :
	LevelState( apGameData, sf::Vector2f{550,64}, LEVEL_ONE_BACKGROUND, LEVEL_ONE_BMP, "FirstLevelState" )
{
	arrWeaponInLevel[0] = WeaponStats({686,521}, pGameData, SHOTGUN);
	arrWeaponInLevel[1] = WeaponStats({54,964}, pGameData, MP5);

	enemies.push_back(new Enemy({115,477}, {64,64}, new WeaponStats( { 0, 0 }, pGameData, MP5),	pGameData,
							{
								sf::Vector2f{115,477},
								sf::Vector2f{115,900},
								sf::Vector2f{945,900}
							}
						)
					);
	enemies.push_back(new Enemy({1140,330}, {64,64}, new WeaponStats({ 0, 0 }, pGameData, MP5),	pGameData,
							{
								sf::Vector2f(1140, 330),
								sf::Vector2f(1140, 800),
								sf::Vector2f(1560, 800)
							}
						)
					);
}

GameState* FirstLevelState::reset_state(){
	return new FirstLevelState(pGameData);
}

