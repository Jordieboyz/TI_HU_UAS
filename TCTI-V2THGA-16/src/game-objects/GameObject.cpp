/*
 * GameObject.cpp
 *
 *  Created on: 11 Jan 2021
 *      Author: lucasw00079
 */

#include "game-objects/GameObject.hpp"

GameObject::GameObject(sf::Vector2f av2fPos, sf::Vector2f av2fSize,
		const char *astrTexturePath, GameData *pGameData, float afRotation,
		const bool abTileable):
		Renderable(av2fPos, av2fSize, astrTexturePath, pGameData, abTileable),
		fRotation(afRotation),
		strTexturePath(astrTexturePath){
}

GameObject::~GameObject() {
}

void GameObject::update(void) {
	sprite.setRotation(fRotation);
//	sprite.setOrigin(v2fSize/2.0f);
	if(pData->pRenderWindow != nullptr)
		pData->pRenderWindow->draw( sprite );
}

void GameObject::collide(Player *apOther) {
}

void GameObject::shot(void) {
	collision_action();
}

void GameObject::setFRotation(float fRotation) {
	this->fRotation = fRotation;
}

void GameObject::collision_action(void) {
}

float GameObject::getFRotation() const {
	return fRotation;
}

bool GameObject::get_is_collidable(void) {
	return bIsCollidable;
}
