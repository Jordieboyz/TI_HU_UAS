/*
 * ThirdLevelState.hpp
 *
 *  Created on: 25 Jan 2021
 *      Author: Milo
 */

#ifndef SRC_GAME_STATES_THIRDLEVELSTATE_HPP_
#define SRC_GAME_STATES_THIRDLEVELSTATE_HPP_

#include "game-states/LevelState.hpp"

class ThirdLevelState: public LevelState {
public:
	ThirdLevelState(struct GameData *apGameData);
	
	/**
	 * @brief
	 * Resets the state
	 */
	GameState* reset_state();
};

#endif /* SRC_GAME_STATES_THIRDLEVELSTATE_HPP_ */
