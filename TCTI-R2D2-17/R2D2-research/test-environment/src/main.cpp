#include <SFML/Window.hpp>
#include <include/image-tools.hpp>
#include <include/image.h>
#include <include/GUI.h>
#include <string.h>

bool get_flags(int n, const char **flags, std::string &out){
    for(int i = 2; i < n; i++){
        if(strlen(flags[i]) == 2 && flags[i][0] == '-')
            out += flags[i][1];
    }
    return (out.length() != 0);
}   

int main(int argc, const char **argv) {
    if(argc < 2){
        printf("provide an input image!\n");
        return 0;
    }

    struct GrayscaleImage *pGray;
    std::string flags = "";

    if(grayscale_from_file(argv[1], &pGray) != 0)
        return 1;

    if(get_flags(argc, argv, flags)) {
        struct BinImage image;
        uint8_t u8Buffer[BINIMAGE_DEFAULT_SIZE*5];
        
        BLIL_init_bin_image(&image, u8Buffer, BINIMAGE_DEFAULT_SIZE*5);

        sf::Texture toSave;

        // which dither filter?
        char dFlag = flags[0];
        switch (dFlag){
            case 'g' :  
                render_grayscale_to_texture(&toSave, pGray); 
                break;
            case 'b' :  
                BLIL_gray_to_dithered(pGray, &image, BLIL_DITHER_BAYER); 
                break; 
            case 'f' :  
                BLIL_gray_to_dithered(pGray, &image, BLIL_DITHER_FLOYD); 
                break; 
            case 't' :  
                BLIL_gray_to_dithered(pGray, &image, BLIL_DITHER_TRESHOLD); 
                break;
            case 'h' :  
                BLIL_gray_to_dithered(pGray, &image, BLIL_DITHER_HALFTONE); 
                break;
        }
        
        // compression
        if(flags.length() > 1 && flags[1] == 'c'){
            if(image.eDither != BLIL_DITHER_NONE){
            
                struct BinImage cTmp;
                uint8_t cBuffer[BINIMAGE_DEFAULT_SIZE];
            
                BLIL_init_bin_image(&cTmp, cBuffer, BINIMAGE_DEFAULT_SIZE);

                char cFlag = flags[2];
                
                struct RLEHeader rConf = {  0, 7 };
                struct HMEHeader uConf = {  8 };

                switch (cFlag) {
                case 'h' : 
                    if(image.eDither == BLIL_DITHER_HALFTONE){
                        BLIL_compress(&image, &cTmp, BLIL_COMPRESSION_HALFTONE, 0);
                        dump_binimage("compressedHALF.bin", &cTmp);
                        }
                    break;
                case 'r' : 
                    BLIL_compress(&image, &cTmp, BLIL_COMPRESSION_RLE, &rConf);
                    dump_binimage("compressedRLE.bin", &cTmp);
                    break;
                case 'u' : 
                    BLIL_compress(&image, &cTmp, BLIL_COMPRESSION_HUF, &uConf);
                    dump_binimage("compressedHUF.bin", &cTmp);
                    break;            
            }
            float sizeRatio = (float)cTmp.u32DataLen/image.u32DataLen*100.0f;
            // printf( "Original size: %u\n"
            //         "Compressed size: %u\n" 
            //         "With a compressionrate of: %f\n", 
            //             image.u32DataLen,       
            //             cTmp.u32DataLen,                
            //             sizeRatio
            //     );
                return 1;
            }
        } else {
            if(isalpha(dFlag)){
                if(dFlag != 'g')
                    render_binimage_to_texture(&toSave, &image);
                toSave.copyToImage().saveToFile(argv[3]);
            }
        }
    } else {

        GUI gui(argv[1], pGray);
        
        sf::Vector2f window_size = gui.get_window_size();

        sf::RenderWindow window( 
            sf::VideoMode( window_size.x, window_size.y ), "BLIL-demo");
        sf::Event event;

        while(window.isOpen()){
            while(window.pollEvent(event)){
                if(event.type == sf::Event::MouseButtonReleased){
                    gui.acceptNewCanvasFlag = true;
                    gui.removeOldCanvasFlag = true;   
                    gui.applyNewFilterFlag = true;
                    gui.applyNewCompFlag = true;
                    gui.openNewImageFlag = true;
                    gui.resetFlag = true;
                    if(gui.openIconClickedFlag){
                        gui.isDropdownOpen = !gui.isDropdownOpen;
                        gui.openIconClickedFlag = false;
                    }
                }
                if(event.type == sf::Event::Closed || gui.closeWindow)
                    window.close();

            }

            window.clear();

            gui.handle_input(window);
            gui.update(window);

            window.display();
        }
    }
}
