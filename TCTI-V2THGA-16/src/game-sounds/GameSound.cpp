/*
 * GameSound.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: sua
 */
#include "GameSound.hpp"


void GameSound::play_sound_file(){
	sound.play();
};

void GameSound::update_speed(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		speed = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		speed = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		speed = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		speed = 1;
	else{
		speed = 0.5;
	}
	sound.setPitch(speed);
}

GameVoiceLine::GameVoiceLine(){
};

void GameVoiceLine::play_voice_line_player(){
	int voiceLine = (rand() % 5 + 1);
	if (voiceLine  > 5 ) {
		voiceLine = 5;
		}
	if(voiceLine ==  1 ) {
		filepath =  VOICE_LINE_1;
		}
	if(voiceLine ==  2 ) {
		filepath =  VOICE_LINE_2;
		}
	if(voiceLine ==  3 ) {
		filepath =  VOICE_LINE_3;
		}
	if(voiceLine ==  4 ) {
			filepath =  VOICE_LINE_4;
			}
	if(voiceLine ==  5 ) {
			filepath =  VOICE_LINE_5;
			}
	soundBuffer.loadFromFile(filepath);
	sound.setBuffer(soundBuffer);
	sound.setVolume(20);
	sound.play();
};

void GameVoiceLine::play_voice_line_enemy(bool state){
	if(alert == true ){
	int voiceLine = (rand() % 5 + 1);
	if (voiceLine  > 5 ) {
		voiceLine = 5;
		}
	if(voiceLine ==  1 ) {
		filepath =  VOICE_LINE_ENEMY_1;
		}
	if(voiceLine ==  2 ) {
		filepath =  VOICE_LINE_ENEMY_2;
		}
	if(voiceLine ==  3 ) {
		filepath =  VOICE_LINE_ENEMY_3;
		}
	if(voiceLine ==  4 ) {
			filepath =  VOICE_LINE_ENEMY_4;
			}
	if(voiceLine ==  5 ) {
			filepath =  VOICE_LINE_ENEMY_5;
			}
	soundBuffer.loadFromFile(filepath);
	sound.setBuffer(soundBuffer);
	sound.setVolume(20);
	sound.play();
	}
	if(state == true){
		alert = false;
	}
};

void GameVoiceLine::update_speed(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		speed = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		speed = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		speed = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		speed = 1;
	else{
		speed = 0.5;
	}
	sound.setPitch(speed);
}



void GameMusic::play_music_file(){
	music.play();
}

void GameMusic::update_speed(){
	music.setLoop(true);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		speed = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		speed = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		speed = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		speed = 1;
	else{
		speed = 0.5;
	}
	music.setPitch(speed);
}
