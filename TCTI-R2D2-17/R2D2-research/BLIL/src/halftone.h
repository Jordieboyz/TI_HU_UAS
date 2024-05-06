#ifndef SRC_HALFTONE_H_
#define SRC_HALFTONE_H_

#include <stdint.h>

struct BinImage;
struct GrayscaleImage;
struct HTPattern;

int halftone_dither(struct BinImage *pOut, struct GrayscaleImage *pIn);

int halftone_compress(struct BinImage *pIn, struct BinImage *pOut, void *pParams);

int halftone_decompress(struct BinImage *pIn, struct BinImage *pOut);

#endif /* SRC_HALFTONE_H_ */
