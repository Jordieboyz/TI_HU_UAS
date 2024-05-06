#ifndef SRC_COMPRESSION_H_
#define SRC_COMPRESSION_H_

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

#include <stdint.h>

//TODO: geen idee of dit handig is, maar heb geen zin om een hele lib te includen alleen voor een define van NULL
// #define NULL ((void *)0)


/* -------------------------------- Objects --------------------------------- */

struct BinImage;

enum BLIL_COMPRESSION
{
    BLIL_COMPRESSION_NONE,
    BLIL_COMPRESSION_RLE,
    BLIL_COMPRESSION_HUF,
    BLIL_COMPRESSION_HALFTONE
};


struct RLEHeader 
{
    uint32_t startVal;
    uint32_t FieldWidth;
};

struct HMEHeader
{
    uint8_t uClusterLength;
};


typedef struct Node
{
    struct Node *left, *right;
    unsigned uFreq;
    unsigned uAddr;
    uint8_t uAddrLen;
    uint8_t uItem;
    uint8_t bIsLeafNode;
}Node;

/* ----------------------------------- End ---------------------------------- */

/* -------------------------------- Interface ------------------------------- */ 

/**
 * @brief
 *  Compresses an image with the specified algorithm.
 * @details
 *  The function does not allocate memory for the output, 
 *  the function expects the output to fit in the data segment of pOut.
 *  Most compression algorithms have their own set of parameters, a pointer
 *  to the appropiate struct containing the parameters is expected.
 */
int BLIL_compress(struct BinImage *pIn, struct BinImage *pOut,
    enum BLIL_COMPRESSION eAlgo, void *pParam);

/**
 * @brief
 *  Decompresses a binary image.
 * @details
 *  Decompresses an image the output is places in pOut. The function itself
 *  does not allocate any memory output is expected to fit in the data segment
 *  of pOut, if the output does not fit an error is returned.
 * 
 *  The decompress function passes the pImage to the right handler based on
 *  the enum set in the object.
 */
int BLIL_decompress(struct BinImage *pIn, struct BinImage *pOut);

/* ----------------------------------- End ---------------------------------- */

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* SRC_COMPRESSION_H_ */
