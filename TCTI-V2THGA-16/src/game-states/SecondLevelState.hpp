/*
 * SecondLevelState.hpp
 *
 *  Created on: 22 Jan 2021
 *      Author: Milo
 */

#ifndef SRC_GAME_STATES_SECONDLEVELSTATE_HPP_
#define SRC_GAME_STATES_SECONDLEVELSTATE_HPP_

#include "game-states/LevelState.hpp"
#include "game-states/GameStateMachine.hpp"

class SecondLevelState : public LevelState {
public:
	SecondLevelState(GameData *apGameData);

	/**
	 * @brief
	 * Resets the state
	 */
	GameState* reset_state();
};

#endif /* SRC_GAME_STATES_SECONDLEVELSTATE_HPP_ */
