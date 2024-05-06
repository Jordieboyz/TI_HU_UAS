/*
 * Character.cpp
 *
 *  Created on: 11 Jan 2021
 *      Author: lucasw00079
 */

#include "game-objects/Character.hpp"
#include "game-objects/Bullet.hpp"

//#define DEBUG

Character::Character(sf::Vector2f av2fPos, sf::Vector2f av2fSize,
		WeaponStats* apWeapon, GameData *pGameData):
	GameObject(av2fPos, av2fSize, "res/sprPlayerHeavyAttack.png", pGameData),
	timer(),
	parrAnimations(apWeapon->pWeapon->pAnimationData),
	pCurrentWeapon(apWeapon)
{
}

Character::~Character() {
}

/* Shedule move, only move once a frame,
 * increases movement smoothness.
 */
void Character::move(sf::Vector2f av2fPos) {
	bIsMoving = true;
	v2fPos = av2fPos;
}

void Character::update() {

	update_texture();
	update_rotation();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !bIsShooting) {
		shoot();
	}

	std::for_each(vFiredBullets.begin(), vFiredBullets.end(), [](Bullet* pBullet) { pBullet->update(); });

	sf::Sprite  tmpSprite;

	/* Sprite should rotate around centre */
	/* Todo: when scaling to v2size, use v2size */

	sf::Vector2u v2uTmpTexSize = texture.getSize();
	tmpSprite.setOrigin(v2uTmpTexSize.x / 2.0f, v2uTmpTexSize.y / 2.0f);

	tmpSprite.setRotation(fRotation);
	tmpSprite.setTexture(texture);
	tmpSprite.setPosition(v2fPos + (v2fSize / 2.0f));
	tmpSprite.setScale(v2fscale);

#ifdef DEBUG
	sf::RectangleShape rsDebugRect;
	rsDebugRect.setPosition(v2fPos);
	rsDebugRect.setSize(v2fSize);
	rsDebugRect.setFillColor(sf::Color{ 0, 0, 0, 0 });
	rsDebugRect.setOutlineThickness(1);
	rsDebugRect.setOutlineColor(sf::Color{ 255, 0, 0 });

	sf::CircleShape csDebugCircle;
	csDebugCircle.setRadius(5.0f);
	csDebugCircle.setOrigin(sf::Vector2f(5.0f, 5.0f));
	csDebugCircle.setPosition(tmpSprite.getOrigin() + tmpSprite.getPosition());
	csDebugCircle.setFillColor(sf::Color{ 0, 0, 255 });

	if(pData->pRenderWindow != nullptr)
		pData->pRenderWindow->draw(csDebugCircle);
	if(pData->pRenderWindow != nullptr)
		pData->pRenderWindow->draw(rsDebugRect);
#endif

	std::for_each(vFiredBullets.begin(), vFiredBullets.end(), [](Bullet* pBullet) { pBullet->update(); });
	if(pData->pRenderWindow != nullptr)
		pData->pRenderWindow->draw(tmpSprite);
	bIsMoving = false;
	shootSound.update_speed();

}

void Character::update_texture(void) {
	unsigned uAnimationIndex = (bDead) ? (ANIMATION_TYPE_DEAD) :
				(bIsShooting) ? (ANIMATION_TYPE_SHOOTING) :
				((bIsMoving) ? (ANIMATION_TYPE_MOVING) : (ANIMATION_TYPE_IDLE));

	/* Change animation, reset animation timer */
	if(uAnimationIndex != uCurrAnimation)
	{
		fAcc = 0.0f;
		uCurrAnimation = uAnimationIndex;
	}

	/* Pointer don't copy */
	const AnimationData pAnimation = parrAnimations[uAnimationIndex];

	float fElapsedSeconds = timer.getElapsedTime().asSeconds() * pData->fTimeScaleFactor;

	float fTmp = (fElapsedSeconds + fAcc) / pAnimation.fDuration;
	fAcc = fTmp;
	if(fTmp >= 1.0f)
	{
		fAcc = 0.0f;
		timer.restart();
	}

	unsigned uImageIndex = fAcc * (pAnimation.uNumImages);

	/* TODO: This is bad*/
	if (uAnimationIndex == (unsigned)ANIMATION_TYPE_IDLE) { uImageIndex = 0; };

	unsigned uImageIndexX = uImageIndex % pAnimation.uNumImagesX;
	unsigned uImageIndexY = uImageIndex / pAnimation.uNumImagesX;

	/* We'll need image date to calculate area. */
	sf::Image tmpImage;
	tmpImage.loadFromFile(pAnimation.strImagePath);
	sf::Vector2u v2uImgSize = tmpImage.getSize();
	sf::Vector2u v2uSpriteSegmentSize = {v2uImgSize.x / pAnimation.uNumImagesX,
										 v2uImgSize.y / pAnimation.uNumImagesY};

	v2fscale = sf::Vector2f( (v2fSize.x / sf::Vector2f(v2uSpriteSegmentSize).x) ,
						   (v2fSize.y / sf::Vector2f(v2uSpriteSegmentSize).y) );

	v2fscale = sf::Vector2f( (v2fSize.x / sf::Vector2f(v2uSpriteSegmentSize).x) ,
						   (v2fSize.y / sf::Vector2f(v2uSpriteSegmentSize).y) );

	sf::Vector2u v2uSpriteOffset = {v2uSpriteSegmentSize.x * uImageIndexX,
									v2uSpriteSegmentSize.y * uImageIndexY};

	sf::Rect<int> area(v2uSpriteOffset.x, v2uSpriteOffset.y,
			v2uSpriteSegmentSize.x, v2uSpriteSegmentSize.y);

	texture.loadFromImage(tmpImage, area);

	/* Clear shoot flag if whole animation is shown. */
	if(bIsShooting && fTmp >= 1.0f)
		bIsShooting = false;
}

void Character::update_rotation(void){
}

bool Character::shoot(void) {
	if(!bIsShooting){
		bIsShooting = true;
		pCurrentWeapon->pWeapon->sound.play_sound_file();
		pData->pParticleManager->add_particle({ 
			&ANIMATION_MUZZLE_FLASH, v2fPos + v2fSize / 2.0f, {105, 20}, fRotation, false });
		for (unsigned int i = 0; i < pCurrentWeapon->pWeapon->uintBulletsFired; i++){
			vFiredBullets.push_back(new Bullet(this, pData, "res/laser.png"));
		}
		return true;
	}
	return false;
}



float Character::get_rotation(void){
	return fRotation;
}

std::vector<Bullet*>* Character::get_fired_bullets(){
	return &vFiredBullets;
}

Weapon* Character::get_Weapon(void){
	return pCurrentWeapon->pWeapon;
}

void Character::set_Weapon(WeaponStats* const aWeapon){
	pCurrentWeapon = aWeapon;
	voice.play_voice_line_player();
	parrAnimations = pCurrentWeapon->pWeapon->pAnimationData;
}

const WeaponStats* Character::drop_weapon()
{
	//drop old weapon to ground
	pCurrentWeapon->pWeapon->set_used(false);
	pCurrentWeapon->pWeapon->move(v2fPos);
	return pCurrentWeapon;
}


void Character::shot() {
	shot_action();
	bDead = true;
	bIsCollidable = false;

	drop_weapon();
}

void Character::shot_action(void) {
}

bool Character::get_bDead() {
	return bDead;
}
