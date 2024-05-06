/*
 * GameCompletedState.cpp
 *
 *  Created on: Jan 29, 2021
 *      Author: jort
 */

#include "game-states/GameCompletedState.hpp"

GameCompletedState::GameCompletedState(GameData *apGameData) :
	GameState(apGameData)
{
	texture.loadFromFile(COMPLETED_BACKGROUND_TEXTURE);
	sprite.setTexture(texture);
}

void GameCompletedState::update(void){
	pGameData->pRenderWindow->draw(sprite);

	for(MenuItem* x : pMIarr){
		x->update();
	}
}

void GameCompletedState::handle_input(void){
	if( mainMenuButton.button_pressed() ){
		pGameData->pStateMachine->set_state( new MainMenuState(pGameData) );
	}
	else if( playAgainButton.button_pressed() ){
		pGameData->pStateMachine->set_state( new FirstLevelState(pGameData) );
	}


}

