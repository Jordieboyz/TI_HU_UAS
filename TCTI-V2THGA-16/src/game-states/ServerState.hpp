/*
 * ServerState.hpp
 *
 *  Created on: 21 Jan 2021
 *      Author: lucasw00079
 */

#ifndef SRC_GAME_STATES_SERVERSTATE_HPP_
#define SRC_GAME_STATES_SERVERSTATE_HPP_

#include <game-states/GameState.hpp>

#include <cstdio>

#include <SFML/Network.hpp>
#include "connection.hpp"
#include "Definitions.hpp"

class ServerState: public GameState {
public:
	/**
	 * @brief
	 *  Loads all static object from map and assigns
	 *  ObjectID's to them
	 * @param apGameData
	 */
	ServerState(GameData *apGameData);

	/**
	 * @brief
	 *  Closes socket
	 */
	virtual ~ServerState();

	/**
	 * @brief
	 *  Main loop, waits for connection then
	 *  handles requests from client.
	 */
	virtual void update() override;

	/**
	 * @brief
	 *  Doesn't do anything used to maintain
	 *  compatible with interface provided by GameState.
	 */
	virtual void handle_input() override;

private:
	int get_new_client_id(void);

	/**
	 * @brief
	 *  Dumps all object into objectsAsString buffer starting
	 *  at arrOnlineObjects[auStartIndex] up to arrOnlineObjects[auEndIndex].
	 * @param auStartIndex
	 * @param auEndIndex
	 * @return Length of data in objectsAsString
	 */
	int update_object_list(unsigned auStartIndex, unsigned auEndIndex);

	/**
	 * @brief
	 *  Handles a SERVER_MSG_OBJ_MOD request updating object
	 *  in arrOnlineObjects to match.
	 * @param apSock connection to client.
	 */
	void object_mod_handler(sf::TcpSocket *apSock);

	/**
	 * @brief
	 *  Handles a SERVER_MSG_OBJ_NEW request pushing new
	 *  object in arrOnlineOjbects and sending back the iObjectID.
	 * @param apSock
	 */
	void object_new_handler(sf::TcpSocket *apSock);

	/**
	 * @brief
	 *  Handles a SERVER_MSG_OBJ_DEL request deleting object
	 *  from arrOnlineObject after checking whether object can be deleted.
	 * @param apSock
	 */
	void object_del_handler(sf::TcpSocket *apSock);

	int iClientCount = 0;
	int iNumObjects  = 0;

	sf::TcpListener TCPSocket;

	char objectsAsString[8192];
	int  arrClientPlayerMap[256];
	int  iLevelElements;

	std::vector<OnlineObject*> arrOnlineObjects;
	std::vector<OnlineObject*> arrOnlinePlayers;
};

#endif /* SRC_GAME_STATES_SERVERSTATE_HPP_ */
