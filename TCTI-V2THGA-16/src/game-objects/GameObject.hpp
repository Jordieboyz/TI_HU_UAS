/*
 * GameObject.hpp
 *
 *  Created on: 11 Jan 2021
 *      Author: lucasw00079
 */

#ifndef SRC_GAME_OBJECTS_GAMEOBJECT_HPP_
#define SRC_GAME_OBJECTS_GAMEOBJECT_HPP_

#include "Renderable.hpp"

/** @file **/

class GameObject: public Renderable {
public:
	GameObject(sf::Vector2f av2fPos, sf::Vector2f av2fSize,
			const char *astrTexturePath, GameData *pGameData,
			float afRotation = 0.0f, const bool abTileable = false);

	virtual ~GameObject();

	virtual void collide(Player *apOther);

	/**
	 * @brief
	 *  Function to be called by bullet upon impact.
	 */
	virtual void shot(void);
	virtual void update(void) override;
	float getFRotation() const;
	void setFRotation(float fRotation = 0.0f);

	virtual bool get_is_collidable(void);

protected:
	float fRotation = 0.0f;

private:
	virtual void collision_action(void);
	const char *strTexturePath;

	friend class GameObjectFactory;

protected:
	bool bIsCollidable = true;
};

#endif /* SRC_GAME_OBJECTS_GAMEOBJECT_HPP_ */
