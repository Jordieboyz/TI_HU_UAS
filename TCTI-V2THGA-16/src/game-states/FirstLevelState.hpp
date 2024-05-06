/*
 * FirstLevelState.hpp
 *
 *  Created on: 20 Jan 2021
 *      Author: Milo
 */

#ifndef SRC_GAME_STATES_FIRSTLEVELSTATE_HPP_
#define SRC_GAME_STATES_FIRSTLEVELSTATE_HPP_

#include "game-states/LevelState.hpp"

class FirstLevelState : public LevelState {
public:
	FirstLevelState(GameData *apGameData);

	/**
	 * @brief
	 * Resets the state
	 */
	GameState* reset_state();
};

#endif /* SRC_GAME_STATES_FIRSTLEVELSTATE_HPP_ */
