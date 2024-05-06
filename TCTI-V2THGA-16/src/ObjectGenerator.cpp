/*
 * WallGenerator.cpp
 *
 *  Created on: 12 Jan 2021
 *      Author: lucasw00079
 */

#include <ObjectGenerator.hpp>
#include <cstdio>

#include "Definitions.hpp"
#include "game-objects/GameObjectFactory.hpp"
#include "GameData.hpp"

#define BITMAP_OFFSET_OFFSET 	10
#define BITMAP_OFFSET_WIDTH 	18
#define BITMAP_OFFSET_HEIGHT 	22

ObjectGenerator::ObjectGenerator(const char *backGroundImage, GameData *apGameData):
	pGameData(apGameData){
	FILE *pFile = fopen(backGroundImage, "r");

	fseek(pFile, 0, SEEK_END);
	uLen = ftell(pFile);
	rewind(pFile);

	pImg  = new uint8_t[uLen+1];
	fread(pImg, 1, uLen, pFile);

	uint32_t u32PixOff = *((uint32_t*)(pImg + BITMAP_OFFSET_OFFSET));
	u32Width  = *((uint32_t*)(pImg + BITMAP_OFFSET_WIDTH));
	u32Height = *((uint32_t*)(pImg + BITMAP_OFFSET_HEIGHT));
	pPixels   = (uint32_t*)((pImg + u32PixOff));
	uIterator = 0;
	fclose(pFile);

	struct MapData *pMapData = &pGameData->mapData;
	pMapData->parrAbstractMap = (uint64_t*)calloc((u32Width * u32Height) >> INDEX_SHIFT, sizeof(uint64_t));
	pMapData->uMapX = u32Width >> LOG2_COMPRESSION;
	pMapData->uMapY = u32Height >> LOG2_COMPRESSION;
}

ObjectGenerator::~ObjectGenerator() {
	//TODO: fix memory leak
	//delete [] pImg;
}

GameObject* ObjectGenerator::generate_object(enum GAME_OBJECT_TYPE aeType,
		uint32_t au32Col) {
	/* Buffer colour if colour change reset iterator */
	if(au32Col != u32ColToSearch){
		u32ColToSearch = au32Col;
		uIterator = 0;
	}

	for(int i = (u32Height-1) - (uIterator / u32Width); i >= 0; i--){
		for(unsigned j = uIterator % u32Width; j < u32Width; j++, uIterator++){
			if(*(pPixels + i * u32Width + j) == au32Col){
				return process_match(j, i, aeType);
			}
		}
	}

	return nullptr;
}

GameObject* ObjectGenerator::process_match(int aiXpos, int aiYpos,
		enum GAME_OBJECT_TYPE aeTypeToGen) {
	uint32_t *pTopLeft = (pPixels + aiYpos * u32Width + aiXpos);
	unsigned uLeft = uIterator % u32Width;
	unsigned uTop = uIterator / u32Width;
	unsigned uWidth;
	unsigned uHeight;

	/* Scan width */
	uint32_t *pTmp = pTopLeft;
	while(*++pTmp == u32ColToSearch);
	uWidth = pTmp - pTopLeft;

	/* Scan height */
	pTmp = pTopLeft;
	while(pTmp >= pPixels && *pTmp == u32ColToSearch)
		pTmp -= u32Width;
	uHeight = (pTopLeft - pTmp) / u32Width;

	/* colour region to mark as processed. Add to map */
	for(unsigned i = 0; i < uHeight; i++){
		for(unsigned j = 0; j < uWidth; j++){
			*(pTopLeft - (i * u32Width) + j) = 0;
			MAP_SET_MAP_POS(pGameData->mapData, (uLeft + j), (uTop + i));
		}
	}

#ifdef DEBUG
	printf("OBJECT_GENERATOR: obj created X: %d Y: %d, width: %d, height: %d\n",
			uLeft, uTop, uWidth, uHeight);
#endif

	return GameObjectFactory::get_instance()->create_object(aeTypeToGen,
			{(float)uLeft, (float)uTop}, { (float)uWidth, (float)uHeight}, pGameData);
}
