/*
 * SecondLevelState.cpp
 *
 *  Created on: 22 Jan 2021
 *      Author: Milo
 */

#include "game-states/SecondLevelState.hpp"


SecondLevelState::SecondLevelState(struct GameData *apGameData) :
	LevelState( apGameData, sf::Vector2f{550,64}, LEVEL_TWO_BACKGROUND, LEVEL_TWO_BMP, "SecondLevelState" )
{
	arrWeaponInLevel[0] = WeaponStats({1976.12,1013.28}, pGameData, SHOTGUN);
	arrWeaponInLevel[1] = WeaponStats({1810,53.0909}, pGameData, M16);
	arrWeaponInLevel[2] = WeaponStats({2611.12,1178.81}, pGameData, M16);
	arrWeaponInLevel[3] = WeaponStats({4455.82,906.783}, pGameData, MP5);

	enemies.push_back(new Enemy({88,71}, {64,64}, &arrWeaponInLevel[0], pGameData,
						{
						 sf::Vector2f{88,81},
						 sf::Vector2f{88,622},
						 sf::Vector2f{1260,622},
						 sf::Vector2f{1260,868}
						}));
	enemies.push_back(new Enemy({1978,458}, {64,64}, &arrWeaponInLevel[0], pGameData,
						{
						 sf::Vector2f(1978, 458),
						 sf::Vector2f(2217.59, 458.423),
						 sf::Vector2f(2217, 75),
						 sf::Vector2f(3033, 75),
						 sf::Vector2f(3672, 75),
						 sf::Vector2f(2217, 1161)
						}));
	enemies.push_back(new Enemy({2195,570}, {64,64}, &arrWeaponInLevel[0], pGameData,
						{
						 sf::Vector2f(2195.63,570.2),
						 sf::Vector2f(2176.53,1292.78),
						 sf::Vector2f(2199.63,1682.14),
						 sf::Vector2f(2254.19,1682.14),
						 sf::Vector2f(2254.19,1636.58),
						 sf::Vector2f(2181.07,1636.58),
						 sf::Vector2f(2136.07,1709.14)
						}));
	enemies.push_back(new Enemy({1438,1975}, {64,64}, &arrWeaponInLevel[0], pGameData,
						{
						sf::Vector2f(1438.42,1975.72),
						sf::Vector2f(142.742,1734.13),
						sf::Vector2f(895.24,1734.13),
						sf::Vector2f(908.319,1305.11),
						sf::Vector2f(862.756,1305.11),
						sf::Vector2f(904.501,1021.73),
						sf::Vector2f(932.063,1021.73)
						}));
	enemies.push_back(new Enemy({3468,1671}, {64,64}, &arrWeaponInLevel[0], pGameData,
						{
						sf::Vector2f(3468.01,1671.82),
						sf::Vector2f(4576.31,1671.82),
						sf::Vector2f(4576.31,2365.39),
						sf::Vector2f(3540.75,2365.39)
						}));
	enemies.push_back(new Enemy({3468,1671}, {64,64}, &arrWeaponInLevel[0], pGameData,
						{
						sf::Vector2f(4213.47,2176.39),
						sf::Vector2f(4613.21,1275.63),
						sf::Vector2f(4600.99,1125.21),
						sf::Vector2f(3745.43,1125.21)
						}));
}

GameState* SecondLevelState::reset_state(){
	return new SecondLevelState(pGameData);
}


