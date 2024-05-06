#include "game-objects/Door.hpp"

Door::Door(sf::Vector2f av2fPos, sf::Vector2f av2fSize, const char* astrTexturePath, GameData* apGameData, bool abPositiveRotation) :
	GameObject(av2fPos, av2fSize, astrTexturePath, apGameData),
	bPositiveRotation(abPositiveRotation)
{
	sprite.setOrigin(sf::Vector2f{ (float)texture.getSize().y, (float)texture.getSize().y } / 2.f);

	//minimum of 4 vertices for corners
	varrCollisionPoints.push_back(sf::Vertex{ av2fPos, sf::Color{255, 0, 0} });
	varrCollisionPoints.push_back(sf::Vertex{ {av2fPos.x, av2fPos.y + av2fSize.y}, sf::Color{255, 0, 0} });
	varrCollisionPoints.push_back(sf::Vertex{ (av2fPos + av2fSize), sf::Color{255, 0, 0} });
	varrCollisionPoints.push_back(sf::Vertex{ {av2fPos.x + av2fSize.x, av2fPos.y}, sf::Color{255, 0, 0} });

	//add vertice every 8 pixels for x axis
	for (float x = av2fPos.x; x < (av2fPos.x + av2fSize.x); x += 8) {
		varrCollisionPoints.push_back(sf::Vertex{ {x, av2fPos.y}, sf::Color{255, 0, 0} });
		varrCollisionPoints.push_back(sf::Vertex{ {x, (av2fPos.y + av2fSize.y)}, sf::Color{255, 0, 0} });
	}
	for (float y = av2fPos.y; y < (av2fPos.y + av2fSize.y); y += 8) {
		varrCollisionPoints.push_back(sf::Vertex{ {av2fPos.x, y}, sf::Color{255, 0, 0} });
		varrCollisionPoints.push_back(sf::Vertex{ {(av2fPos.x + av2fSize.x), y}, sf::Color{255, 0, 0} });
	}
}

void Door::Interact(GameObject* apOther){

	sf::Vector2f v2fOtherPosCenter = apOther->get_pos() + (apOther->get_size() / 2.f);
	sf::Vector2f v2fPosCenter = v2fPos + (v2fSize / 2.f);

	//calculate distance using pythagoras theorem
	float fDistance = std::pow(
		(std::pow(std::abs(v2fOtherPosCenter.x - v2fPosCenter.x), 2) + 
		(std::pow(std::abs(v2fOtherPosCenter.y - v2fPosCenter.y), 2))), 0.5f);

	if (fRotationSpeed == 0.f && fDistance < 100.f)
	{
		if (v2fOtherPosCenter.y > v2fPosCenter.y) {
			
			fRotationSpeed = -DOOR_ROTATION_SPEED_DEGREES;
		}
		else if (v2fOtherPosCenter.y < v2fPosCenter.y) {
			
			fRotationSpeed = DOOR_ROTATION_SPEED_DEGREES;
		}
	}
}

void Door::update(){
	//tmp value to know delta of rotation
	float fRotationBefore = fRotationDegrees;

	fRotationDegrees += (fRotationSpeed * pData->fTimeScaleFactor);

	//detect where the door needs to stop
	if (fRotationSpeed != 0.f){
		if (bPositiveRotation){
			if (fRotationDegrees < (fRotationOrigin - DOOR_MAX_ROTATION_DEGREES)) {
				fRotationDegrees = fRotationOrigin - DOOR_MAX_ROTATION_DEGREES;
				fRotationSpeed = 0.f;
			}
			if (fRotationDegrees > fRotationOrigin) {
				fRotationDegrees = fRotationOrigin;
				fRotationSpeed = 0.f;
			}
		}else{
			if (fRotationDegrees > (fRotationOrigin + DOOR_MAX_ROTATION_DEGREES)) {
				fRotationDegrees = fRotationOrigin + DOOR_MAX_ROTATION_DEGREES;
				fRotationSpeed = 0.f;
			}
			if (fRotationDegrees < fRotationOrigin) {
				fRotationDegrees = fRotationOrigin;
				fRotationSpeed = 0.f;
			}
		}
	}

	//rotate door according to rotational speed
	sprite.setRotation(fRotationDegrees);

	//draw
	GameObject::update();

	//update collision points
	UpdateCollisionPoints(fRotationDegrees - fRotationBefore);
}

void Door::collide(Player* apOther){
	sf::Vector2f v2fOffset{10, 10};
	sf::Rect<float> frectPlayer((apOther->get_pos()) + v2fOffset, (apOther->get_size()) - (v2fOffset * 2.f));

	for (unsigned int i = 0; i < varrCollisionPoints.size(); i++) {
		if (frectPlayer.contains(varrCollisionPoints[i].position)) {
			apOther->move(apOther->get_last_location());
			break;
		}
	}
}

void Door::UpdateCollisionPoints(float fRotationAngle){
	//absolute hinge position
	sf::Vector2f v2fHinge{ v2fPos.x + (v2fSize.y / 2.f),  v2fPos.y + (v2fSize.y / 2.f) };

	//calculate sine and cosine
	float fRotationAngleRadians = (fRotationAngle * PI) / 180.f;
	float fSinRotationAngle = std::sin(fRotationAngleRadians);
	float fCosRotationAngle = std::cos(fRotationAngleRadians);

	for (unsigned int i = 0; i < varrCollisionPoints.size(); i++) {
		//relative position where origin is v2fHinge's position
		sf::Vector2f v2fPositionFromHinge = varrCollisionPoints[i].position - v2fHinge;

		//calculate new relative x and y position where hinge is origin
		sf::Vector2f v2fNewPositionFromHinge;
		v2fNewPositionFromHinge.x = (v2fPositionFromHinge.x * fCosRotationAngle) - (v2fPositionFromHinge.y * fSinRotationAngle);
		v2fNewPositionFromHinge.y = (v2fPositionFromHinge.x * fSinRotationAngle) + (v2fPositionFromHinge.y * fCosRotationAngle);

		//convert relative position to absolute position
		varrCollisionPoints[i].position = (v2fNewPositionFromHinge + v2fHinge);
	}
}
