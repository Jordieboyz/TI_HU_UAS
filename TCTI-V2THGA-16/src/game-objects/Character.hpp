/*
 * Character.hpp
 *
 *  Created on: 11 Jan 2021
 *      Author: lucasw00079
 */
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

#ifndef SRC_GAME_OBJECTS_CHARACTER_HPP_
#define SRC_GAME_OBJECTS_CHARACTER_HPP_


#include "game-objects/Bullet.hpp"
#include "game-objects/GameObject.hpp"
#include "animated-sprites.hpp"
#include "game-objects/Weapon.hpp"


class Bullet;
class Weapon;

/** @file **/

class Character: public GameObject {
public:
	Character(sf::Vector2f av2fPos, sf::Vector2f av2fSize,
		WeaponStats* apWeapon, GameData* pGameData);

	virtual ~Character();

	/**
	 * @brief
	 *  Moves character to new position.
	 * @details
	 *  It also sets a flag indicating that the character is
	 *  currently moving, the flag is used to determine the right animation.
	 * @param av2fPos
	 */
	virtual void move(sf::Vector2f av2fPos) override;

	/**
	 * @brief
	 *  update overrides update from GameObject
	 * @details
	 *  Overrides the definition provided by GameData as it doesn't provide
	 *  any mechanism for animations or the rotation of the object.
	 */
	virtual void update() override;

	/**
	 * @brief
	 *  Shoots a bullet
	 * @details
	 *  if character can shoot, make the amount of bullets the weapon is supposed to shoot.
	 *	Store pointers of these bullets in vBulletsFired.
	 * @return
	 *  True if character actually shot, false if in cooldown period.
	 */
	virtual bool shoot(void);

	/**
	 * @brief
	 *  getter for fRotation
	 * @return
	 *  current rotation
	 */
	virtual float get_rotation(void);

	virtual std::vector<Bullet*>* get_fired_bullets();

	virtual Weapon* get_Weapon(void);
	virtual void set_Weapon(WeaponStats* aWeapon);
	virtual const WeaponStats* drop_weapon();

	/**
	 * @brief
	 *  Shot handler, called by bullet on impact.
	 */
	virtual void shot() override;

	bool get_bDead();

protected:

	/**
	 * @brief
	 *  Updates the texture to match the state of the character EG: moving,
	 *  shooting.
	 */
	virtual void update_texture(void);

	/**
	 * @brief
	 *  Updates rotation, called by update
	 * @details
	 *  This definition is empty, it is defined to keep us from having to
	 *  redefine update, a rather lengthy function, in subclasses.
	 */
	virtual void update_rotation(void);

	/**
	 * @brief
	 *  Called by shot
	 * @details
	 *  Another empty definition that keeps us from having to redefine
	 *  the shot function.
	 */
	virtual void shot_action(void);

	float fAcc = 0.0f;

	bool bIsMoving = false;
	bool bIsShooting = false;
	bool bDead = false;
	unsigned uCurrAnimation = ANIMATION_TYPE_IDLE;
	sf::Clock timer;
	const AnimationData *parrAnimations;
	GameSound shootSound = {SHOOT_SOUND_EFFECT};
	GameVoiceLine voice;

	const WeaponStats* pCurrentWeapon;
	std::vector<Bullet*> vFiredBullets = {};
};

#endif /* SRC_GAME_OBJECTS_CHARACTER_HPP_ */
