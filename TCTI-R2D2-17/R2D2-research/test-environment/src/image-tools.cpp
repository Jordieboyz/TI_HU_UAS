#include <include/image-tools.hpp>

#include <errno.h>

#include <SFML/Graphics.hpp>
#include <include/image.h> 


/* -------------------------------- Interface ------------------------------- */ 

/* TODO: implement. */
int load_binimage_from_file(const char *strPath, struct BinImage **pImage)
{
    return 0;
}

/* TODO: implement. */
int save_binimage_to_file(const char *strPath, struct BinImage *pImage)
{
    return 0;
}

/* TODO: reduce complexity of certain expressions in this function. */
int render_binimage_to_texture(sf::Texture *pTex, struct BinImage *pImage)
{
    if(pImage->eCompression != BLIL_COMPRESSION_NONE)
        return -EINVAL;

    unsigned uWidth  = pImage->u16Width;
    unsigned uHeight = pImage->u16Height;
    unsigned uPixels = uWidth * uHeight;
    uint32_t *imgBuffer = new uint32_t[uWidth * uHeight];
   
    printf("Rendering binary image with X: %d, Y: %d\n", uWidth, uHeight);

    pTex->create(uWidth, uHeight);

    for( unsigned i = 0; i < uPixels; i++)
    {
        uint8_t tmp = pImage->data[pImage->u16Offset + (i >> 3)];
        uint8_t fill = ((tmp & (0x1U << (i & 0x7U))) != 0) ? (0xFFU) : (0x00U);

        imgBuffer[i] = fill | (fill << 8) | (fill << 16) | (0xFFU << 24);
    }
    
    pTex->update((uint8_t*)imgBuffer, uWidth, uHeight, 0, 0);
    delete imgBuffer;

    return 0;
}


int dump_binimage(const char *strOutFile, struct BinImage *pImage)
{
    FILE *f = fopen(strOutFile, "wb+");
    if(f == NULL)
        return 1;

    /* 
     * Don't write pointers as these will always vary
     * between image's which would keep us from using checksums to
     * verify whether image's are correctly compressed and decompressed.
     */
    fwrite(pImage, 1, sizeof(struct BinImage) - sizeof(uint8_t *), f);
    fwrite(pImage->data, 1, pImage->u32DataLen, f);
    fclose(f);

    return 0;
}


int grayscale_from_file(const char *strPath, struct GrayscaleImage **pImage)
{
    sf::Image img;
    sf::Vector2u vec2uDimm;

    if(!img.loadFromFile(strPath))
        return -ENOENT;

    vec2uDimm = img.getSize();

    /* Dynamically allocate space for grayscaled image and set fields. */
    *pImage = (struct GrayscaleImage*)malloc(sizeof(struct GrayscaleImage));
    (*pImage)->u8arrData = (uint8_t*)malloc(vec2uDimm.x * vec2uDimm.y);
    (*pImage)->u16Width = vec2uDimm.x;
    (*pImage)->u16Height = vec2uDimm.y;

    for(unsigned i = 0; i < vec2uDimm.y; i++)
        for(unsigned j = 0; j < vec2uDimm.x; j++)
        {
            sf::Color RGB = img.getPixel(j, i);

            /* Weighted grayscale conversion. 
             * https://en.wikipedia.org/wiki/Grayscale
             */
            uint8_t tmp = RGB.r * 0.2126 + RGB.g * 0.7152 + RGB.b * 0.0722;
            (*pImage)->u8arrData[i * vec2uDimm.x + j] = tmp; 
        }

    return 0;
}


/* This code is suppar, TODO: increase efficiency. */
int render_grayscale_to_texture(sf::Texture *pTex, struct GrayscaleImage *pImg)
{
    unsigned uWidth  = pImg->u16Width;
    unsigned uHeight = pImg->u16Height;
    uint32_t *imgBuffer = new uint32_t[uWidth * uHeight];

    pTex->create(uWidth, uHeight);

    printf("Rendering grayscale image with X: %d, Y: %d\n", uWidth, uHeight);

    for(unsigned i = 0; i < uHeight; i++)
        for(unsigned j = 0; j < uWidth; j++)
        {
            uint8_t u8GrayVal = pImg->u8arrData[i * uWidth + j];
        
            imgBuffer[i * uWidth + j] = u8GrayVal | (u8GrayVal << 8) | 
                (u8GrayVal << 16) | (0xFFU << 24);
        }
    
    pTex->update((uint8_t*)imgBuffer, uWidth, uHeight, 0, 0);
    delete imgBuffer;

    return 0;
}

/* ----------------------------------- End ---------------------------------- */
