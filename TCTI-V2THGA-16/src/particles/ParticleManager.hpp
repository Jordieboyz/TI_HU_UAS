/*
 * ParticleManager.hpp
 *
 *  Created on: 18 Jan 2021
 *      Author: lucasw00079
 */

#ifndef SRC_PARTICLES_PARTICLEMANAGER_HPP_
#define SRC_PARTICLES_PARTICLEMANAGER_HPP_

#include <vector>
#include <SFML/Graphics.hpp>
#include "game-objects/animated-sprites.hpp"

/** @file **/

class ParticleManager {
public:
	ParticleManager(struct GameData *apGameData);
	virtual ~ParticleManager();

	/**
	 * @brief
	 *  Updates and draws all particles to the window in GameData.
	 */
	void update(void);

	/**
	 * @brief
	 *  Adds a particle to the manager
	 * @details
	 *  Adds a particle to the manager the deallocating of
	 *  resources is done by manager. For a detailed overview of
	 *  the struct ParticleData see src/game-objects/animated-sprites.hpp.
	 * @param aParticle The particle to add
	 */
	void add_particle(struct ParticleData aParticle);

	/**
	 * @brief
	 *  This function resets the particle manager.
	 * @detail
	 *  A call to this function resets manager, deallocating any
	 *  resources currently in use by manager.
	 */
	void reset(void);

private:

	/**
	 * @brief
	 *  A struct for internal use only, it contains all data
	 *  needed by the particle manager to correctly display a
	 *  particle.
	 */
	struct PlayingParticle{
		struct ParticleData pPart;
		sf::Image img;
		float currPlayTime;
	};

	struct GameData *pGameData;
	std::vector<PlayingParticle*> particlesPlaying;
};

#endif /* SRC_PARTICLES_PARTICLEMANAGER_HPP_ */
