#include "Weapon.hpp"

Weapon::Weapon(sf::Vector2f av2fPos, const char* astrTexturePath, GameData* apGameData, 
	const float afBulletVelocity, const float afBulletSpreadDegreesMax,
	const unsigned int auintBulletsFired, const AnimationData* apAnimationData, std::string filepath)
	:
	GameObject(av2fPos, sf::Vector2f{ 80.f, 60.f }, astrTexturePath, apGameData),
	fBulletVelocity(afBulletVelocity),
	fBulletSpreadDegreesMax(afBulletSpreadDegreesMax),
	uintBulletsFired(auintBulletsFired),
	pAnimationData(apAnimationData),
	sound(filepath)
{}

void Weapon::update(){
	if (!bIsUsed) {
		GameObject::update();
	}
}
