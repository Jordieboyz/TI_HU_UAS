/*
 * GameObjectFactory.cpp
 *
 *  Created on: 15 Jan 2021
 *      Author: lucasw00079
 */

#include "game-objects/GameObjectFactory.hpp"

#include <cstdio>
#include "game-objects/Glass.hpp"

#include "game-objects/GameObject.hpp"
#include "game-objects/Player.hpp"
#include "Definitions.hpp"

GameObjectFactory* GameObjectFactory::get_instance() {
	if(pInstance == nullptr)
		pInstance = new GameObjectFactory;

	return pInstance;
}

GameObjectFactory::GameObjectFactory() {
}

GameObject* GameObjectFactory::create_object(enum GAME_OBJECT_TYPE aeType,
		sf::Vector2f av2fPos, sf::Vector2f av2fSize, struct GameData *apData,
		const char *aStrTexPath, float afRot) {
	GameObject *pRetVal = nullptr;

	switch(aeType){
	case GAME_OBJECT_TYPE_WALL:
		pRetVal = new GameObject(av2fPos, av2fSize, BRICK_TEXTURE, apData, 0.0f, true);
		break;
	case GAME_OBJECT_TYPE_BARRIER:
		pRetVal = new GameObject(av2fPos, av2fSize, TRANSPARENT_TEXTURE, apData, afRot);
		break;
	case GAME_OBJECT_TYPE_NPC:
		break;
	case GAME_OBJECT_TYPE_GLASS:
		pRetVal = new Glass(av2fPos, av2fSize, apData);
		break;
	case GAME_OBJECT_TYPE_UNSPECIFIED:
		pRetVal = new GameObject(av2fPos, av2fSize, aStrTexPath, apData, afRot);
		break;
	default:
		break;
	}

	return pRetVal;
}

GameObject* GameObjectFactory::GameObjectFactory::create_object(
		const char *aStrObj, struct GameData *apData) {

	float posX, posY;
	float sizX, sizY;
	float fRot;
	char  strPath[256];

	sscanf(aStrObj, OBJECT_STRING_FORMAT, &posX, &posY, &sizX,
			&sizY, &fRot, strPath);

	return create_object(GAME_OBJECT_TYPE_UNSPECIFIED, {posX, posY},
			{sizX, sizY}, apData, strPath);
}

void GameObjectFactory::dump_object(GameObject *apToDump, char *astrOut) {
	sprintf(astrOut, OBJECT_STRING_FORMAT, apToDump->v2fPos.x, apToDump->v2fPos.y,
			apToDump->v2fSize.x, apToDump->v2fSize.y, apToDump->fRotation, apToDump->strTexturePath);
}

Player* GameObjectFactory::create_player(sf::Vector2f av2fPos,
		sf::Vector2f av2fSize, struct GameData *apData, float afRotation) {
	return new Player(av2fPos, av2fSize, new WeaponStats({ 0, 0 }, apData, M16), apData);
}

GameObjectFactory::~GameObjectFactory() {
	delete pInstance;
}

