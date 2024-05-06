/*
 * ParticleManager.cpp
 *
 *  Created on: 18 Jan 2021
 *      Author: lucasw00079
 */

#include "particles/ParticleManager.hpp"
#include "GameData.hpp"

ParticleManager::ParticleManager(struct GameData *apGameData)
: pGameData(apGameData){
}

ParticleManager::~ParticleManager() {
}

void ParticleManager::update(void) {
	for(unsigned int i = 0; i < particlesPlaying.size(); i++){
		PlayingParticle *part = particlesPlaying[i];
		struct AnimationData *pAnim = part->pPart.pAnim;
		sf::Vector2f fScale;
		sf::Vector2f v2fSize = part->pPart.v2fSize;

		part->currPlayTime += (1.0f/FPS_SECOND) * pGameData->fTimeScaleFactor;
		float fAnimProgress = (part->currPlayTime / pAnim->fDuration);
		unsigned uImageIndex = (unsigned int)(fAnimProgress  * (pAnim->uNumImages));

		if(part->currPlayTime >= pAnim->fDuration){
			if(part->pPart.bPersistent)
				uImageIndex = (pAnim->uNumImages-1);

			else{
				particlesPlaying.erase(
						std::remove(particlesPlaying.begin(),
									particlesPlaying.end(), part),
						particlesPlaying.end());

				delete part;
				i--;
				continue;
			}
		}



		unsigned uImageIndexX = uImageIndex % pAnim->uNumImagesX;
		unsigned uImageIndexY = uImageIndex / pAnim->uNumImagesX;

		sf::Vector2u v2uImgSize = part->img.getSize();
		sf::Vector2u v2uSpriteSegmentSize = {v2uImgSize.x / pAnim->uNumImagesX,
											 v2uImgSize.y / pAnim->uNumImagesY};

		fScale = sf::Vector2f( (v2fSize.x / sf::Vector2f(v2uSpriteSegmentSize).x) ,
							   (v2fSize.y / sf::Vector2f(v2uSpriteSegmentSize).y) );


		sf::Vector2u v2uSpriteOffset = {v2uSpriteSegmentSize.x * uImageIndexX,
										v2uSpriteSegmentSize.y * uImageIndexY};

		sf::Rect<int> area(v2uSpriteOffset.x, v2uSpriteOffset.y,
				v2uSpriteSegmentSize.x, v2uSpriteSegmentSize.y);

		sf::Texture tmpTexture;
		tmpTexture.loadFromImage(part->img, area);

		sf::Sprite tmpSprite;
		tmpSprite.setTexture(tmpTexture);
		tmpSprite.setScale(fScale);
		tmpSprite.setPosition(part->pPart.v2fPos);
		tmpSprite.setOrigin(v2fSize/2.0f);
		tmpSprite.setRotation(part->pPart.fRotation);

		pGameData->pRenderWindow->draw(tmpSprite);
	}
}

void ParticleManager::add_particle(struct ParticleData aParticle) {
	sf::Image img;
	struct PlayingParticle *tmp = \
			new PlayingParticle{ aParticle, img, 0.0f };

	tmp->img.loadFromFile(tmp->pPart.pAnim->strImagePath);
	particlesPlaying.push_back(tmp);
}

void ParticleManager::reset(void) {
	for(unsigned int i = 0; i < particlesPlaying.size(); i++)
	{
		PlayingParticle *pTmp = particlesPlaying[i];
		particlesPlaying.erase(particlesPlaying.begin() + i--);

		delete pTmp;
	}
}
