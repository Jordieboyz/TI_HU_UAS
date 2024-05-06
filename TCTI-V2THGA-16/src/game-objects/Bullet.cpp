#include "game-objects/Bullet.hpp"

//#define DEBUG

Bullet::Bullet(Character* apShooter, GameData* apGameData, const char* astrTexturePath) :
	GameObject(sf::Vector2f{}, sf::Vector2f{BULLET_SIZE, BULLET_SIZE }, astrTexturePath, apGameData),
	pShooter(apShooter),
	fBulletVelocity(apShooter->get_Weapon()->fBulletVelocity)
{
	const float fBulletSpreadDegreesMax =  apShooter->get_Weapon()->fBulletSpreadDegreesMax;

	//calculating random spread
	float fTotalSpread = ((((float)rand()) / (float)RAND_MAX) * (fBulletSpreadDegreesMax * 2)) - fBulletSpreadDegreesMax;
	float fTmpShooterRotation = pShooter->get_rotation() + fTotalSpread;

	//set origin to middle, then move to center of character
	sprite.setOrigin(sf::Vector2f{ BULLET_SIZE, BULLET_SIZE } / 2.f);
	move(pShooter->get_pos() + (pShooter->get_size() / 2.0f));
	sprite.setRotation(fTmpShooterRotation);

	//convert to radians from degrees, follow unit circle for movement speed multiplier
	v2fSpeed.x = std::cos((fTmpShooterRotation * PI) / 180.f);
	v2fSpeed.y = std::sin((fTmpShooterRotation * PI) / 180.f);

	//calculate bullet speed
	v2fSpeed *= fBulletVelocity;
}

void Bullet::update(void){
    move((v2fSpeed * pData->fTimeScaleFactor) + v2fPos);
	if(pData->pRenderWindow != nullptr)
		pData->pRenderWindow->draw(sprite);

#ifdef DEBUG
	sf::RectangleShape rsDebugRect;
	rsDebugRect.setPosition(v2fPos);
	rsDebugRect.setSize(v2fSize);
	rsDebugRect.setFillColor(sf::Color{ 0, 0, 0, 0 });
	rsDebugRect.setOutlineThickness(1);
	rsDebugRect.setOutlineColor(sf::Color{ 255, 0, 0 });

	sf::CircleShape csDebugCircle;
	csDebugCircle.setRadius(2.0f);
	csDebugCircle.setOrigin(sf::Vector2f(2.0f, 2.0f));
	csDebugCircle.setPosition(sprite.getOrigin() + sprite.getPosition());
	csDebugCircle.setFillColor(sf::Color{ 0, 0, 255 });
	if(pData->pRenderWindow != nullptr)
		pData->pRenderWindow->draw(rsDebugRect);
	if(pData->pRenderWindow != nullptr)
		pData->pRenderWindow->draw(csDebugCircle);
#endif
}
