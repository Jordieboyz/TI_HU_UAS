/*
 * GameObjectFactory.hpp
 *
 *  Created on: 15 Jan 2021
 *      Author: lucasw00079
 */

#ifndef SRC_GAME_OBJECTS_GAMEOBJECTFACTORY_HPP_
#define SRC_GAME_OBJECTS_GAMEOBJECTFACTORY_HPP_

#include <SFML/Graphics.hpp>

#define OBJECT_STRING_FORMAT "{ %f, %f }, { %f, %f }, %f, %s\n"

enum GAME_OBJECT_TYPE
{
	GAME_OBJECT_TYPE_WALL,
	GAME_OBJECT_TYPE_BARRIER,
	GAME_OBJECT_TYPE_NPC,
	GAME_OBJECT_TYPE_UNSPECIFIED,
	GAME_OBJECT_TYPE_GLASS
};

class  GameObject;
class  Player;
struct GameData;

/** @file **/

class GameObjectFactory {
public:
	static GameObjectFactory *get_instance();

	void dump_object(GameObject *apToDump, char *astrOut);

	/**
	 * @brief
	 *  Creates a new object from a string.
	 * @param aStrObj
	 * @param apData
	 * @return
	 */
	GameObject *create_object(const char *aStrObj,
			struct GameData *apData);

	/**
	 * @brief
	 *  Creates a new gameObject from enum and essential parameters.
	 * @param aeType
	 * @param av2fPos
	 * @param av2fSize
	 * @param apData
	 * @param aStrTexPath
	 * @param afRot
	 * @return
	 */
	GameObject* create_object(enum GAME_OBJECT_TYPE aeType,
			sf::Vector2f av2fPos, sf::Vector2f av2fSize, struct GameData *apData,
			const char *aStrTexPath = "", float afRot = 0.0f);

	/**
	 * @brief
	 *  Returns a character Player object, only to be called by
	 *  multi-player client.
	 * @param av2fPos
	 * @param av2fSize
	 * @param apData
	 * @param afRotation
	 * @return
	 */
	Player *create_player(sf::Vector2f av2fPos, sf::Vector2f av2fSize,
			struct GameData *apData, float afRotation);

private:
	/* Static inline variables are available in C++17 and up. */
	static inline GameObjectFactory *pInstance = nullptr;

	GameObjectFactory();
	virtual ~GameObjectFactory();
};

#endif /* SRC_GAME_OBJECTS_GAMEOBJECTFACTORY_HPP_ */
