/*
 * Enemy.cpp
 *
 *  Created on: 18 Jan 2021
 *      Author: Milo
 */

#include "game-objects/Enemy.hpp"

#include "MapData.hpp"

#include <cmath>

#define DEG_TO_RAD(DEG)\
	(DEG * (PI / 180.0f))

enum MOVEMENT_DIRECTION
{
	MOVEMENT_DIRCETION_START,
	MOVEMENT_DIRCETION_LEFT,
	MOVEMENT_DIRCETION_RIGHT,
	MOVEMENT_DIRCETION_UP,
	MOVEMENT_DIRCETION_DOWN,
	MOVEMENT_NUM_DIRECTIONS
};

sf::Vector2u Deltas[MOVEMENT_NUM_DIRECTIONS] =
{
		sf::Vector2u(0,0),
		sf::Vector2u(1,0),
		sf::Vector2u(-1,0),
		sf::Vector2u(0,1),
		sf::Vector2u(0,-1)
};

struct Item
{
		sf::Vector2u coord;
		enum MOVEMENT_DIRECTION eDirection;
};


Enemy::Enemy(sf::Vector2f av2fPos, sf::Vector2f av2fSize,
		     WeaponStats* apWeapon, GameData *pGameData, std::vector<sf::Vector2f> aVecV2Path):
	Character(av2fPos, av2fSize, apWeapon, pGameData),
	vPath(aVecV2Path)
{
	//Makes sure the enemy takes the same way back
	int size = vPath.size();
	for(unsigned int i = size-1; i > 0; i--){
		vPath.push_back(vPath[i]);
	}
}

void Enemy::update() {
	fSpeed = NPC_MOVEMENT_SPEED * pData->fTimeScaleFactor;

	switch(eState){
		case NPC_STATE_PATROL:
			eState = patrol_handler();
			break;
		case NPC_STATE_RETURN:
			eState = return_handler();
			break;
		case NPC_STATE_ALERT:
			voice.play_voice_line_enemy(eState == NPC_STATE_ALERT);
			eState = alert_handler();
			break;
		case NPC_STATE_DEAD:
			eState = dead_handler();
			break;
		default:
			eState = NPC_STATE_PATROL;
			break;
	};

	update_texture();
	sf::Sprite  tmpSprite;

	sf::Vector2u v2uTmpTexSize = texture.getSize();
	tmpSprite.setOrigin(v2uTmpTexSize.x / 2.0f, v2uTmpTexSize.y / 2.0f);

	tmpSprite.setRotation(fRotation);
	tmpSprite.setTexture(texture);
	tmpSprite.setPosition(v2fPos + (v2fSize / 2.0f));
	tmpSprite.setScale(v2fscale);

	std::for_each(vFiredBullets.begin(), vFiredBullets.end(), [](Bullet* pBullet) { pBullet->update(); });
	pData->pRenderWindow->draw(tmpSprite);
	bIsMoving = false;
}

void Enemy::follow_path(sf::Vector2f dest, float speed) {

	if( check_y_margin(dest) ){
		//Horizontal Movement
		if( v2fPos.x < dest.x ){
			//Move east
			v2fPos.x += speed;
		} else if( v2fPos.x > dest.x ){
			//Move west
			v2fPos.x -= speed;
		}
	} else if ( check_x_margin(dest) ){
		//Vertical Movement
		if( v2fPos.y < dest.y ){
			//Move south
			v2fPos.y += speed;
		} else if( v2fPos.y > dest.y ){
			//Move north
			v2fPos.y -= speed;
		}
	} else {
		//Diagonal Movement
		if( dest.x < v2fPos.x && dest.y < v2fPos.y){
			//Move North West
			v2fPos += sf::Vector2f(-speed, -speed);
		} else if( dest.x > v2fPos.x && dest.y > v2fPos.y ){
			//Move South East
			v2fPos += sf::Vector2f(speed, speed);
		} else if( dest.x < v2fPos.x &&  dest.y > v2fPos.y){
			//Move South West
			v2fPos += sf::Vector2f(-speed, speed);
		} else if( dest.x > v2fPos.x && dest.y < v2fPos.y){
			//Move North East
			v2fPos += sf::Vector2f(speed, -speed);
		}
	}
}

bool Enemy::check_destination_margin(sf::Vector2f dest, unsigned int margin) {
	sf::FloatRect rect = {dest.x-margin, dest.y-margin, (float)margin*2, (float)margin*2};
	return (rect.contains(v2fPos)) ? true : false;
}

bool Enemy::check_y_margin(sf::Vector2f dest, unsigned int margin){
	return (v2fPos.y+margin > dest.y && v2fPos.y-margin < dest.y) ? true : false;
}

bool Enemy::check_x_margin(sf::Vector2f dest, unsigned int margin){
	return (v2fPos.x+margin > dest.x && v2fPos.x-margin < dest.x) ? true : false;
}

bool Enemy::check_clear_line_of_sight() {

#ifdef DEBUG
	sf::Vertex line[] =
	{
	    sf::Vertex(sf::Vector2f(v2fPos.x + (v2fSize.x/2), v2fPos.y + (v2fSize.y/2))),
	    sf::Vertex(sf::Vector2f(pData->pPlayer->get_pos().x + (pData->pPlayer->get_size().x /2),
	    						pData->pPlayer->get_pos().y + (pData->pPlayer->get_size().y /2)))
	};

	pData->pRenderWindow->draw(line, 2, sf::Lines); //Debugging only
#endif

	int range = 900;
	if( ((int)(pData->pPlayer->get_pos().y - v2fPos.y) < range && (int)(pData->pPlayer->get_pos().y - v2fPos.y) > -range) ||
		((int)(pData->pPlayer->get_pos().x - v2fPos.x) < range && (int)(pData->pPlayer->get_pos().x - v2fPos.x) > -range) ){

		/* TODO: use origin, requires adjustments to maps */
//		sf::Vector2f vec2fOrigin = v2fPos + v2fSize/2.0f;

		for(float i = fRotation - NPC_H_FOV; i < fRotation + NPC_H_FOV; i+=2){
			for(int j = 0; j < range; j += 32){
				sf::Vector2f vec2fScanLine = { 	(float)cos(DEG_TO_RAD(i)),
												(float)sin(DEG_TO_RAD(i))};

				sf::Vector2f vec2fCurr = v2fPos + (float)j * vec2fScanLine;

				/* Check whether object exist on line of sight */
				if(vec2fCurr.x < 0.0f || vec2fCurr.y < 0.0f)
					continue;

				if(MAP_GET_MAP_POS(pData->mapData, ((int)vec2fCurr.x), ((int)vec2fCurr.y)))
					break;

				/* Check whether player has been reached */
				if(((int)vec2fCurr.x >> LOG2_COMPRESSION) == ((int)pData->pPlayer->get_pos().x >> LOG2_COMPRESSION))
					if(((int)vec2fCurr.y >> LOG2_COMPRESSION) == ((int)pData->pPlayer->get_pos().y >> LOG2_COMPRESSION))
						return true;
#ifdef DEBUG
				sf::CircleShape tmpC(2);
				tmpC.setFillColor(sf::Color::Yellow);
				tmpC.setPosition(vec2fCurr);
				pData->pRenderWindow->draw(tmpC);
#endif
				}
		}

		return false;
	} else {
		return false;
	}
}

void Enemy::update_path_to_point_of_interest(sf::Vector2f av2fOrigin,
		sf::Vector2f av2fTarget) {
	/* TODO: Add point of interest */
	sf::Vector2u vec2uTarget(av2fTarget.x,
			av2fTarget.y);

	vec2uTarget.x >>= LOG2_COMPRESSION;
	vec2uTarget.y >>= LOG2_COMPRESSION;

	sf::Vector2u vec2uOrigin(av2fOrigin.x, av2fOrigin.y);
	vec2uOrigin.x >>= LOG2_COMPRESSION;
	vec2uOrigin.y >>= LOG2_COMPRESSION;

	std::vector<struct Item> items = {{vec2uTarget, MOVEMENT_DIRCETION_START}};

	unsigned uCurrIndex;
	unsigned uMapX = pData->mapData.uMapX;
	unsigned uMapY = pData->mapData.uMapY;
	for(uCurrIndex = 0; uCurrIndex < items.size(); uCurrIndex++)
	{
		struct Item curr = items[uCurrIndex];
		if(curr.coord == vec2uOrigin)
		{
			/* Create path */
			vPlayerPath.clear();
			struct Item curr = items[uCurrIndex];
			while(curr.eDirection != MOVEMENT_DIRCETION_START){
				sf::Vector2u prevCoord = curr.coord - Deltas[curr.eDirection];
				for(int i = uCurrIndex; i >= 0; i--){
					if(items[i].coord == prevCoord){
						uCurrIndex = i;
						break;
					}
				}
				enum MOVEMENT_DIRECTION eLastDir = curr.eDirection;
				curr = items[uCurrIndex];

				if(eLastDir != curr.eDirection)
					vPlayerPath.push_back({(float)(curr.coord.x << LOG2_COMPRESSION), (float)(curr.coord.y << LOG2_COMPRESSION)});
			}
			return;
		}

		for(unsigned i = 1; i < MOVEMENT_NUM_DIRECTIONS; i++){
			struct Item Neighbour = {(sf::Vector2u)(curr.coord + Deltas[(enum MOVEMENT_DIRECTION)i]), (enum MOVEMENT_DIRECTION)i};

			/* Less than zero results in overflow */
			if(Neighbour.coord.y > uMapY or Neighbour.coord.x > uMapX)
				continue;

			if(!MAP_GET_MAP_POS_ADJUSTED_INPUT(pData->mapData,
					Neighbour.coord.x, Neighbour.coord.y)){

				auto l = [&Neighbour](const struct Item &in){
					return (in.coord == Neighbour.coord);
				};

				if(!std::any_of(items.begin(), items.end(), l))
					items.push_back(Neighbour);
			}
		}
	}
}

enum NPC_STATE Enemy::patrol_handler(void) {
	enum NPC_STATE eRetVal = NPC_STATE_PATROL;
	sf::Vector2f v2fDest = sf::Vector2f{vPath[uCurrentDest]};
	update_rotation(v2fDest);

#ifdef DEBUG
	sf::CircleShape tmpC(8);
	tmpC.setFillColor(sf::Color::Blue);
	for(sf::Vector2f &a : vPath){
		tmpC.setPosition(a);
		pData->pRenderWindow->draw(tmpC);
	}
#endif

	if( check_destination_margin(v2fDest) ){
		uCurrentDest++;
		if(uCurrentDest == vPath.size())
			uCurrentDest = 0;
	}

	if(check_clear_line_of_sight()){
		eRetVal = NPC_STATE_ALERT;
		update_path_to_point_of_interest(v2fPos, pData->pPlayer->get_pos());
		uPlayerPathDest = 0;
	}

	int tmp = listen();
	if(tmp != -1)
		eRetVal =(enum NPC_STATE)(tmp);

	follow_path(v2fDest, fSpeed);

	return eRetVal;
}

enum NPC_STATE Enemy::return_handler(void) {
	enum NPC_STATE eRetVal = NPC_STATE_RETURN;
	sf::Vector2f v2fDest = sf::Vector2f{vPlayerPath[uPlayerPathDest]};
	update_rotation(v2fDest);

#ifdef DEBUG
	sf::CircleShape tmpC(8);
	tmpC.setFillColor(sf::Color::Green);
	for(sf::Vector2f &a : vPlayerPath){
		tmpC.setPosition(a);
		pData->pRenderWindow->draw(tmpC);
	}
#endif

	if( check_destination_margin(v2fDest) ){
		uPlayerPathDest++;
		if(uPlayerPathDest == vPlayerPath.size()){
			uCurrentDest = 0;
			eRetVal = NPC_STATE_PATROL;
		}
	}

	if(check_clear_line_of_sight()){
		eRetVal = NPC_STATE_ALERT;
		update_path_to_point_of_interest(v2fPos, pData->pPlayer->get_pos());
		uPlayerPathDest = 0;
	}

	int tmp = listen();
	if(tmp != -1)
		eRetVal =(enum NPC_STATE)(tmp);

	follow_path(v2fDest, fSpeed);

	return eRetVal;
}

enum NPC_STATE Enemy::alert_handler(void) {
	enum NPC_STATE eRetVal = NPC_STATE_ALERT;

	if(vPlayerPath.empty())
		return NPC_STATE_PATROL;

	sf::Vector2f v2fDest = sf::Vector2f{vPlayerPath[uPlayerPathDest]};
	update_rotation(pData->pPlayer->get_pos());

#ifdef DEBUG
	sf::CircleShape tmpC(8);
	tmpC.setFillColor(sf::Color::Red);
	for(sf::Vector2f &a : vPlayerPath){
		tmpC.setPosition(a);
		pData->pRenderWindow->draw(tmpC);
	}
#endif

	if(check_clear_line_of_sight()){
		shoot();
		update_path_to_point_of_interest(v2fPos, pData->pPlayer->get_pos());
		uPlayerPathDest = (vPlayerPath.size() == 1) ? 0 : 1;
	}

	if( check_destination_margin(v2fDest, 10) ){
		uPlayerPathDest++;
		if(uPlayerPathDest == vPlayerPath.size()){
			eRetVal = NPC_STATE_RETURN;
			uPlayerPathDest = 0;
			update_path_to_point_of_interest(v2fPos, vPath[uCurrentDest]);
		}
	}

//	int tmp = listen();
//	if(tmp != -1)
//		eRetVal =(enum NPC_STATE)(tmp);

	follow_path(v2fDest, fSpeed);

	return eRetVal;
}

void Enemy::update_rotation(sf::Vector2f av2fTarget) {
	sf::Vector2f v2fDirection = {av2fTarget.x - (v2fPos.x ),
								av2fTarget.y - (v2fPos.y )};

	fRotation = (180.0f/PI) * std::atan(v2fDirection.y / v2fDirection.x);
	if (v2fDirection.x < 0.0f)
		fRotation += 180.0f;
}

enum NPC_STATE Enemy::dead_handler(void) {
	return NPC_STATE_DEAD;
}

void Enemy::shot_action() {
	if(eState != NPC_STATE_DEAD){
		eState = NPC_STATE_DEAD;
		ParticleData tmpPart = {&ANIMATION_BULLET_IMPACT,
				v2fPos, v2fSize*2.0f, fRotation, true};

		ParticleData pointPart {&ANIMATION_POINTS, v2fPos,
			{725, 408}, ((fRotation >= 180.0f) ? (fRotation - 180.0f) :
					(fRotation)), false};

		pData->pParticleManager->add_particle(tmpPart);
		pData->pParticleManager->add_particle(pointPart);
	}
}

int Enemy::listen(void) {
	int iRetVal = -1;

	if(pData->pPlayer->bIsShooting)
	{
		sf::Vector2f vec2fPlayer = pData->pPlayer->get_pos();
		float fDist = pow(v2fPos.x - vec2fPlayer.x + v2fPos.y - vec2fPlayer.y, 2);
		if(fDist < 1440000)
		{
			iRetVal = NPC_STATE_ALERT;
			update_path_to_point_of_interest(v2fPos, pData->pPlayer->get_pos());
			uPlayerPathDest = 0;
		}
	}

	return iRetVal;
}
