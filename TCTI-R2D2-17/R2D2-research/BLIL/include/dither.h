#ifndef SRC_DITHER_H_
#define SRC_DITHER_H_

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

#include <stdint.h>


/* -------------------------------- Objects --------------------------------- */

struct BinImage;
struct GrayscaleImage;

enum BLIL_DITHER 
{
    BLIL_DITHER_NONE,
    BLIL_DITHER_TRESHOLD,
    BLIL_DITHER_BAYER,
    BLIL_DITHER_FLOYD,
    BLIL_DITHER_HALFTONE
};

struct TresholdHeader
{
    uint8_t u8TresholdValue;
};

/* ----------------------------------- End ---------------------------------- */


/* -------------------------------- Interface ------------------------------- */

/**
 * @brief
 *  Dithers a binary image with the selected dither filter.
 * @details
 *  This functions attempts to dither the image with the
 *  selected filter, the size of the data part of the output
 *  image should at least 1/8 of the number of pixels.
 * @retval
 *  returns 0 if success, 
 *  -EINVAL if dither filter is not available,
 *  -EOVERFLOW if provided output image is to small te contain data.
 */
int BLIL_gray_to_dithered(struct GrayscaleImage *pIn,
    struct BinImage *pOut, enum BLIL_DITHER eDither);

/* ----------------------------------- End ---------------------------------- */

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* SRC_DITHER_H_ */
