#include <include/dither.h>

#include <errno.h>

#include <include/image.h>
#include "halftone.h"

/* ------------------------ Static function prototypes ---------------------- */

static 
int treshold_filter(struct BinImage *pOut, struct GrayscaleImage *pIn);

static
int bayer_filter(struct BinImage *pOut, struct GrayscaleImage *pIn);

static
int floyd_filter(struct BinImage *pOut, struct GrayscaleImage *pIn);

/* ----------------------------------- End ---------------------------------- */


/* ------------------------ Static function definitions --------------------- */

static 
int treshold_filter(struct BinImage *pOut, struct GrayscaleImage *pIn)
{
    uint32_t u32PixCount = pOut->u16Width * pOut->u16Height;

    pOut->u32DataLen = (u32PixCount >> 3);
    
    for(unsigned i = 0; i < u32PixCount; i++)
    {
        if(pIn->u8arrData[i] >= 128)
            pOut->data[pOut->u16Offset + (i >> 3)] |= (0x01U << (i & 0x7));
        else
            pOut->data[pOut->u16Offset + (i >> 3)] &= ~(0x01U << (i & 0x7));
    }

    return 0;
}

static
int bayer_filter(struct BinImage *pOut, struct GrayscaleImage *pIn)
{
    const int BAYER_PATTERN_4X4[4][4] =	{
                                            {	  0, 128,  32, 160	},
                                            {	192,  64, 224,  96	},
                                            {	 48, 176,  16, 144	},
                                            {	240, 112, 208,  80	}
                                        };

    int	col	= 0;
	int	row	= 0;
    int pix = 0;

    uint32_t u32PixCount = pOut->u16Width * pOut->u16Height;

    pOut->u32DataLen = (u32PixCount >> 3);

    for(unsigned y = 0; y < pIn->u16Height; y++)
    {
        row	= y & 3;

        for(unsigned x = 0; x < pIn->u16Width; x++)
        {
            col	= x & 3;
            pix = x * pOut->u16Width + y;

            if (pIn->u8arrData[pix] < BAYER_PATTERN_4X4[col][row])
            {
                pOut->data[pOut->u16Offset + (pix >> 3)] &= ~(0x01U << (pix & 0x7));
            }
            else
            {
                pOut->data[pOut->u16Offset + (pix >> 3)] |=  (0x01U << (pix & 0x7));
            }
        }
        
    }
    return 0;
}

static
int floyd_filter(struct BinImage *pOut, struct GrayscaleImage *pIn){

    uint16_t width = pIn->u16Width;
    uint16_t height = pIn->u16Height;

    uint32_t u32PixCount = width * height;

    pOut->u32DataLen = (u32PixCount >> 3);

    uint8_t tmp[u32PixCount];

    unsigned i = 0;
    while(i++ < u32PixCount){
        tmp[i] = pIn->u8arrData[i];
    }

    for(unsigned y = 0; y < height-1; y++){
        for(unsigned x = 1; x < width-1; x++){

            int index = x * width + y;

            uint8_t oldPixel = tmp[index];

            uint8_t newPixel = ( (oldPixel / 256.0f ) >= 0.5 ) ? 1.0f : 0.0f;
            
            tmp[index] = newPixel;
      
            float quant_error = oldPixel - newPixel;

            tmp[ (x + 1) * width + y       ] += quant_error * 7/16;
            tmp[ (x - 1) * width + (y + 1) ] += quant_error * 5/16;
            tmp[ x       * width + (y + 1) ] += quant_error * 3/16;   
            tmp[ (x + 1) * width + (y + 1) ] += quant_error * 1/16;

            if(tmp[index] == 0)
                pOut->data[pOut->u16Offset + (index >> 3)] |= (0x01U << (index & 0x7));
            else
                pOut->data[pOut->u16Offset + (index >> 3)] &= ~(0x01U << (index & 0x7));
        }
    }
    return 0;
}

/* ----------------------------------- End ---------------------------------- */


/* -------------------------------- Interface ------------------------------- */

int BLIL_gray_to_dithered(struct GrayscaleImage *pIn,
    struct BinImage *pOut, enum BLIL_DITHER eDither)
{
    int iRetVal = 0;
    unsigned uWidth  = pIn->u16Width;
    unsigned uHeight = pIn->u16Height;

    /* Does output fit in data? If not return error. */
    if(pOut->u32MaxDataLen < (uWidth * uHeight >> 3))
        return -EOVERFLOW;

    pOut->eDither       = eDither;
    pOut->eCompression  = BLIL_COMPRESSION_NONE;
    pOut->u16Offset     = 0;
    pOut->u16Width      = uWidth;
    pOut->u16Height     = uHeight; 
    pOut->u32DataLen    = uWidth * uHeight >> 3;

    switch(eDither)
    {
        case BLIL_DITHER_NONE:
            break;
            
        case BLIL_DITHER_TRESHOLD:
            iRetVal = treshold_filter(pOut, pIn);
            break;

        case BLIL_DITHER_BAYER:
            iRetVal = bayer_filter(pOut, pIn);
            break;

        case BLIL_DITHER_FLOYD:
            iRetVal = floyd_filter(pOut, pIn);
            break;

        case BLIL_DITHER_HALFTONE:
            iRetVal = halftone_dither(pOut, pIn);
            break;

        default:
            iRetVal = -EINVAL;
            break;
    }

    return iRetVal;
}

/* ----------------------------------- End ---------------------------------- */
