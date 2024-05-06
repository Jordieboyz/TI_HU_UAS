#include "halftone.h"

#include <include/image.h>
#include "bit_operations.h"


/* --------------------------------- Macros --------------------------------- */

#define BLOCK_SIZ  8

#define POW_2(X) \
    ((X) * (X))

#define ABS(X) \
    ((X < 0) ? (-X) : (X))

/* ----------------------------------- End ---------------------------------- */


/* ---------------------------------- Objects ------------------------------- */

struct HTPattern
{
    uint8_t *data;          /* Precomputed circleshape.     */
    uint8_t u8Size;         /* Width and height of square.  */
    uint8_t bInverted;      /* Pattern should be inverted.  */
    uint8_t u8Count;        /* Resulting intensity.         */
};

/* ----------------------------------- End ---------------------------------- */


/* ------------------------ Static function prototypes ---------------------- */

/**
 * Draws a dot in the data array of the HTPattern, 
 * other variables are left unchanged.
 */
static
void HT_dot(struct HTPattern *pPattern, unsigned uRadius);

/**
 * Calculates the average pixel value in a grayscale image.
 */
static
uint8_t block_avg(uint8_t *pStart, struct GrayscaleImage *pImg);

/**
 * Counts the number of white pixels in a square, 
 * offsett from pStart in bits should be given.
 */
static
int block_count(uint8_t *pStart, unsigned uOff, unsigned uSize, unsigned uWidth);

/**
 * Copies a halftone pattern into a binary image.
 */
static
void pattern_cpy(uint8_t* pStart, struct BinImage *pImg, struct HTPattern *pPattern);

/**
 * Initialises a set of HTPatterns, patterns start at dot size of 0
 * up to iNumPatterns / 2.
 * The first half of patterns are white on black, 
 * the second half are black on white.
 */
static
void precompute_patterns(
    struct HTPattern arrPatterns[], uint8_t arrCircles[][64], int iNumPatterns);

/* ----------------------------------- End ---------------------------------- */


/* ------------------------ Static function definitions --------------------- */

void HT_dot(struct HTPattern *pPattern, unsigned uRadius)
{
    unsigned uCentre = pPattern->u8Size >> 1;
    unsigned uSize   = pPattern->u8Size;
    uint8_t *pCanvas = pPattern->data;
    int iDistance;
    int x = uRadius;
    int y = 0;
    int left;
    int right;

    do
    {
        iDistance = POW_2(x) + POW_2(y);
        while(iDistance > POW_2(uRadius))
        {
            x -= 1;
            iDistance = POW_2(x) + POW_2(y);
        }

        /* Bottom */
        left = (uCentre + y) * uSize + (uCentre - x);
        right = (uCentre + y) * uSize + (uCentre + x);
        while(left++ < right) 
            pCanvas[left >> 3] |= 0x1U << (left & 0x07U);

        /* Top */
        left = (uCentre - y) * uSize + (uCentre - x);
        right = (uCentre - y) * uSize + (uCentre + x);
        while(left++ < right) 
            pCanvas[left >> 3] |= 0x1U << (left & 0x07U);
        
    } while( y++ < uRadius);   
}


void pattern_cpy(uint8_t* pStart, struct BinImage *pImg, struct HTPattern *pPattern)
{
    unsigned uPixels    = POW_2(BLOCK_SIZ);
    unsigned uImgWidth  = pImg->u16Width;
    unsigned uPatWidth  = pPattern->u8Size;

    if(pPattern->bInverted)
        for(unsigned i = 0; i < uPixels; i++)
        {
            if((pPattern->data[i >> 3] & (0x1U << (i & 0x7U))) != 0)
                pStart[i / uPatWidth * uImgWidth >> 3] &= ~(0x1U << (i & 0x7U));
            else
                pStart[i / uPatWidth * uImgWidth >> 3] |= (0x1U << (i & 0x7U));
        }
    else
        for(unsigned i = 0; i < uPixels; i++)
        {
            if((pPattern->data[i >> 3] & (0x1U << (i & 0x7U))) != 0)
                pStart[i / uPatWidth * uImgWidth >> 3] |= (0x1U << (i & 0x7U));
            else
                pStart[i / uPatWidth * uImgWidth >> 3] &= ~(0x1U << (i & 0x7U));
        }  
}


uint8_t block_avg(uint8_t *pStart, struct GrayscaleImage *pImg)
{
    unsigned uImgWidth      = pImg->u16Width;
    uint32_t uAccumulator   = 0;

    for(int i = 0; i < BLOCK_SIZ; i++)
    {
        for(int j = 0; j < BLOCK_SIZ; j++)
        {
            uAccumulator += pStart[i * uImgWidth + j];
        }
    }

    return (uAccumulator / POW_2(BLOCK_SIZ));
}


int block_count(uint8_t *pStart, unsigned uOff, unsigned uSize, unsigned uWidth)
{
    unsigned uAccumulator   = 0;
    unsigned uIndex         = uOff;

    for(int i = 0; i < uSize; i++)
    {
        uIndex = i * uWidth + uOff;

        for(int j = 0; j < uSize; j++)
        {
            if((pStart[uIndex >> 3] & (0x1U << (uIndex & 0x7U))) != 0)
                uAccumulator++;

            uIndex++;
        }
    }

    return uAccumulator;
}


void precompute_patterns(
    struct HTPattern arrPatterns[], uint8_t arrCircles[][64], int iNumPatterns)
{
    unsigned uCount;

    for( int i = 0; i < iNumPatterns / 2; i++)
    {
        /* Initialise patterns, both the normal and inverted. */
        arrPatterns[i].bInverted    = 0;
        arrPatterns[i].u8Size       = BLOCK_SIZ;
        arrPatterns[i].data         = arrCircles[i];

        arrPatterns[iNumPatterns - 1 - i].bInverted     = 1;
        arrPatterns[iNumPatterns - 1 - i].u8Size        = BLOCK_SIZ;
        arrPatterns[iNumPatterns - 1 - i].data          = arrCircles[i];
        
        HT_dot(&arrPatterns[i], i);

        uCount = block_count(arrCircles[i], 0, BLOCK_SIZ, BLOCK_SIZ);
        arrPatterns[i].u8Count = uCount;
        arrPatterns[iNumPatterns - 1 - i].u8Count = POW_2(BLOCK_SIZ) - uCount;
    }
}

/* ----------------------------------- End ---------------------------------- */


/* -------------------------------- Interface ------------------------------- */

int halftone_dither(struct BinImage *pOut, struct GrayscaleImage *pIn)
{
    unsigned uBlockAvg;
    unsigned uOff = 0;

    /* Pre-compute circles. */
    uint8_t circles[BLOCK_SIZ / 2][POW_2(BLOCK_SIZ)] = {{0}};
    struct HTPattern patterns[BLOCK_SIZ];

    precompute_patterns(patterns, circles, BLOCK_SIZ);

    for(int i = 0; i < (pIn->u16Width / BLOCK_SIZ); i++)
    {
        for(int j = 0; j < (pIn->u16Height / BLOCK_SIZ); j++)
        {
            uOff = (i * BLOCK_SIZ) + (j * BLOCK_SIZ * pIn->u16Width);
            uBlockAvg = block_avg(pIn->u8arrData  + uOff, pIn);
            uBlockAvg = uBlockAvg / (256 / BLOCK_SIZ);

            pattern_cpy(pOut->data + (uOff >> 3), pOut, &patterns[uBlockAvg]);
        }
    }
    
    return 0;
}


int halftone_compress(struct BinImage *pIn, struct BinImage *pOut, void *pParams)
{
    unsigned uCurr   = 0;
    unsigned uOutOff = 0;
    int iAcc;

    uint8_t circles[BLOCK_SIZ / 2][POW_2(BLOCK_SIZ)] = {{0}};
    struct HTPattern patterns[BLOCK_SIZ];

    precompute_patterns(patterns, circles, BLOCK_SIZ);

    /* Count horizontal pixels, */
    for(int i = 0; i < (pIn->u16Width / BLOCK_SIZ); i++)
    {
        for(int j = 0; j < (pIn->u16Height / BLOCK_SIZ); j++)
        {
            uCurr = i * BLOCK_SIZ + j * BLOCK_SIZ * pIn->u16Width;
            iAcc = block_count(pIn->data, uCurr, BLOCK_SIZ, pIn->u16Width);

            /* Search matching pattern. */
            for(int k = 0; k < BLOCK_SIZ; k++)
            {
                if(patterns[k].u8Count == iAcc)
                {
                    BFI((pOut->data + (uOutOff >> 3)), (uOutOff & 0x07U), 3, k);
                    uOutOff += 3;
                    break;
                }
            }
        }
    }

    pOut->u32DataLen = (uOutOff >> 3);

    return 0;
}


int halftone_decompress(struct BinImage *pIn, struct BinImage *pOut)
{
    unsigned uOutOff        = 0;
    unsigned uInOff         = 0;
    unsigned uPattern;

    uint8_t circles[BLOCK_SIZ / 2][POW_2(BLOCK_SIZ)] = {{0}};
    struct HTPattern patterns[BLOCK_SIZ];

    precompute_patterns(patterns, circles, BLOCK_SIZ);

    for(int i = 0; i < (pIn->u16Width / BLOCK_SIZ); i++)
    {
        for(int j = 0; j < (pIn->u16Height / BLOCK_SIZ); j++)
        {
            uPattern = UBFX((pIn->data + (uInOff >> 3)), uInOff & 0x07U, 3);
            uInOff += 3;

            uOutOff = (i * BLOCK_SIZ) + (j * BLOCK_SIZ * pIn->u16Width);
            pattern_cpy(pOut->data + (uOutOff >> 3), pOut, &patterns[uPattern]);
        }
    }

    return 0;
}

/* ----------------------------------- End ---------------------------------- */
