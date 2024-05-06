/*
 * ThirdLevelState.cpp
 *
 *  Created on: 25 Jan 2021
 *      Author: Milo
 */

#include "game-states/ThirdLevelState.hpp"

ThirdLevelState::ThirdLevelState(struct GameData *apGameData) :
	LevelState( apGameData, sf::Vector2f{550,64}, LEVEL_THREE_BACKGROUND, LEVEL_THREE_BMP, "ThirdLevelState" )
{

	pGameData->pPlayer->set_pos(sf::Vector2f(376.985,925.689));
	arrWeaponInLevel[2] = WeaponStats({646.459,691.385}, pGameData, SHOTGUN);
	arrWeaponInLevel[3] = WeaponStats({528.254,143.302}, pGameData, M16);
	arrWeaponInLevel[4] = WeaponStats({1764.02,72.4089}, pGameData, MP5);

	enemies.push_back(new Enemy(sf::Vector2f(1300.24,844.601), {64,64}, &arrWeaponInLevel[0], pGameData,
						{
							sf::Vector2f(1300.24,844.601),
							sf::Vector2f(1729.89,817.689),
							sf::Vector2f(1680.51,552.027)
						}));
	enemies.push_back(new Enemy(sf::Vector2f(315.891,244.747), {64,64}, &arrWeaponInLevel[1], pGameData,
						{
							sf::Vector2f(315.891,244.747),
							sf::Vector2f(623.599,556.34),
							sf::Vector2f(1248.03,556.34),
							sf::Vector2f(1248.03,565.903),
							sf::Vector2f(876.323,566.356),
							sf::Vector2f(876.323,593.919),
							sf::Vector2f(848.515,575.356)
						}));
	enemies.push_back(new Enemy(sf::Vector2f(885.077,58.6546), {64,64}, &arrWeaponInLevel[0], pGameData,
						{
							sf::Vector2f(885.077,58.6546),
							sf::Vector2f(885.077,314.083),
							sf::Vector2f(1248.68,314.083),
							sf::Vector2f(1248.68,350.646),
							sf::Vector2f(1248.68,305.083),
							sf::Vector2f(1546.24,305.083)
						}));
}

GameState* ThirdLevelState::reset_state(){
	return new ThirdLevelState(pGameData);
}

