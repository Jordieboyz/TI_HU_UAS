/*
 * ClientState.hpp
 *
 *  Created on: 21 Jan 2021
 *      Author: lucasw00079
 */

#ifndef SRC_GAME_STATES_CLIENTSTATE_HPP_
#define SRC_GAME_STATES_CLIENTSTATE_HPP_

#include <game-states/GameState.hpp>

#include <cstdio>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>

#include <SFML/Network.hpp>
#include "connection.hpp"
#include "Definitions.hpp"

class ClientState: public GameState {
public:

	/**
	 * @brief
	 *  Constructor that initialises the ClientID and
	 *  gets the list of static objects from the server.
	 * @param apGameData
	 */
	ClientState(GameData *apGameData);

	/**
	 * @brief
	 *  Unlocks mutexes and joins the network thread.
	 */
	virtual ~ClientState();

	/**
	 * @brief
	 *  Main loop of the client handling graphics and
	 *  scheduling of commands.
	 */
	virtual void update() override;

	/**
	 * @brief
	 *  Exists to comply with the interface of GameState,
	 *  not used.
	 */
	virtual void handle_input() override;

private:
	/**
	 * @brief
	 *  A Command contains a SERVER_MSG and
	 *  a target object if applicable if not
	 *  it should be set to a nullptr.
	 */
	struct Command {
		enum SERVER_MSG eCmdType;
		OnlineObject *pOnObj;
	};

	/**
	 * @brief
	 *  Checks whether keys are pressed and creates an object used
	 *  to notify server.
	 */
	void update_player_position(void);

	/**
	 * @brief
	 *  Opens connection to server.
	 */
	void start_transaction(void);

	/**
	 * @brief
	 *  Sends an empty message to server, prompting the server
	 *  to close the connection.
	 */
	void end_transaction(void);

	/**
	 * @brief
	 *  Main loop for thread that does the server communication.
	 * @details
	 *  In order to close join this thread the main thread has to
	 *  release the lock on the command and object mutexes and wait until
	 *  the thread has sent the latest updates it will then quit.
	 */
	void do_server_communication();

	/**
	 * @brief
	 *  Sends all commands scheduled without closing
	 *  the connection in between operations.
	 * @details
	 *  This command should not be called by the main thread while the
	 *  server communication thread is active as it could crash both the
	 *  client and the server.
	 *  This function does not lock the command mutex, it expects a copy to
	 *  be passed instead.
	 * @param apCommands Command array containing commands to be sent.
	 */
	void send_pending_commands(std::vector<Command> *apCommands);

	/**
	 * @brief
	 *  Notifies server that we would like to participate in online game,
	 *  server will send back a new client ID.
	 */
	void get_client_ID(void);

	/**
	 * @brief
	 *  Returns the list of objects on server.
	 * @details
	 *  This function also has to be called directly after getting a
	 *  client ID, the server will then return a list of all static objects.
	 *  all subsequent calls will yield a list containing all moving
	 *  objects.
	 */
	void get_object_list(void);

	/**
	 * @brief
	 *  Sets the playerObjectID to the OnlineObject representing the local
	 *  player.
	 */
	void get_player(void);

	/**
	 * @brief
	 *  Dumps the essentials of the GameObject contained by apGObj and
	 *  sends the parameters to the server.
	 * @param apGObj OnlineObject that has been modified.
	 */
	void send_mod_object_to_server(OnlineObject *apGObj);

	/**
	 * @brief
	 *  Dumps the essentials and then sends the new object to server.
	 * @details
	 *  The onlineObject is sent with IObjectID = -1, the server will return
	 *  the ObjectID of the new object.
	 * @param OnlineObject New object
	 */
	void send_new_object_to_server(OnlineObject *apOnObj);

	/**
	 * @brief
	 *  Requests an OnlineObject to be removed from game.
	 * @details
	 *  A client can request the deletion of every object, if the requested
	 *  object is an essential item of the level, the server simply won't
	 *  comply.
	 * @param apOnObj OnlineObject to be removed
	 */
	void send_del_object_to_server(OnlineObject *apOnObj);

	sf::TcpSocket TCPSocket;
	int iClientID = -1;
	int iPlayerObjID = -1;
	int iLevelElements = -1;

	Player *pPlayer = nullptr;

	int iNumBullets = 0;

	std::vector<Command> arrPendingCommands;
	std::mutex commandMutex;
	std::vector<OnlineObject*> arrBullets;
	std::vector<OnlineObject*> arrOnlineObjects;
	std::vector<OnlineObject*> arrLocalObjects;
	std::mutex objectMutex;

	std::thread *communicationThread;
	bool bRunCommThread = true;
};

#endif /* SRC_GAME_STATES_CLIENTSTATE_HPP_ */
