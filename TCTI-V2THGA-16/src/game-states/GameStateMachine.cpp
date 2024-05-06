/*
 * GameStateMachine.cpp
 *
 *  Created on: 11 Jan 2021
 *      Author: lucasw00079
 */

#include "game-states/GameStateMachine.hpp"

void GameStateMachine::set_state(GameState *apGameState) {
	pCurrGameState = apGameState;
}

void GameStateMachine::update(void) {
	sf::Clock timer;
	float acc = 0;

	/* Create copy of current game state as it
	 * can be changed by the state itself. */
	GameState* pTmpState = pCurrGameState;
	GameState* pCheckOLd = pOldState;

	pCurrGameState->handle_input();
	pCurrGameState->update();

	while(acc < (1.0f / FPS_SECOND))
	{
		acc += timer.getElapsedTime().asSeconds();
	}

	/* Wait until frame time has passed */
	/* State changed by state, save old state */
	if(pTmpState != pCurrGameState){
		pOldState = pTmpState;
		/* Check if pCheckOld doesn't point to pCurrState */
		if( pCheckOLd != pCurrGameState){
			delete pCheckOLd;
		}
	}
}

GameState* GameStateMachine::get_old_state() {
	return pOldState;
}
