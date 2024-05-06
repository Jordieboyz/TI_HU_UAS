#pragma once

#include <iostream>
#include <math.h>
#include <array>
#include "game-objects/GameObject.hpp"
#include "Definitions.hpp"
#include "game-objects/Player.hpp"

class GameObject;

/** @file **/

class Door : public GameObject
{
public:
	/**
	 * @brief
	 *  Door constructor
	 * @details
	 *	The door creates a special collisionbox using vertices, the amount of vertices is determined by the size of the object.
	 * @params
	 *	abPositiveRotation dictates whether the door will open up to a positive y axis or negative y axis
	 */
	Door(sf::Vector2f av2fPos, sf::Vector2f av2fSize, const char* astrTexturePath, GameData* apGameData, 
		bool abPositiveRotation = true);
	~Door() = default;

	/**
	 * @brief
	 *  function for interactions
	 * @details
	 *	Opens the door if the other game object is in it's vicinity, opens the door to the direction the player wants to go.
	 * @params
	 *	the GameObject it is interacting with
	 *	Distance is calculated with pythagoras theorem: c² = a² + b²
	 */
	virtual void Interact(GameObject* apOther);

	/**
	* @brief
	*	updates the door
	* @details
	*	Updates the doors rotation according to the rotation speed multiplied by the time multiplier.
	*	It then draws door.
	*/
	virtual void update() override;

	/**
	* @brief
	*	door collision check
	* @details
	*	Is needed because the door uses an array of vertices to calculate whether it collides with anything.
	*/
	virtual void collide(Player* apOther) override;

private:
	/**
	* @brief
	*	calculates new collision points
	* @details
	*	This function calculates the new positions of all vertices in the vertex array using the angle of rotation for the door.\n\n
	* 
	*	formulas (x' is new x coordinate, y' is new y coordinate, a is the angle of rotation):\n
	*		x' = x cos(a) - y * sin(a)\n
	*		y' = x sin(a) + y * cos(a)\n\n
	* 
	*	Note that the original x and y coordinates have to be translated to a coordinate where the hinge is the origin (0, 0).
	*	This is easily done by substracting the hinge coordinate from the vertex position coordinate.
	*	After calculating the new coordinate, translate it back into a coordinate on the actual game by adding the hinge coordinate once more.
	* @params
	*	angle of rotation change
	*/
	void UpdateCollisionPoints(float fRotationAngle);

	float fRotationOrigin = 0.f;
	float fRotationDegrees = 0.f;
	float fRotationSpeed = 0.f;

	bool bPositiveRotation;

	std::vector<sf::Vertex> varrCollisionPoints = {};
};

