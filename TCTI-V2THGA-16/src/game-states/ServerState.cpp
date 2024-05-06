/*
 * ServerState.cpp
 *
 *  Created on: 21 Jan 2021
 *      Author: lucasw00079
 */

#include <game-states/ServerState.hpp>

#include <cstdlib>
#include <cstring>

#include "game-objects/Player.hpp"
#include "ObjectGenerator.hpp"

ServerState::ServerState(GameData *apGameData)
: GameState(apGameData)
{
	printf("Entering Server mode \n");
	TCPSocket.setBlocking(true);
	TCPSocket.listen(SERVER_PORT_DEC);

	ObjectGenerator objGenerator("res/level3.bmp", apGameData);
	GameObject *pBackground = new GameObject({0,0}, {5120,2880},
			"res/background4.png", pGameData);

	OnlineObject *pTmpOnlineObject = new OnlineObject;
	pTmpOnlineObject->iObjectID = iNumObjects++;
	pTmpOnlineObject->pObject = pBackground;
	arrOnlineObjects.push_back(pTmpOnlineObject);

	while(true){
		GameObject *pObj = objGenerator.generate_object(GAME_OBJECT_TYPE_WALL,
				WALL_GENERATOR_COL_TO_SEARCH);
		if(pObj == nullptr)
			break;

		OnlineObject *pTmpOnlineObject = new OnlineObject;
		pTmpOnlineObject->iObjectID = iNumObjects++;
		pTmpOnlineObject->pObject = pObj;

		arrOnlineObjects.push_back(pTmpOnlineObject);
	}

	while(true){
		GameObject *pObj = objGenerator.generate_object(GAME_OBJECT_TYPE_BARRIER,
				WALL_GENERATOR_COL_BARRIER);
		if(pObj == nullptr)
			break;

		OnlineObject *pTmpOnlineObject = new OnlineObject;
		pTmpOnlineObject->iObjectID = iNumObjects++;
		pTmpOnlineObject->pObject = pObj;

		arrOnlineObjects.push_back(pTmpOnlineObject);
	}

	iLevelElements = arrOnlineObjects.size();
}

ServerState::~ServerState() {
	TCPSocket.close();
}

void ServerState::update() {
		sf::TcpSocket clientConn;
		if(TCPSocket.accept(clientConn) == sf::Socket::Done) {
			char commandBuffer[256];
			std::size_t numReceived;

			unsigned bLoop = 1;
			int iClientID;
			int iType;
			int iPayloadLen;

			while(bLoop) {
				/* Receive header, make valid string by appending null character */
				clientConn.receive(commandBuffer, 256, numReceived);
				*(commandBuffer + numReceived) = 0x00;
				sscanf(commandBuffer, SERVER_COMM_HEADER_FORMAT, &iClientID, &iType);

				switch(iType)
				{
					case SERVER_MSG_NONE:
						bLoop = 0;
						break;

					case SERVER_MSG_NEW_CLIENT:
						iType = get_new_client_id();
						clientConn.send(&iType, sizeof(int));
						break;

					case SERVER_MSG_GET_OBJECT_LIST:
						if(iClientID != -1)
							iPayloadLen = update_object_list(iLevelElements-1, arrOnlineObjects.size());
						else
							iPayloadLen = update_object_list(0, iLevelElements);
						clientConn.send(objectsAsString, iPayloadLen);
						/* Client needs time to process request wait until
						 * reception is confirmed */
						clientConn.receive(commandBuffer, 4, numReceived);
						break;

					case SERVER_MSG_GET_PLAYER:
						iType = arrClientPlayerMap[iClientID];
						clientConn.send(&iType, sizeof(int));
						break;

					case SERVER_MSG_OBJ_MOD:
						object_mod_handler(&clientConn);
						break;

					case SERVER_MSG_OBJ_NEW:
						object_new_handler(&clientConn);
						break;

					case SERVER_MSG_OBJ_DEL:
						object_del_handler(&clientConn);
						break;

					default:
						bLoop = 0;
						break;
				}

				if(bLoop == 0)
					break;

				/* This send indicates that server is
				 * ready for next msg. */
				clientConn.send(&iType, 4);
			}
			clientConn.disconnect();
		}
}

void ServerState::handle_input() {
}

int ServerState::get_new_client_id(void) {
	/* Construct new playable character */
	GameObject *pTmp = GameObjectFactory::get_instance()->create_player(
				{200,200}, {64,64}, pGameData, 0.0f);

	OnlineObject *pOn = new OnlineObject;
	pOn->iObjectID = iNumObjects++;
	pOn->pObject   = pTmp;
	arrOnlineObjects.push_back(pOn);

	arrClientPlayerMap[iClientCount] = pOn->iObjectID;

	return iClientCount++;
}

int ServerState::update_object_list(unsigned auStartIndex, unsigned auEndIndex) {
	char *pCurrString = objectsAsString;

	for(unsigned i = auStartIndex; i < auEndIndex; i++) {
		OnlineObject *currObject = arrOnlineObjects[i];
		sprintf(pCurrString, "%d,", currObject->iObjectID);

		char cTmp[256];
		GameObjectFactory::get_instance()->dump_object(
				currObject->pObject, cTmp);

		strcat(pCurrString, (const char*)cTmp);

		pCurrString += strlen(pCurrString)+1;
	}

	int iRetVal = pCurrString - objectsAsString;
	/* nothing to send send minimal string */
	if(iRetVal == 0) {
		strcpy(objectsAsString, "\n");
		iRetVal = 1;
	}
	return iRetVal;
}

void ServerState::object_mod_handler(sf::TcpSocket *apSock) {
	char cBuff[256];
	std::size_t payloadLen;

	/* Send data to indicate ready data itself doesn't matter */
	apSock->send(cBuff, 4);

	/* Create temporally object, update object in arrOnlineObjects
	 * to match. */
	apSock->receive(cBuff, 256, payloadLen);

	int   iID;
	float xPos, yPos;
	float xSiz, ySiz;
	float fRot;
	char texPath[128];

	sscanf(cBuff, SERVER_OBJECT_FORMAT, &iID, &xPos,
			&yPos, &xSiz, &ySiz, &fRot, texPath);

	for(unsigned i = 0; i < arrOnlineObjects.size(); i++) {
		OnlineObject *currObject = arrOnlineObjects[i];

		if(currObject->iObjectID == iID) {
			GameObject *pGObj = currObject->pObject;
			pGObj->set_pos({xPos, yPos});
			pGObj->set_size({xSiz, ySiz});
			pGObj->setFRotation(fRot);

			break;
		}
	}

	apSock->send(&iID, sizeof(int));
}

void ServerState::object_new_handler(sf::TcpSocket *apSock) {
	char cBuff[256];
	std::size_t payloadLen;

	/* Send data to indicate ready data itself doesn't matter */
	apSock->send(cBuff, 4);

	apSock->receive(cBuff, 256, payloadLen);

	int   iID;
	float xPos, yPos;
	float xSiz, ySiz;
	float fRot;
	char texPath[128];

	sscanf(cBuff, SERVER_OBJECT_FORMAT, &iID, &xPos,
			&yPos, &xSiz, &ySiz, &fRot, texPath);

	OnlineObject *pTmp = new OnlineObject;
	pTmp->iObjectID = iNumObjects++;
	pTmp->pObject = GameObjectFactory::get_instance()->create_object(
					GAME_OBJECT_TYPE_UNSPECIFIED, {xPos, yPos}, {xSiz, ySiz},
					pGameData, texPath);

	arrOnlineObjects.push_back(pTmp);

	apSock->send(&pTmp->iObjectID, sizeof(int));
}

void ServerState::object_del_handler(sf::TcpSocket *apSock) {
	char cBuff[256];
	std::size_t payloadLen;

	/* Send data to indicate ready data itself doesn't matter */
	apSock->send(cBuff, 4);

	apSock->receive(cBuff, 4, payloadLen);
	int iToRemove = *(int*)(cBuff);

	/* Item requested is essential part of level, don't */
	if(iToRemove < iLevelElements)
		return;

	for(int i = 0; i <= iClientCount; i++) {
		if(iToRemove == arrClientPlayerMap[i]) {
			arrClientPlayerMap[i] = -1;
		}
	}


	for(int i = 0; i < arrOnlineObjects.size(); i++) {
		if(arrOnlineObjects[i]->iObjectID == iToRemove) {
			arrOnlineObjects.erase(arrOnlineObjects.begin() + i);
			break;
		}
	}
}
