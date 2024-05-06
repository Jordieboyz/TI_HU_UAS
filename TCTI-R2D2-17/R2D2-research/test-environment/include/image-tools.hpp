#ifndef INCLUDE_IMAGE_TOOLS_HPP_
#define INCLUDE_IMAGE_TOOLS_HPP_

#include <SFML/Graphics.hpp>


struct BinImage;
struct GrayscaleImage;


/* -------------------------------- Interface ------------------------------- */ 

int load_binimage_from_file(const char *strPath, struct BinImage **pImage);

int save_binimage_to_file(const char *strPath, struct BinImage *pImage);

int render_binimage_to_texture(sf::Texture *pWindow, struct BinImage *pImage);

int dump_binimage(const char *strOutFile, struct BinImage *pImage);


int grayscale_from_file(const char *strPath, struct GrayscaleImage **pImage);

int render_grayscale_to_texture(sf::Texture *pTex, struct GrayscaleImage *pImg);

/* ----------------------------------- End ---------------------------------- */

#endif /* INCLUDE_IMAGE_TOOLS_HPP_ */
