#ifndef SRC_IMAGE_H_
#define SRC_IMAGE_H_

#ifdef __cplusplus
    extern "C" {
#endif /* cplusplus */

#include <stdint.h>

#include "dither.h"
#include "compression.h"


/* --------------------------------- Objects -------------------------------- */

struct BinImage 
{
    uint16_t u16Width;
    uint16_t u16Height;
    uint16_t u16Offset;
    uint32_t u32MaxDataLen;
    uint32_t u32DataLen;

    enum BLIL_DITHER eDither;
    enum BLIL_COMPRESSION eCompression;

    uint8_t *data;
};


struct GrayscaleImage
{
    uint16_t u16Width;
    uint16_t u16Height;

    uint8_t *u8arrData;
};

/* ----------------------------------- End ---------------------------------- */


/* -------------------------------- Interface ------------------------------- */ 

/**
 * @brief
 *  Initialises the image by assigning the data segment to image.
 * @details
 *  Other functions assume that the data segment
 *  remains untouched and available.
 */
int BLIL_init_bin_image(struct BinImage *pImg, uint8_t *pData, uint32_t u32Len);

/* ----------------------------------- End ---------------------------------- */

#ifdef __cplusplus
    }
#endif /* cplusplus */

#endif /* SRC_IMAGE_H_ */
