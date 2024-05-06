/*
 * GameStateMachine.hpp
 *
 *  Created on: 11 Jan 2021
 *      Author: lucasw00079
 */

#ifndef SRC_GAME_STATES_GAMESTATEMACHINE_HPP_
#define SRC_GAME_STATES_GAMESTATEMACHINE_HPP_

#include <array>
#include "game-states/GameState.hpp"

// all possible states
#include "game-states/MainMenuState.hpp"
#include "game-states/FirstLevelState.hpp"
#include "game-states/SecondLevelState.hpp"
#include "game-states/ThirdLevelState.hpp"
#include "game-states/GameOverState.hpp"
#include "game-states/WinState.hpp"
#include "game-states/PauseMenuState.hpp"
#include "game-states/GameCompletedState.hpp"

/** @file **/

class GameStateMachine {
public:

	/**
	 * @brief
	 *  Sets a new state, switching over as soon as update loop has ended.
	 * @details
	 *  This function makes the assumption that the state to be set is
	 *  Dynamically allocated. The state machine will deallocate object at
	 *  pointer.
	 * @param apGameState DYNAMICALLY allocated state.
	 */
	void set_state(GameState *apGameState);

	/**
	 * @brief
	 *  Main loop, gives state time to handle input and draw.
	 * @details
	 *  It also detects whether the state has changed and deallocates the
	 *  old state.
	 */
	void update(void);

	/**
	 * @brief
	 *  Returns currently set state.
	 * @return
	 *  current game state.
	 */
	GameState* get_old_state();

private:
	GameState *pCurrGameState;
	GameState* pOldState = nullptr;
};

#endif /* SRC_GAME_STATES_GAMESTATEMACHINE_HPP_ */
