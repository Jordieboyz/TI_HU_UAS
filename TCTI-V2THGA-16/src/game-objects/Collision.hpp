/*
 * Collisions.hpp
 *
 *  Created on: 12 Jan 2021
 *      Author: MiloB
 */

#ifndef SRC_COLLISIONS_HPP_
#define SRC_COLLISIONS_HPP_

#include "Player.hpp"

/**
 * @file
 *
 * @brief
 * Collision Class
 * @details
 * This class is used to detect collisions,
 * it also has a few options to handle collisions.
 */

class Collision {
public:
	Collision();
	~Collision();

	/**
	 * @brief
	 * check_renderable_collision
	 * @details
	 * This function is able to detect a collision beteen
	 * any 2 renderable objects. It also has the option to handle
	 * collisions by moving the first object.
	 * @param object1
	 * @param object2
	 * @param margin
	 * @param handleObject1Collisions
	 * @return
	 */
	bool check_renderable_collision(Renderable *object1, Renderable *object2, float margin = 12, bool handleObject1Collisions = true);


	/**
	 * @brief
	 * handle_player_collision
	 * @details
	 * This function is specifically made to handle the collisions
	 * beteen the player and the walls.
	 * @param object1
	 * @param object2
	 */
	void handle_player_collision(Player *object1, Renderable *object2);
};

#endif /* SRC_COLLISIONS_HPP_ */
