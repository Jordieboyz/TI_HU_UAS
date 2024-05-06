/*
 * ClientState.cpp
 *
 *  Created on: 21 Jan 2021
 *      Author: lucasw00079
 */

#include <game-states/ClientState.hpp>

#include <cstdio>
#include <cstring>

#include "game-objects/GameObject.hpp"
#include "game-objects/Player.hpp"
#include "game-objects/Collision.hpp"
#include "game-states/GameOverState.hpp"

ClientState::ClientState(GameData *apGameData) :
		GameState(apGameData) {
	printf("Entering Client mode \n");

	std::vector<Command> tmpCommands = {
			{SERVER_MSG_GET_OBJECT_LIST, nullptr},
			{SERVER_MSG_NEW_CLIENT, nullptr}
	};

	send_pending_commands(&tmpCommands);

	iLevelElements = arrOnlineObjects.size();

	communicationThread = new std::thread(&ClientState::do_server_communication, this);

	printf("Got client ID: %d\n", iClientID);
}

ClientState::~ClientState() {
	bRunCommThread = false;

	objectMutex.unlock();
	commandMutex.unlock();
	communicationThread->join();
	TCPSocket.disconnect();

	delete communicationThread;
}

void ClientState::update() {
	objectMutex.lock();
		arrLocalObjects = arrOnlineObjects;
	objectMutex.unlock();

	if (iPlayerObjID == -1 && pPlayer != nullptr){
		sf::View currView = pGameData->pRenderWindow->getView();
		currView.setCenter(sf::Vector2f(WINDOW_LENGTH, WINDOW_HEIGHT)/2.0f);
		pGameData->pRenderWindow->setView(currView);
		pGameData->pStateMachine->set_state(new GameOverState(pGameData, 0));
		return;
	}

	if (pPlayer == nullptr) {
		GameObject *pTmp;

		for (unsigned i = 0; i < arrLocalObjects.size(); i++) {
			if (arrLocalObjects[i]->iObjectID == iPlayerObjID) {
				pTmp = arrLocalObjects[i]->pObject;

				pPlayer = GameObjectFactory::get_instance()->create_player(
						{128,128}, pTmp->get_size(), pGameData,
						pTmp->getFRotation());
				break;
			}
		}
		return;
	}

	/* Focus camera on player */
	sf::View currView = pGameData->pRenderWindow->getView();
	currView.setCenter(pPlayer->get_pos() + pPlayer->get_size() / 2.0f);
	pGameData->pRenderWindow->setView(currView);

	for (OnlineObject *pOnObject : arrLocalObjects) {
		if (pOnObject->iObjectID == iPlayerObjID)
			continue;

		pOnObject->pObject->update();
	}

	update_player_position();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (pPlayer->shoot()) {
			struct OnlineObject *tmpBullet = new OnlineObject;
			tmpBullet->iObjectID = -1; /* ID currently unknown */
			tmpBullet->pObject = pPlayer->get_fired_bullets()->back();
commandMutex.lock();
			arrPendingCommands.push_back({SERVER_MSG_OBJ_NEW, tmpBullet});
commandMutex.unlock();
			arrBullets.push_back(tmpBullet);
		}
	}

	/* Update bullets on server to match local bullets. */
	for (OnlineObject *pOnObject : arrBullets) {
		pOnObject->pObject->update();
		sf::Vector2f vec2fRelativePos(
				pOnObject->pObject->get_pos().x - pPlayer->get_pos().x,
				pOnObject->pObject->get_pos().y - pPlayer->get_pos().y );

		if(vec2fRelativePos.x < -1000.0f || vec2fRelativePos.x > 1000.0f
				|| vec2fRelativePos.y < -1000.0f || vec2fRelativePos.y > 1000.0f) {
			arrBullets.erase(std::find(arrBullets.begin(), arrBullets.end(),
					pOnObject));
			break;
		}


commandMutex.lock();
		arrPendingCommands.push_back({SERVER_MSG_OBJ_MOD, pOnObject});
commandMutex.unlock();
	}

	/* Collision check on bullets */
	Collision no;
	for (OnlineObject *pOnBullet : arrBullets) {
		for (OnlineObject *pOnObject : arrLocalObjects) {
			if (pOnObject->iObjectID == iPlayerObjID)
				continue;

			if (pOnBullet->iObjectID == pOnObject->iObjectID)
				continue;

			/* Don't collide with background */
			if (pOnObject->iObjectID == 0)
				continue;

			if (no.check_renderable_collision(pOnBullet->pObject,
					pOnObject->pObject, -10.0f, false)) {

				/* Remove bullet (local) */
				arrBullets.erase(
						std::find(arrBullets.begin(), arrBullets.end(),
								pOnBullet));

commandMutex.lock();

				/* Remove bullet (remote) */
				arrPendingCommands.push_back({SERVER_MSG_OBJ_DEL, pOnBullet});

				/* Remove other (remote) */
				arrPendingCommands.push_back({SERVER_MSG_OBJ_DEL, pOnObject});

commandMutex.unlock();

				break;
			}
		}
	}

	for (OnlineObject *pOnObject : arrBullets) {
		pOnObject->pObject->update();
	}

	pPlayer->update();
}

void ClientState::handle_input() {
}

void ClientState::update_player_position(void) {
	if(!pGameData->pRenderWindow->hasFocus())
		return;

	sf::Vector2f v2fDeltaPos = { 0.0f, 0.0f };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		v2fDeltaPos.y -= MOVEMENT_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		v2fDeltaPos.x -= MOVEMENT_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		v2fDeltaPos.y += MOVEMENT_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		v2fDeltaPos.x += MOVEMENT_SPEED;

	if (v2fDeltaPos != sf::Vector2f(0, 0))
	{
		pPlayer->set_last_location(pPlayer->get_pos());
		pPlayer->move((pPlayer->get_pos() + v2fDeltaPos));

		/* Sync player */
		OnlineObject *tmpOnObj = new OnlineObject;
		tmpOnObj->iObjectID = iPlayerObjID;
		tmpOnObj->pObject = pPlayer;

commandMutex.lock();
		arrPendingCommands.push_back({SERVER_MSG_OBJ_MOD, tmpOnObj});
commandMutex.unlock();
	}

	Collision col;
	for(OnlineObject *pOnObect : arrLocalObjects){
		if(pOnObect->iObjectID == iPlayerObjID)
			continue;

		/* Don't collide with background */
		if (pOnObect->iObjectID == 0)
			continue;

		if(col.check_renderable_collision(pPlayer, pOnObect->pObject, false)){
			pPlayer->move(pPlayer->get_last_location());
		}
	}
}

void ClientState::get_client_ID(void) {
	char cBuff[64];
	std::size_t payloadLen;

	sprintf(cBuff, SERVER_COMM_HEADER_FORMAT, -1, SERVER_MSG_NEW_CLIENT);
	int iMsgLen = strlen(cBuff);
	TCPSocket.send(cBuff, iMsgLen);

	TCPSocket.receive(cBuff, 4, payloadLen);
	iClientID = *((int*) cBuff);
}

void ClientState::get_object_list(void) {
	char cBuff[8192] = { 0 };
	std::size_t payloadLen;

	sprintf(cBuff, SERVER_COMM_HEADER_FORMAT, iClientID,
			SERVER_MSG_GET_OBJECT_LIST);
	int iMsgLen = strlen(cBuff);
	TCPSocket.send(cBuff, iMsgLen);

	TCPSocket.receive(cBuff, 8192, payloadLen);

	char *pBuff = cBuff;
	if(payloadLen == 1){
		TCPSocket.send("NONO", 4);
		return;
	}

	/* Delete local objects */
	for (int i = iLevelElements; i < arrOnlineObjects.size();) {
		arrOnlineObjects.pop_back();
	}

	while (strlen(pBuff) > strlen(SERVER_OBJECT_FORMAT)) {
		int iID;
		float xPos, yPos;
		float xSiz, ySiz;
		float fRot;
		char texPath[128];

		sscanf(pBuff, SERVER_OBJECT_FORMAT, &iID, &xPos, &yPos, &xSiz, &ySiz,
				&fRot, texPath);

		OnlineObject *pOnlineObj = new OnlineObject;
		pOnlineObj->iObjectID = iID;
		pOnlineObj->pObject = GameObjectFactory::get_instance()->create_object(
				GAME_OBJECT_TYPE_UNSPECIFIED, { xPos, yPos }, { xSiz, ySiz },
				pGameData, texPath, fRot);

		objectMutex.lock();
		arrOnlineObjects.push_back(pOnlineObj);
		objectMutex.unlock();

		pBuff += strlen(pBuff) + 1;
	}

	TCPSocket.send("NONO", 4);
}

void ClientState::get_player(void) {
	char cBuff[64];
	std::size_t payloadLen;

	sprintf(cBuff, SERVER_COMM_HEADER_FORMAT, iClientID, SERVER_MSG_GET_PLAYER);
	int iMsgLen = strlen(cBuff);
	TCPSocket.send(cBuff, iMsgLen);

	TCPSocket.receive(cBuff, 4, payloadLen);

	iPlayerObjID = *((int*) cBuff);
}

#define MOD_HEADER "0,5\n"
#define MOD_HEADER_LEN 4
void ClientState::send_mod_object_to_server(OnlineObject *apGObj) {
	char cBuff[256];
	char nBuff[4];
	std::size_t payloadLen;
	int iMsgLen;

	TCPSocket.send(MOD_HEADER, MOD_HEADER_LEN);

	/* Parse objectNum, append data to end using pointer arithmetic */
	sprintf(cBuff, "%d,", apGObj->iObjectID);
	iMsgLen = strlen(cBuff);

	/* Wait ready */
	TCPSocket.receive(nBuff, 4, payloadLen);

	/* potentially dangerous race-condition */
	GameObjectFactory::get_instance()->dump_object(apGObj->pObject,
			cBuff + iMsgLen);
	iMsgLen = strlen(cBuff);

	TCPSocket.send(cBuff, iMsgLen);

	/* Wait until processed */
	TCPSocket.receive(cBuff, 4, payloadLen);
}

void ClientState::send_new_object_to_server(OnlineObject *apOnObj) {
	char cBuff[256];
	std::size_t payloadLen;

	sprintf(cBuff, SERVER_COMM_HEADER_FORMAT, iClientID, SERVER_MSG_OBJ_NEW);
	int iMsgLen = strlen(cBuff);
	TCPSocket.send(cBuff, iMsgLen);

	/* Wait ready */
	TCPSocket.receive(cBuff, 256, payloadLen);

	/* Parse objectNum, append data to end using pointer arithmetic */
	sprintf(cBuff, "%d,", apOnObj->iObjectID);
	iMsgLen = strlen(cBuff);

	GameObjectFactory::get_instance()->dump_object(apOnObj->pObject,
			cBuff + iMsgLen);
	iMsgLen = strlen(cBuff);

	TCPSocket.send(cBuff, iMsgLen);

	/* Response is new ID */
	TCPSocket.receive(cBuff, 4, payloadLen);
	apOnObj->iObjectID = *((int*) cBuff);
}

void ClientState::start_transaction(void) {
	TCPSocket.connect(SERVER_IP, SERVER_PORT_DEC);
}

void ClientState::end_transaction(void) {
	char cBuff[64];
	int  iMsgLen;
	std::size_t s;

	/* Send empty command, server will close connection. */
	sprintf(cBuff, SERVER_COMM_HEADER_FORMAT, iClientID, SERVER_MSG_NONE);
	iMsgLen = strlen(cBuff);
	TCPSocket.send(cBuff, iMsgLen);
}

void ClientState::send_pending_commands(std::vector<Command> *apCommands) {
	start_transaction();

	for(const Command &cmd : *apCommands){
		switch(cmd.eCmdType){
			case SERVER_MSG_NEW_CLIENT:
				get_client_ID();
				break;
			case SERVER_MSG_GET_OBJECT_LIST:
				get_object_list();
				break;
			case SERVER_MSG_GET_PLAYER:
				get_player();
				break;
			case SERVER_MSG_OBJ_NEW:
				send_new_object_to_server(cmd.pOnObj);
				break;
			case SERVER_MSG_OBJ_MOD:
				send_mod_object_to_server(cmd.pOnObj);
				break;
			case SERVER_MSG_OBJ_DEL:
				send_del_object_to_server(cmd.pOnObj);
				break;
			default:
				break;
		}

		char tmp[4];
		std::size_t s;
		TCPSocket.receive(tmp, 4, s);
	}

	apCommands->clear();

	end_transaction();
}

void ClientState::do_server_communication() {
	while(bRunCommThread) {
		std::vector<Command> arrTmp = {
				{SERVER_MSG_GET_OBJECT_LIST, nullptr},
				{SERVER_MSG_GET_PLAYER, nullptr}
		};

		std::chrono::time_point now = std::chrono::system_clock::now();
		std::chrono::time_point sendTime = now + std::chrono::milliseconds(100);
		while(now < sendTime) {
			if(!commandMutex.try_lock())
				if(!bRunCommThread)
					return;

			/* Only keep remove MOD commands as they cancel each other out */
			for(unsigned i = 0; i < arrPendingCommands.size(); i++)
			{
				if(arrPendingCommands[i].eCmdType == SERVER_MSG_OBJ_MOD)
					arrPendingCommands.erase(arrPendingCommands.begin() + i--);
			}
			commandMutex.unlock();

			now = std::chrono::system_clock::now();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(
				int(1000.0f/FPS_SECOND) + 1));

		commandMutex.lock();
		for(Command &cmd : arrPendingCommands)
			arrTmp.push_back(cmd);

		arrPendingCommands.clear();
		commandMutex.unlock();

		send_pending_commands(&arrTmp);
	}
}

void ClientState::send_del_object_to_server(OnlineObject *apOnObj) {
	char cBuff[256];
	std::size_t payloadLen;

	sprintf(cBuff, SERVER_COMM_HEADER_FORMAT, iClientID, SERVER_MSG_OBJ_DEL);
	int iMsgLen = strlen(cBuff);
	TCPSocket.send(cBuff, iMsgLen);

	/* Wait ready */
	TCPSocket.receive(cBuff, 256, payloadLen);

	/* Only object id will suffice */
	TCPSocket.send(&apOnObj->iObjectID, sizeof(int));
}
