/*
 * MainMenuState.cpp
 *
 *  Created on: Jan 13, 2021
 *      Author: jort
 */

#include "game-states/MainMenuState.hpp"

#include "game-states/ClientState.hpp"

MainMenuState::MainMenuState(GameData *apGameData) :
	GameState(apGameData)
{
	texture.loadFromFile(MAIN_MENU_BACKGROUND_TEXTURE);
	sprite.setTexture(texture);

	loadingBarRect.setFillColor(sf::Color::Black);
	loadingBarRect.setPosition(520, 460);
}

void MainMenuState::update(void){
	pGameData->pRenderWindow->draw(sprite);
	pGameData->pRenderWindow->draw(loadingBarRect);
	gameLogo.update();


	for(MenuItem* x : pMIarr){
		x->update();
	}

	if(toLevelSelection){
		to_level_selection();
	}
	else if(toMainMenu){
		to_main_menu();
	}
	else if(toLevel){
		to_level();
	}
}

void MainMenuState::handle_input(void){
	if(startButton.button_pressed()){
		nextLevel = new FirstLevelState(pGameData);
		toLevel = true;
	}
	else if(selectLevelButton.button_pressed()){
		toLevelSelection = true;
	}
	else if(multiplayerButton.button_pressed()){
		pGameData->pStateMachine->set_state(new ClientState(pGameData));
	}
	else if(exitButton.button_pressed()){
		pGameData->pRenderWindow->close();
	}
	else if(level1Button.button_pressed()){
		nextLevel = new FirstLevelState(pGameData);
		toLevel = true;
	}
	else if(level2Button.button_pressed()){
		nextLevel = new SecondLevelState(pGameData);
		toLevel = true;
	}
	else if(level3Button.button_pressed()){
		nextLevel = new ThirdLevelState(pGameData);
		toLevel = true;
	}
	else if(playGameButton.button_pressed()){
		nextLevel = new FirstLevelState(pGameData);
		toLevel = true;
	}
	else if(mainMenuButton.button_pressed()){
		toMainMenu = true;
	}
}

void MainMenuState::to_level_selection(){
	for( auto x : pMIarr ){
		if(startButton.get_pos().x <= -WINDOW_LENGTH/2){
			toLevelSelection = false;
		}
		x->move({-40, 0});
		gameLogo.move({0, -1});
	}
}

void MainMenuState::to_main_menu(){
	for( auto x : pMIarr ){
		if(startButton.get_pos().x >= +WINDOW_LENGTH/2){
			toMainMenu = false;
		}
		x->move({+40, 0});
		gameLogo.move({0, +1});
	}
}

void MainMenuState::to_level(){
	if( loadingBarRect.getSize().x > 250 ){
		pGameData->pStateMachine->set_state(nextLevel);
	} else {
		for( auto x : pMIarr){
			if(u8Opacity > 0){
				u8Opacity -= 1;
			} else {
				u8Opacity = 0;
			}
			x->set_opacity(u8Opacity);
			gameLogo.set_opacity(u8Opacity);

			sf::Clock clk;

			// little cooldown so the bar is more fluid
			while(clk.getElapsedTime().asMicroseconds() <= 7000){}
			loadingBarRect.setSize( sf::Vector2f{255.f+((float)u8Opacity*-1.f), 50.f} );

			sf::Color color = sprite.getColor();
			color.a = u8Opacity;
			sprite.setColor(color);
		}
		loading.update();
	}
}



