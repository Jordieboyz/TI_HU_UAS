/*
 * MapData.hpp
 *
 *  Created on: 17 Jan 2021
 *      Author: lucasw00079
 */

#ifndef SRC_MAPDATA_HPP_
#define SRC_MAPDATA_HPP_

#include <cstdint>

#define LOG2_64				6
#define LOG2_COMPRESSION	6
#define INDEX_SHIFT			(LOG2_64 + LOG2_COMPRESSION)

/**
 * @brief
 *  Macro used to access elements on compressed map using
 *  position relative to window.
 */
#define MAP_GET_MAP_POS(MAP_DATA, X_POS, Y_POS)\
		((MAP_DATA.parrAbstractMap[(((Y_POS >> LOG2_COMPRESSION) * MAP_DATA.uMapX + (X_POS >> LOG2_COMPRESSION)) >> LOG2_64)]\
				& (0x1ULL << (((Y_POS >> LOG2_COMPRESSION) * MAP_DATA.uMapX + (X_POS >> LOG2_COMPRESSION))) % 64)) != 0)

/**
 * @brief
 *  Macro used to access elements on compressed map with adjusted input.
 */
#define MAP_GET_MAP_POS_ADJUSTED_INPUT(MAP_DATA, X_POS, Y_POS)\
	((MAP_DATA.parrAbstractMap[(Y_POS * MAP_DATA.uMapX + X_POS) >> LOG2_64]\
	& 0x1ULL << ((Y_POS * MAP_DATA.uMapX + X_POS) % 64)) != 0)

/**
 * @brief
 *  Sets position on compressed map to occupied.
 */
#define MAP_SET_MAP_POS(MAP_DATA, X_POS, Y_POS)\
		(MAP_DATA.parrAbstractMap[(((Y_POS >> LOG2_COMPRESSION) * MAP_DATA.uMapX + (X_POS >> LOG2_COMPRESSION)) >> LOG2_64)]\
				|= (0x1ULL << (((Y_POS >> LOG2_COMPRESSION) * MAP_DATA.uMapX + (X_POS >> LOG2_COMPRESSION))) % 64))

/**
 * @brief
 *  Mars position on compressed map as vacant.
 */
#define MAP_RESET_MAP_POS(MAP_DATA, X_POS, Y_POS)\
		(MAP_DATA.parrAbstractMap[(((Y_POS >> LOG2_COMPRESSION) * MAP_DATA.uMapX + (X_POS >> LOG2_COMPRESSION)) >> LOG2_64)]\
				&= (~(0x1ULL << (((Y_POS >> LOG2_COMPRESSION) * MAP_DATA.uMapX + (X_POS >> LOG2_COMPRESSION))) % 64)))

struct MapData {
	uint64_t *parrAbstractMap;
	unsigned uMapX;
	unsigned uMapY;
};

#endif /* SRC_MAPDATA_HPP_ */
