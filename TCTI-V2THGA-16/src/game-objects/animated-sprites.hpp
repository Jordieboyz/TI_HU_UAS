/*
 * animated-sprites.hpp
 *
 *  Created on: 12 Jan 2021
 *      Author: lucasw00079
 */

#ifndef SRC_GAME_OBJECTS_ANIMATED_SPRITES_HPP_
#define SRC_GAME_OBJECTS_ANIMATED_SPRITES_HPP_

#include "Definitions.hpp"

#include <SFML/Graphics.hpp>

enum ANIMATION_TYPE
{
	ANIMATION_TYPE_IDLE,
	ANIMATION_TYPE_MOVING,
	ANIMATION_TYPE_SHOOTING,
	ANIMATION_TYPE_DEAD,
	ANIMATION_NUM_TYPES
};

struct AnimationData{
	unsigned uNumImagesX;
	unsigned uNumImagesY;
	unsigned uNumImages;

	float 	 fDuration;
	const char *strImagePath;
};

struct ParticleData{
	struct AnimationData *pAnim;
	sf::Vector2f v2fPos;
	sf::Vector2f v2fSize;
	float fRotation;
	bool  bPersistent;
};

extern AnimationData PLAYER_ANIMATIONS_M16[ANIMATION_NUM_TYPES];
extern AnimationData PLAYER_ANIMATIONS_MP5[ANIMATION_NUM_TYPES];
extern AnimationData PLAYER_ANIMATIONS_SHOTGUN[ANIMATION_NUM_TYPES];

extern AnimationData ANIMATION_EXPLOSION;
extern AnimationData ANIMATION_MUZZLE_FLASH;
extern AnimationData ANIMATION_BULLET_IMPACT;
extern AnimationData ANIMATION_POINTS;

#endif /* SRC_GAME_OBJECTS_ANIMATED_SPRITES_HPP_ */
