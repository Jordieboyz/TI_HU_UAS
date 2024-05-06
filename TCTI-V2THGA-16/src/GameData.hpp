/*
 * GameData.hpp
 *
 *  Created on: 11 Jan 2021
 *      Author: lucasw00079
 */

#ifndef SRC_GAMEDATA_HPP_
#define SRC_GAMEDATA_HPP_

#include "game-sounds/GameSound.hpp"
#include <SFML/Graphics.hpp>

#include "MapData.hpp"
#include "particles/ParticleManager.hpp"
class Player;
class GameStateMachine;

struct GameData
{
	GameStateMachine *pStateMachine;
	sf::RenderWindow *pRenderWindow;
	float fTimeScaleFactor;
	Player *pPlayer;
	struct MapData mapData;
	ParticleManager *pParticleManager;
	bool key_released;
	sf::Event evCurrentEvent;
};


#endif /* SRC_GAMEDATA_HPP_ */
