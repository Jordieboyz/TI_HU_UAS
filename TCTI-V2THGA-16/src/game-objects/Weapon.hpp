#ifndef SRC_GAME_OBJECTS_WEAPON_HPP_
#define SRC_GAME_OBJECTS_WEAPON_HPP_

#include "game-objects/GameObject.hpp"
#include "animated-sprites.hpp"

class GameObject;

/** @file **/

enum WeaponTypes
{
	MP5,
	M16,
	SHOTGUN
};

class Weapon : public GameObject {
public:
	Weapon(sf::Vector2f av2fPos, const char* astrTexturePath, GameData* apGameData, const float afBulletVelocity, const float afBulletSpreadDegreesMax,
		const unsigned int auintBulletsFired, const AnimationData* apAnimationData, std::string filepath );
	~Weapon() = default;

	/**
	 * @brief
	 *  Weapon update
	 * @details
	 *	Draws the weapon if it is not used.
	 */
	virtual void update() override;

	/**
	 * @brief
	 *  bIsUsed getter
	 * @returns
	 *	true if weapon is in use by a character, otherwise false
	 */
	const bool is_used() { return bIsUsed; };

	/**
	 * @brief
	 *  bIsUsed setter
	 * @params
	 *	set to true if the weapon is going to be used by a character
	 */
	void set_used(bool aUsed) { bIsUsed = aUsed; };

	//all of them are const, so this is acceptable
	const float fBulletVelocity;
	const float fBulletSpreadDegreesMax;
	const unsigned int uintBulletsFired;
	const AnimationData* const pAnimationData;

	GameSound sound;
private:

	bool bIsUsed = false;

};

struct WeaponStats
{
	/**
	 * @brief
	 *  Weapon wrapper
	 * @details
	 *	This wrapper makes it possible to have a finite amount of predetermined weapon types.
	 *	Weapon types are dictated by enum WeaponTypes.
	 */
	WeaponStats(sf::Vector2f av2fPos, GameData* apGameData, WeaponTypes aType)
	{
		switch (aType)
		{
		case MP5:
			pWeapon = new Weapon(av2fPos, MP5_TEXTURE, apGameData, 70.f, 2.f, 1, PLAYER_ANIMATIONS_MP5, MP5_SOUND );
			break;
		case M16:
			pWeapon = new Weapon(av2fPos, M16_TEXTURE, apGameData, 30.f, 3.f, 1, PLAYER_ANIMATIONS_M16, M16_SOUND);
			break;
		case SHOTGUN:
			pWeapon = new Weapon(av2fPos, SHOTGUN_TEXTURE, apGameData, 15.f, 10.f, 5, PLAYER_ANIMATIONS_SHOTGUN, SHOTGUN_SOUND);
			break;
		}
	};

	//weapon
	Weapon* pWeapon = nullptr;
};

#endif /* SRC_GAME_OBJECTS_WEAPON_HPP_ */
