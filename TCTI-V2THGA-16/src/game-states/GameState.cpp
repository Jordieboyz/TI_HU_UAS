/*
 * GameState.cpp
 *
 *  Created on: 28 Jan 2021
 *      Author: Jort
 */

#ifndef SRC_GAME_STATES_GAMESTATE_CPP_
#define SRC_GAME_STATES_GAMESTATE_CPP_

#include "game-states/GameState.hpp"

GameState::GameState(GameData *apGameData, const char * astrName) :
	pGameData(apGameData),
	strName(astrName)
{
	scoreFont.loadFromFile(TEXT_BUTTON_FONT);
	scoreText.setFont(scoreFont);
	scoreText.setFillColor(sf::Color::Cyan);
	scoreText.setCharacterSize(50);

	pGameData->pParticleManager->reset();
}

std::string GameState::get_name() {
	return strName;
}

GameState* GameState::reset_state() {
	return nullptr;
}

#endif /* SRC_GAME_STATES_GAMESTATE_CPP_ */
