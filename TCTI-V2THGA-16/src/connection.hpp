/*
 * ServerConnection.hpp
 *
 *  Created on: 21 Jan 2021
 *      Author: erik
 */

#ifndef SRC_CONNECTION_HPP_
#define SRC_CONNECTION_HPP_

#include "game-objects/GameObjectFactory.hpp"

#define SERVER_COMM_HEADER_FORMAT 	"%d, %d\n"
#define SERVER_OBJECT_FORMAT 		"%d," OBJECT_STRING_FORMAT

#define SEND_SERVER_MSG(ID, E_TYPE);

enum SERV_ERROR
{
	SERV_ERROR_NONE,
	SERV_ERROR_NO_CONN,
	SERV_ERROR_BUSY,
	SERV_ERROR_TIMOUT
};

enum SERVER_MSG
{
	SERVER_MSG_NONE,
	SERVER_MSG_NEW_CLIENT,
	SERVER_MSG_SET_CLIENT,
	SERVER_MSG_GET_OBJECT_LIST,
	SERVER_MSG_GET_PLAYER,
	SERVER_MSG_OBJ_MOD,
	SERVER_MSG_OBJ_NEW,
	SERVER_MSG_OBJ_DEL
};


struct OnlineObject
{
	int iObjectID;
	GameObject *pObject;
};


#endif /* SRC_CONNECTION_HPP_ */
