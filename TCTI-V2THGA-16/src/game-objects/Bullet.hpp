#include <cmath>
#include <time.h>
#include <stdlib.h>

#ifndef SRC_GAME_OBJECTS_BULLET_HPP_
#define SRC_GAME_OBJECTS_BULLET_HPP_

#include "game-objects/GameObject.hpp"
#include "game-objects/Character.hpp"

class GameObject;
class Character;

/** @file **/

class Bullet: public GameObject
{
public:
	/**
	 * @brief
	 *  Bullet constructor
	 * @details
	 *  creates a bullet with the players location and rotation, rotation is also adjusted with the spread of the weapon firing it.
	 *  This bullet also gets a direction multiplier derived from its rotation.
	 *	For the x multiplier we simply take the cosines of the rotation, for the y multiplier we take the sine of the rotation.
	 *	This gets you a coordinate on the unit circle, multiplying this coordinate with the speed the bullet is supposed to go, gets you the x and y speeds for the bullet.
	 */
	Bullet(Character* apShooter, GameData* apGameData, const char* astrTexturePath = "res/laser.png");

	virtual ~Bullet() = default;

	/**
	 * @brief
	 *  updates the bullets location
	 * @details
	 *  Updates the bullets location using its speed and the time scaling factor.
	 *	It also draws the bullet on the window.
	 */
	virtual void update(void) override;

private:
	Character *pShooter;

	sf::Vector2f v2fSpeed;

	const float fBulletVelocity;
};

#endif /* SRC_GAME_OBJECTS_BULLET_HPP_ */
