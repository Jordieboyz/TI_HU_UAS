/*
 * Player.cpp
 *
 *  Created on: 12 Jan 2021
 *      Author: lucasw00079
 */

#include <cmath>
#include "game-objects/Player.hpp"

#include "game-states/GameOverState.hpp"
#include "game-states/GameStateMachine.hpp"


Player::Player(sf::Vector2f av2fPos, sf::Vector2f av2fSize,
		WeaponStats* apWeapon, GameData *pGameData):
		Character(av2fPos, av2fSize, apWeapon, pGameData)
{
}

Player::~Player() {
}

void Player::update_rotation() {
	/* Rotate to look to mouse */
	sf::Vector2i v2iMouse;
	if(pData->pRenderWindow != nullptr)
		v2iMouse = sf::Mouse::getPosition(*pData->pRenderWindow);

	/* Adjust mouse position for current view */
	sf::View tmpView = pData->pRenderWindow->getView();
	sf::Vector2f vec2fLocation = tmpView.getCenter() - tmpView.getSize() / 2.0f;

	v2iMouse += sf::Vector2i{(int)vec2fLocation.x, (int)vec2fLocation.y};

	sf::Vector2f v2fDirection = { v2iMouse.x - (v2fPos.x + (v2fSize.x / 2.0f)),
									v2iMouse.y - (v2fPos.y + (v2fSize.y) / 2.0f) };

	fRotation = (180.0f/PI) * atan(v2fDirection.y / v2fDirection.x);

	if(v2fDirection.x < 0.0f)
		fRotation += 180.0f;
}

void Player::set_last_location( sf::Vector2f av2fNewLocation ){
	v2fLastLocation = av2fNewLocation;
}

sf::Vector2f Player::get_last_location() {
	return v2fLastLocation;
}

void Player::shot_action() {
	sf::View tmpView = pData->pRenderWindow->getView();
	tmpView.setCenter(sf::Vector2f(WINDOW_LENGTH, WINDOW_HEIGHT)/2.0f);
	pData->pRenderWindow->setView(tmpView);
//	bIsCollidable = false;
//	pData->pStateMachine->set_state(new GameOverState(pData, 0));
}
