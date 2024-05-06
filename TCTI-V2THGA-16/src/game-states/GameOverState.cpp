/*
 * GameOver.cpp
 *
 *  Created on: Jan 12, 2021
 *      Author: sua
 */

#include <iostream>
#include "game-states/GameOverState.hpp"

GameOverState::GameOverState(GameData *apGameData, unsigned new_score) :
	GameState(apGameData)
{
	texture.loadFromFile(GAME_OVER_BACKGROUND_TEXTURE);
	background.setTexture(texture);

	scoreText.setString("KILL COUNT : " + std::to_string(new_score));
	scoreText.setPosition(	WINDOW_LENGTH/2 - (scoreText.getGlobalBounds().width/2),
							WINDOW_HEIGHT/3 - (scoreText.getGlobalBounds().height/2)+30);
}

void GameOverState::update( void ){
	pGameData->pRenderWindow->draw(background);
	pGameData->pRenderWindow->draw(scoreText);

	for(MenuItem* x : pMIarr) {
		x->update();
	}
}

void GameOverState::handle_input() {
	if( mainMenuText.button_pressed()){
		pGameData->pStateMachine->set_state(new MainMenuState(pGameData));
	}
	else if( restartText.button_pressed()){
		pGameData->pStateMachine->set_state(pGameData->pStateMachine->get_old_state()->reset_state());
	}
}



