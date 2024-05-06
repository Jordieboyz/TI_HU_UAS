/*
 * PauseMenuState.cpp
 *
 *  Created on: Jan 22, 2021
 *      Author: jort
 */

#include "game-states/PauseMenuState.hpp"

PauseMenuState::PauseMenuState(GameData *apGameData, sf::Image *apImg) :
	GameState(apGameData)
{
	texture.loadFromFile(PAUSE_MENU_BACKGROUND_TEXTURE);
	sprite.setTexture(texture);

	backgroundTexture.loadFromImage(*apImg);
	backgroundSprite.setTexture(backgroundTexture);
}

void PauseMenuState::update(void){
	pGameData->pRenderWindow->draw(backgroundSprite);
	pGameData->pRenderWindow->draw(sprite);

	for( MenuItem* x : pMIarr ){
		x->update();
	}
}

void PauseMenuState::handle_input(void){
	if( resumeButton.button_pressed() ){
		pGameData->pStateMachine->set_state( (pGameData->pStateMachine->get_old_state()) );
	}
	else if( restartButton.button_pressed() ){
		pGameData->pStateMachine->set_state( pGameData->pStateMachine->get_old_state()->reset_state() );
	}
	else if( exitButton.button_pressed() ){
		pGameData->pStateMachine->set_state(new MainMenuState(pGameData));
	}
}

