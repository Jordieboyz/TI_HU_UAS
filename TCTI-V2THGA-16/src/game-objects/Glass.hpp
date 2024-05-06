/*
 * Glass.hpp
 *
 *  Created on: 27 Jan 2021
 *      Author: Milo
 */

#ifndef SRC_GAME_OBJECTS_GLASS_HPP_
#define SRC_GAME_OBJECTS_GLASS_HPP_

#include "game-objects/GameObject.hpp"
#include "Definitions.hpp"

class Glass: public GameObject {
public:
	Glass(sf::Vector2f av2fPos, sf::Vector2f av2fSize,
			GameData* pGameData);
	 ~Glass() = default;

	 void collision_action( void ) override;

private:
	 const char* strActiveTexture = GLASS_TEXTURE;
};

#endif /* SRC_GAME_OBJECTS_GLASS_HPP_ */
