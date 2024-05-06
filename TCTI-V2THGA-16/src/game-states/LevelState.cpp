/*
 * LevelState.cpp
 *
 *  Created on: 21 Jan 2021
 *      Author: Milo
 */

#include "game-states/LevelState.hpp"
#include "game-states/WinState.hpp"

LevelState::LevelState(struct GameData *apGameData, sf::Vector2f v2PlayerLocation,
					   const char* sBackgroundFilePath, const char* sWallFilePath,
					   const char * astrName) :
	GameState(apGameData, astrName)
{
	ObjectGenerator objGenerator(sWallFilePath, apGameData);
	
	//Load all invisible walls
	while(true){
		GameObject *pObj = objGenerator.generate_object(GAME_OBJECT_TYPE_WALL,
				WALL_GENERATOR_COL_TO_SEARCH);
		if(pObj == nullptr)
			break;

		walls.push_back(pObj);
	}

	//Load all actual walls
	while(true){
		GameObject *pObj = objGenerator.generate_object(GAME_OBJECT_TYPE_BARRIER,
				WALL_GENERATOR_COL_BARRIER);
		if(pObj == nullptr)
			break;

		walls.push_back(pObj);
	}

	if (std::string(sBackgroundFilePath) == "res/background4.png"){
		gameTime = 100000;
	}

	if (std::string(sBackgroundFilePath) == "res/background5.png"){
		gameTime = 30000;
	}
	//Load all the windows
	while(true){
		GameObject *pObj = objGenerator.generate_object(GAME_OBJECT_TYPE_GLASS,
				WALL_GENERATOR_COL_GLASS);
		if(pObj == nullptr)
			break;

		walls.push_back(pObj);
	}

	backgroundTexture.loadFromFile(sBackgroundFilePath);
	background.setTexture(backgroundTexture);

	backgroundMusic.play_music_file();
	pGameData->pPlayer = new Player(v2PlayerLocation, sf::Vector2f{64,64}, new WeaponStats({ 0, 0 }, pGameData, MP5), pGameData);
	clock.restart();
}

void LevelState::update() {
	pGameData->pRenderWindow->draw(background);

	currView.setCenter(pGameData->pPlayer->get_pos() + pGameData->pPlayer->get_size() / 2.0f);
	pGameData->pRenderWindow->setView(currView);
	iGameScore = (gameTime - clock.getElapsedTime().asMilliseconds())/10;
	if(iGameScore >= 0){
	scoreText.setString(std::to_string(iGameScore));
	scoreText.setPosition(pGameData->pPlayer->get_pos().x - 550,pGameData->pPlayer->get_pos().y - 300);
	pGameData->pRenderWindow->draw(scoreText);
	}
	pGameData->pParticleManager->update();
	std::vector<Bullet*> *vFiredBullets = pGameData->pPlayer->get_fired_bullets();


	//Check Player Bullets
	for(auto & object : walls){
		object->update();
		if(object->get_is_collidable() == false){
			continue;
		}
		col.handle_player_collision(pGameData->pPlayer, object);
		for (unsigned int i = 0; i < (vFiredBullets->size()); i++) {
			if (col.check_renderable_collision(vFiredBullets->at(i), object, -8, false)) {
				Bullet* bCollidedBullet = vFiredBullets->at(i);
				pGameData->pParticleManager->add_particle(
						{&ANIMATION_EXPLOSION,
						bCollidedBullet->get_pos(),{175,175}, 0, false});
				vFiredBullets->erase(vFiredBullets->begin() + i);
				object->shot();
				delete bCollidedBullet;
				return;
			}
		}
	}

	//Check if enemy got shot
	for (unsigned int i = 0; i < vFiredBullets->size(); i++) {
		for(auto enemy : enemies){
			if(enemy->get_is_collidable() == false){
				continue;
			}
			if (col.check_renderable_collision(vFiredBullets->at(i), enemy, -10.f, false)) {
				Bullet* bCollidedBullet = vFiredBullets->at(i);
				pGameData->pParticleManager->add_particle(
						{&ANIMATION_EXPLOSION,
						bCollidedBullet->get_pos(),{175,175}, 0, false});
				vFiredBullets->erase(vFiredBullets->begin() + i);
				enemy->shot();
				enemy->drop_weapon();
				delete bCollidedBullet;
				return;
			}
		}
	}

	//Check enemies bullets
	if(enemies.size() != 0){
		for(auto enemy : enemies){
		std::vector<Bullet*>* vFiredBulletss = enemy->get_fired_bullets();
			for(auto & object : walls){
				object->update();
				if(object->get_is_collidable() == false){
					continue;
				}
				for (unsigned int i = 0; i < vFiredBulletss->size(); i++) {
					if (col.check_renderable_collision(vFiredBulletss->at(i), object, -10.f, false)) {
						Bullet* bCollidedBullet = vFiredBulletss->at(i);
						pGameData->pParticleManager->add_particle(
								{&ANIMATION_EXPLOSION,
								bCollidedBullet->get_pos(),{175,175}, 0, false});
						vFiredBulletss->erase(vFiredBulletss->begin() + i);
						object->shot();
						delete bCollidedBullet;
						return;
					}
				}
			}
			//Check if the player got shot
			for (unsigned int i = 0; i < vFiredBulletss->size(); i++) {
				if (col.check_renderable_collision(vFiredBulletss->at(i), pGameData->pPlayer, -10.f, false)) {
					Bullet* bCollidedBullet = vFiredBulletss->at(i);
					pGameData->pParticleManager->add_particle(
							{&ANIMATION_EXPLOSION,
							bCollidedBullet->get_pos(),{175,175}, 0, false});
					vFiredBulletss->erase(vFiredBulletss->begin() + i);
					pGameData->pPlayer->shot();
					delete bCollidedBullet;
					return;
				}
			}
		}
	}

	std::for_each(arrWeaponInLevel.begin(), arrWeaponInLevel.end(), [](WeaponStats& weapon) { weapon.pWeapon->update(); });
	pGameData->pPlayer->update();
	backgroundMusic.update_speed();

	unsigned uDead = 0;
	if(enemies.size() != 0){
		for(auto enemy : enemies){
			enemy->update();
			if(enemy->get_bDead()){
				uDead++;
				if((int)uDead > enemyCount){
					gameTime += 1000;
					enemyCount = uDead;
				}
			}
		}
	}

	if(uDead == enemies.size()) {
		currView.setCenter(sf::Vector2f(WINDOW_LENGTH, WINDOW_HEIGHT)/2.0f);
		pGameData->pRenderWindow->setView(currView);
		pGameData->pStateMachine->set_state(new WinState(pGameData,(iGameScore + enemyCount * 100),enemyCount,iGameScore, gameTime));
	}

	if(iGameScore <= 0 || pGameData->pPlayer->get_bDead() == true){
		currView.setCenter(sf::Vector2f(WINDOW_LENGTH, WINDOW_HEIGHT)/2.0f);
		pGameData->pRenderWindow->setView(currView);
		pGameData->pStateMachine->set_state(new GameOverState(pGameData, uDead));
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)){
		currView.reset({0.f, 0.f, WINDOW_LENGTH, WINDOW_HEIGHT});
		pGameData->pRenderWindow->setView( currView );
		sf::Image image = take_screenshot();
		pGameData->pStateMachine->set_state(new PauseMenuState(pGameData, &image));
	}
}

void LevelState::handle_input() {
	sf::Vector2f v2fDeltaPos = {0.0f, 0.0f};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		v2fDeltaPos.y -= MOVEMENT_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		v2fDeltaPos.x -= MOVEMENT_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		v2fDeltaPos.y += MOVEMENT_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		v2fDeltaPos.x += MOVEMENT_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
		for (WeaponStats& weapon : arrWeaponInLevel){
			if (col.check_renderable_collision(pGameData->pPlayer, weapon.pWeapon, 10.f, false) && !weapon.pWeapon->is_used()){

					//drop old weapon to ground
					pGameData->pPlayer->drop_weapon();

					//give player new weapon
					pGameData->pPlayer->set_Weapon(&weapon);
					weapon.pWeapon->set_used(true);
					break;
			}
		}
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
		if( pGameData->pPlayer->shoot() ){
			fInitialTimeScaleParamter -= TIME_SCALE_PAR_INC_SHOOT;
			if(fInitialTimeScaleParamter <= 1.0f)
				fInitialTimeScaleParamter = 1.0f;
		}
	}

	if(v2fDeltaPos != sf::Vector2f(0,0)){
		fInitialTimeScaleParamter -= TIME_SCALE_PAR_INC_MOVE_SEC;
		if(fInitialTimeScaleParamter <= 1.0f)
			fInitialTimeScaleParamter = 1.0f;
		pGameData->pPlayer->set_last_location( pGameData->pPlayer->get_pos() );
		pGameData->pPlayer->move(pGameData->pPlayer->get_pos() + (v2fDeltaPos * pGameData->fTimeScaleFactor));
	}
	else{
		fInitialTimeScaleParamter += TIME_SCALE_INC_UPDATE;
		if(fInitialTimeScaleParamter > TIME_SCALE_PAR_INC_SEC)
			fInitialTimeScaleParamter = TIME_SCALE_PAR_INC_SEC;
	}

	pGameData->fTimeScaleFactor = 1 / fInitialTimeScaleParamter;
}

sf::Image LevelState::take_screenshot(){
	sf::Texture texture;
	texture.create(WINDOW_LENGTH, WINDOW_HEIGHT);
	texture.update(*pGameData->pRenderWindow);
	sf::Image screen;
	screen = texture.copyToImage();
	return screen;
}
