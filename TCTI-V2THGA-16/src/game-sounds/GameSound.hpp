/*
 * GameSounds.hpp
 *
 *  Created on: Jan 18, 2021
 *      Author: sua
 */

#ifndef SRC_GAME_SOUNDS_GAMESOUND_HPP_
#define SRC_GAME_SOUNDS_GAMESOUND_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GameData.hpp"

/**
 * @file
 *
 * @brief
 * class for in game sound.
 * @details
 * used with wav files.
 */
class GameSound {
public:
	/**
	 * @brief
	 * constructor for GameSound.
	 * @details
	 * loads filepath into soundBuffer, after that
	 * sound is set with soundBuffer.
	 * the volume of sound is set to 20 (0-100);
	 * @param filepath
	 */
	GameSound(std::string filepath) : filepath(filepath){
		soundBuffer.loadFromFile(filepath);
		sound.setBuffer(soundBuffer);
		sound.setVolume(20);
	}
	/**
	 * @brief
	 * destructor for GameSound.
	 */
	~GameSound() {};

	/**
	 * @brief
	 * plays sound file given to filepath.
	 */
	void play_sound_file();
	/**
	 * @brief
	 * function to update and set the speed for
	 * voice line.
	 *@details
	 * used to increase the pitch of the sound file when player
	 *moves.
	 */
	void update_speed();

protected:
	std::string filepath;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	float speed = 1;
};
/**
 * @brief
 * class for general voice lines in game.
 * @details
 * used with wav files for player and enemies.
 */
class GameVoiceLine {
public:
	/**
	 * @brief
	 * constructor for class
	 * GameVoiceLine.
	 */
	GameVoiceLine();
	/**
	 * @brief
	 * destructor for GameSound.
	 */
	~GameVoiceLine() {};

	/**
	 * @brief
	 * function to play voice line
	 * for player.
	 *@details
	 * the function choose randomly 1 of the 5
	 * voice lines to play for Player.
	 */
	void play_voice_line_player();
	/**
	 * @brief function to
	 * play voice line for enemy
	 * @details
	 * the function choose randomly 1 of the 5
	 * voice lines to play for enemy.
	 * the functions works only once when the given state
	 * is true.
	 * @param state
	 */
	void play_voice_line_enemy(bool state);
	/**
	 * @brief
	 * function to update and set the speed for
	 * voice line.
	 *@details
	 * used to increase the pitch of the sound file when player
	 *moves.
	 */
	void update_speed();

protected:
	std::string filepath;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	bool alert = true;
	float speed = 1;
};

/**
 * @brief
 * class for in game music.
 * @details
 * used with wav files.
 */
class GameMusic {
public:
	/**
	 * @brief
	 * constructor for class
	 *@details
	 * GameMusic.
	 * opens filepath into music and sets
	 * volume to 10 (0-100);
	 * @param filepath
	 */
	GameMusic(std::string filepath) : filepath(filepath) {
		music.openFromFile(filepath);
		music.setVolume(10);
	}
	/**
	 * @brief
	 * destructor for GameMusic.
	 */
	~GameMusic() {};

	/**
	 * @brief
	 * function plays music file from filepath.
	 */
	void play_music_file();
	/**
	 * @brief
	 * function to update and set the speed for
	 * music.
	 *@details
	 * used to increase the pitch of the music file when player
	 * moves.
	 */
	void update_speed();

protected:
		std::string filepath;
		sf::Music music;
		float speed = 1;
};






#endif /* SRC_GAME_SOUNDS_GAMESOUND_HPP_ */
