/*
 * WinState.cpp
 *
 *  Created on: Jan 14, 2021
 *      Author: sua
 */

#include "game-states/WinState.hpp"

WinState::WinState(GameData* apGameData, int iGameScore, int kill_count , int time, int iGameTimeOflevel) :
	GameState(apGameData)
{
	if(iGameTimeOflevel == 6000){
		FilepathOfHS = "res/HighScore.txt";
	}
	if(iGameTimeOflevel == 10000){
		FilepathOfHS = "res/HighScore2.txt";
	}
	if(iGameTimeOflevel == 3000){
		FilepathOfHS = "res/HighScore3.txt";
	}
	std::ifstream sHighScore;
	sHighScore.open(FilepathOfHS);

	if( sHighScore.is_open()){
		while( !sHighScore.eof()){
			sHighScore >> iHighScore;
		}
	}

	sHighScore.close();

	std::ofstream writeHighScore("res/HighScore.txt");
	if(writeHighScore.is_open()){
		if ( iGameScore > iHighScore) {
			iHighScore = iGameScore;
		}

		writeHighScore << iHighScore;
	}

	writeHighScore.close();

	killCount.setFont(scoreFont);
	killCount.setFillColor(sf::Color::Cyan);
	killCount.setCharacterSize(20);

	tHighScore.setFont(scoreFont);
	tHighScore.setFillColor(sf::Color::Cyan);
	tHighScore.setCharacterSize(20);

	texture.loadFromFile(WIN_MENU_BAKCGROUND_TEXTURE);
	sprite.setTexture(texture);

	scoreText.setString("END SCORE :\n      "+std::to_string(iGameScore));
	scoreText.setPosition(	WINDOW_LENGTH/2 - (scoreText.getGlobalBounds().width/2),400);
	tHighScore.setString("HIGH SCORE : "+std::to_string(iHighScore));
	tHighScore.setPosition(	WINDOW_LENGTH/2 - (scoreText.getGlobalBounds().width/2)+100,40);
	killCount.setString("KILL COUNT : " + std::to_string(kill_count) +" X 100" + "\n" +
						"TIME :             " + std::to_string(time));
	killCount.setPosition(	WINDOW_LENGTH/2 - (killCount.getGlobalBounds().width/2),
							WINDOW_HEIGHT/2 - (scoreText.getGlobalBounds().height/2) + 30);

}

void WinState::update(void) {
	pGameData->pRenderWindow->draw(sprite);
	pGameData->pRenderWindow->draw(scoreText);
	pGameData->pRenderWindow->draw(tHighScore);
	pGameData->pRenderWindow->draw(killCount);
	for( MenuItem* button : pMIarr ){
		button->update();
		button->set_opacity(u8Opacity);
	}

	if(u8Opacity < 255){
		u8Opacity += 3;
	} else {
		u8Opacity = 255;
	}
}

void WinState::handle_input() {
	if(nextLevelButton.button_pressed()){
		std::string strName = pGameData->pStateMachine->get_old_state()->get_name();
		if( strName == "FirstLevelState"){
			pGameData->pStateMachine->set_state( new SecondLevelState( pGameData ));
		}
		if( strName == "SecondLevelState"){
			pGameData->pStateMachine->set_state( new ThirdLevelState( pGameData ));
		}
		if( strName == "ThirdLevelState"){
			pGameData->pStateMachine->set_state( new GameCompletedState( pGameData ));
		}
	}
	else if(mainMenuButton.button_pressed()){
		pGameData->pStateMachine->set_state( new MainMenuState( pGameData ));
	};
}


