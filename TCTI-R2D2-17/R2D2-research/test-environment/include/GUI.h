#ifndef _INCLUDE_GUI_H_
#define _INCLUDE_GUI_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>

#include <include/image-tools.hpp>
#include <include/image.h>
#include <include/dither.h>
#include <include/compression.h>

#define BINIMAGE_DEFAULT_SIZE   156269 //this is for 512x512 // 65536; this is for 240x240
#define amountOfTextures 15
#define PATH "test-environment/res/"


struct image_info {
    uint8_t binImageBuff[BINIMAGE_DEFAULT_SIZE];
    struct BinImage image;

    uint32_t originalDataLen = 0;

    image_info(){
        image.data = nullptr;
        image.eCompression = BLIL_COMPRESSION_NONE;
        image.eDither = BLIL_DITHER_NONE;
        image.u16Height = 0;
        image.u16Width = 0;
        image.u16Offset = 0;
        image.u32DataLen = 0;
        image.u32MaxDataLen = 0;
        BLIL_init_bin_image(&image, binImageBuff, BINIMAGE_DEFAULT_SIZE);
    }
};

struct sprite_struct {
    sf::Sprite sprite;
    sf::Texture normal, hover;
    
    image_info imInfo;

    void loadNSetTexture(const char * nTexture, const char * hTexture = nullptr){
        normal.loadFromFile(nTexture);
        if(!(!hTexture))
            hover.loadFromFile(hTexture);
        sprite.setTexture(normal);
    }

    void set_texture(bool b = true){
        (b) ? sprite.setTexture(normal) : sprite.setTexture(hover);
    }

    void reset(sf::Texture t){
        imInfo = image_info();

        normal = t;
        sprite.setTexture(normal);
    }
};

enum icons {
    OPEN = 1,
    SAVE,
    REMOVE,
    ADD,
    RESET,
    GRAY,
    BAYER,
    FLOYD,
    THRESHOLD,
    HALFTONE_D,
    HALFTONE_C,
    HUFFMAN,
    RLE,
    CLOSE
};

class GUI {
public:
    GUI( const char * imPath,   
         struct GrayscaleImage *grayScaledImage) 
        :   imPath(imPath),
            grayImg(grayScaledImage)   
    {
        BLIL_init_bin_image(&tmpCompBinImage, binImageBuffer,
                                     BINIMAGE_DEFAULT_SIZE);

        imPathTexture.loadFromFile(imPath);

        calculate_window_size();

        load_gui_textures();

        get_image_filenames();

        create_open_dropdown();


        compressionSize.setPosition(0, windowSize.y-40.0f);
        compressionSize.setFont(f);
    }

    sf::Vector2f get_window_size();
    
    void handle_input(sf::RenderWindow &window);
    void update(sf::RenderWindow &window);

    // flags to prevent multiple clicks on icons
    bool acceptNewCanvasFlag = true;
    bool removeOldCanvasFlag = false;
    bool applyNewFilterFlag = true;
    bool applyNewCompFlag = true;
    bool openNewImageFlag   = true;
    bool openIconClickedFlag= false;

    bool isDropdownOpen = false;
    bool closeWindow = false;
    bool resetFlag = true;

private:
    void calculate_window_size();
    void set_max_canvas_rows(int x, int y);

    void select_canvas(sf::RenderWindow &window);
    void update_canvas_rows();

    void apply_dither_filter(BLIL_DITHER dither);
    void apply_compression(BLIL_COMPRESSION compression);

    void add_canvas();
    void remove_canvas();

    bool load_gui_textures();

    sf::Vector2f windowSize;

    const char *imPath;
    struct BinImage tmpCompBinImage;  // this is mainly for compression; 
    GrayscaleImage *grayImg;
    uint8_t binImageBuffer[BINIMAGE_DEFAULT_SIZE];

    sprite_struct gui_sprites[amountOfTextures];
    sf::RectangleShape imagePreview;

    std::vector<sprite_struct *> images = {};

    int maxCanvasRows[2] = {5, 2};
    int currCanvasRows[2] = {0, 0};

    sf::Text compressionSize;

    // save already used Textures again if needed. just for filters/ dithered images.
    sf::Texture imPathTexture;

    sprite_struct *isSelected = nullptr;


    // opening files..this is shit...
    void get_image_filenames();
    void create_open_dropdown();

    sf::Font f;
    sf::RectangleShape dialogBG;

    std::vector<std::string> filenames;
    std::vector<sf::Text *> dialog_items = {};


};

#endif
