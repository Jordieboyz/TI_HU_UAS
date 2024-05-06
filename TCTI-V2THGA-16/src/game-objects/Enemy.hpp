/*
 * Enemy.hpp
 *
 *  Created on: 18 Jan 2021
 *      Author: Milo
 */

#ifndef SRC_GAME_OBJECTS_ENEMY_HPP_
#define SRC_GAME_OBJECTS_ENEMY_HPP_

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "game-objects/Character.hpp"
#include "game-objects/Player.hpp"
#include "Definitions.hpp"

/**
 * @file
 *
 * \brief
 * NPC_STATE enum
 * \details
 * This enum is used by the Enemies internal
 * state machine.
 */
enum NPC_STATE
{
	NPC_STATE_PATROL,    /**< NPC_STATE_PATROL */
	NPC_STATE_RETURN,    /**< NPC_STATE_RETURN */
	NPC_STATE_ALERT,     /**< NPC_STATE_ALERT */
	NPC_STATE_DEAD,      /**< NPC_STATE_DEAD */
	NPC_STATE_UNCONSCIOUS/**< NPC_STATE_UNCONSCIOUS */
};


/**
 * @brief
 * Enemy Class
 * @details
 * The Enemy class makes an Enemy which is capable
 * of following a specified path, generating a path
 * to the player and shooting at the player.
 */
class Enemy: public Character {
public:
	Enemy(sf::Vector2f av2fPos, sf::Vector2f av2fSize,
		     WeaponStats* apWeapon, GameData *pGameData,
			 std::vector<sf::Vector2f> aVecV2Path);

	virtual ~Enemy() = default;

	/**
	 * @brief
	 * update
	 * @details
	 * This update function handles all the
	 * different states, renders the objects
	 * shot bullets and updates the rotation.
	 */
	virtual void update() override;

	/**
	 * @brief
	 * follow_path
	 * @details
	 * This function moves the enemy closer
	 * to its destination, supports horizontal,
	 * vertical and diagonal movements.
	 * @param dest
	 * @param speed
	 */
	void follow_path(sf::Vector2f dest, float speed);

private:
	/**
	 * @brief
	 * check_destination_margin
	 * @details
	 * This function adds a margin to the destination
	 * and checks if the player has reached it. The
	 * margin in necessary because of the timescalar
	 * which is a float, this makes it so the player
	 * won't exactly reach its destination and may
	 * cause it to be stuck.
	 * @param dest
	 * @param margin
	 * @return
	 */
	bool check_destination_margin( sf::Vector2f dest, unsigned int margin = NPC_MOVEMENT_SPEED + 1 );

	/**
	 * @brief
	 * check_y_margin
	 * @details
	 * This checks the margin on only the y axis
	 * @param dest
	 * @param margin
	 * @return
	 */
	bool check_y_margin( sf::Vector2f dest, unsigned int margin = NPC_MOVEMENT_SPEED + 1 );

	/**
	 * @brief
	 * check_x_margin
	 * @details
	 * This checks the margin on only the y axis
	 * @param dest
	 * @param margin
	 * @return
	 */
	bool check_x_margin( sf::Vector2f dest, unsigned int margin = NPC_MOVEMENT_SPEED + 1 );

	/**
	 * @brief
	 * check_clear_line_of_sight
	 * @details
	 * This function creates a vision cone
	 * and checks if the player is within it
	 * the vision cone also considers walls
	 * within this vision cone
	 * @return
	 */
	bool check_clear_line_of_sight();

	/**
	 * @brief
	 * update_path_to_point_of_interest
	 * @details
	 * This function uses a form of the a*
	 * algorithm to navigate the compressed
	 * map.
	 * @param av2fOrigin
	 * @param av2fTarget
	 */
	void update_path_to_point_of_interest(sf::Vector2f av2fOrigin,
			sf::Vector2f av2fTarget);

	/**
	 * @brief
	 * update_rotation
	 * @details
	 * This function updates the rotation
	 * of the enemy. This can be the player
	 * or its destination.
	 * @param av2fTarget
	 */
	void update_rotation(sf::Vector2f av2fTarget);

	/**
	 * @brief
	 * patrol_handler
	 * @details
	 * This function handles the patrol
	 * state of the enemy. In the patrol
	 * state it follows its pre-deterimined
	 * path and checks if anything is spotted
	 * in its line of sight, if so it activates
	 * the alert handler
	 * @return
	 */
	enum NPC_STATE patrol_handler(void);

	/**
	 * @brief
	 * return_handler
	 * @details
	 * This function handles the return state
	 * this state occurs when the enemy lost
	 * the player and needs to return to
	 * its pre-determined path. It does so
	 * by using the update_path_to_point_of_interest
	 * function.
	 * @return
	 */
	enum NPC_STATE return_handler(void);

	/**
	 * @brief
	 * alert_handler
	 * @details
	 * This function handles the alert state
	 * it goes to the last seen location of the
	 * player and keeps updating it while shooting
	 * at the player.
	 * @return
	 */
	enum NPC_STATE alert_handler(void);

	/**
	 * @brief
	 * dead_handler
	 * @details
	 * This function handles the dead state
	 * it keeps returning NPS_STATE_DEAD
	 * @return
	 */
	enum NPC_STATE dead_handler(void);

	/**
	 * @brief
	 * Sets the internal state if a shot
	 * has been heard.
	 * @details
	 * Modifies internals state of object
	 * significantly it will update vPlayerPath
	 * and set the state to NPC_STATE_ALERT
	 * @return
	 * Returns NPC_STATE_ALERT if sound is heard
	 * else -1;
	 */
	int listen(void);

	virtual void shot_action() override;

	std::vector<sf::Vector2f> vPlayerPath;
	std::vector<sf::Vector2f> vPath;
	unsigned int uCurrentDest = 0;
	unsigned int uPlayerPathDest = 0;
	float fSpeed = NPC_MOVEMENT_SPEED;
	enum NPC_STATE eState = NPC_STATE_PATROL;
};

#endif /* SRC_GAME_OBJECTS_ENEMY_HPP_ */
