#include <include/image.h>


/* -------------------------------- Interface ------------------------------- */ 

int BLIL_init_bin_image(struct BinImage *pImg, uint8_t *pData, uint32_t u32Len)
{
    pImg->u32MaxDataLen     = u32Len;
    pImg->data              = pData;
    pImg->u32DataLen        = 0;

    return 0;
}

/* ----------------------------------- End ---------------------------------- */

