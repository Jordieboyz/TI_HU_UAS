#include <include/GUI.h>


bool is_hovered(sf::FloatRect rect, sf::RenderWindow &window){
    return rect.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
}

bool is_button_pressed(sf::Mouse::Button button = sf::Mouse::Left ){
    return sf::Mouse::isButtonPressed(button);
}

bool is_loaded_texture(const sf::Texture &texture){
    return texture.getSize() == sf::Vector2u(0, 0);
}

void exec_term_cmd(std::string cmd){
    system(cmd.c_str());
}

//---------------------------------------------------------------//
//--------------------------[ PUBLIC ]--------------------------//
//---------------------------------------------------------------//
void GUI::update(sf::RenderWindow &window){
    for(unsigned i = 0; i < amountOfTextures; i++){
        window.draw(gui_sprites[i].sprite);
        window.draw(imagePreview);
    }

    update_canvas_rows();
    for(unsigned i = 0; i < images.size(); i++){
        window.draw(images[i]->sprite);
    }

    select_canvas(window);

    if(isDropdownOpen){
        window.draw(dialogBG);
        for(auto ob : dialog_items){
            window.draw(*ob);
        }
    }


    if(isSelected != nullptr){
        if(isSelected->imInfo.image.eCompression != BLIL_COMPRESSION_NONE){
            compressionSize.setString(std::string{
                "Original size: " +
                std::to_string(isSelected->imInfo.originalDataLen) +
                "          Compressed size: " +
                std::to_string(isSelected->imInfo.image.u32DataLen)}
            );
            window.draw(compressionSize);
        }
    }
}

void GUI::handle_input(sf::RenderWindow &window){
    if(isDropdownOpen){
        for(auto ob : dialog_items){
            if(is_hovered(ob->getGlobalBounds(), window)){
                ob->setFillColor(sf::Color::Green);

                if(is_button_pressed() && openNewImageFlag){
                    exec_term_cmd("./main test-environment/res/test-images/" 
                                            + ob->getString() + " &");
                    openNewImageFlag = false;
                } 
            } else {
                ob->setFillColor(sf::Color::White);
            }
        }
    }

    // first item in vector is the background!
    for(unsigned i = 1; i < amountOfTextures; i++){
        if(is_hovered(gui_sprites[i].sprite.getGlobalBounds(), window)){
            
            gui_sprites[i].sprite.setTexture(gui_sprites[i].hover);

            if(is_button_pressed()){
                switch(i){
                    case OPEN:
                        if(openIconClickedFlag == false)
                            openIconClickedFlag = true;
                        break;
                    case SAVE: 
                        printf("implementation of save!\n"); 
                        break;
                    case REMOVE: 
                        if(removeOldCanvasFlag) 
                            remove_canvas();
                        break;
                    case ADD: 
                        if(acceptNewCanvasFlag)
                            add_canvas(); 
                        break;
                    case RESET:
                        if(!(!isSelected) && resetFlag){
                            isSelected->reset(imPathTexture);
                            resetFlag = false;
                        }
                        break;
                    case GRAY: 
                        apply_dither_filter(BLIL_DITHER_NONE);
                        break;
                    case BAYER:
                        apply_dither_filter(BLIL_DITHER_BAYER);
                        break;
                    case FLOYD: 
                        apply_dither_filter(BLIL_DITHER_FLOYD);
                        break;
                    case THRESHOLD: 
                        apply_dither_filter(BLIL_DITHER_TRESHOLD);
                        break;
                    case HALFTONE_D: 
                        apply_dither_filter(BLIL_DITHER_HALFTONE); 
                        break;
                    case HALFTONE_C: 
                        apply_compression(BLIL_COMPRESSION_HALFTONE); 
                        break;  
                    case HUFFMAN: 
                        apply_compression(BLIL_COMPRESSION_HUF); 
                        break; 
                    case RLE: 
                        apply_compression(BLIL_COMPRESSION_RLE);
                        break; 
                    case CLOSE:
                        closeWindow = true;
                        break;       
                }
            }
        } else {
            gui_sprites[i].sprite.setTexture(gui_sprites[i].normal);
        }
    }
}

sf::Vector2f GUI::get_window_size(){
    return windowSize;
}


//---------------------------------------------------------------//
//--------------------------[ PRIVATE ]--------------------------//
//---------------------------------------------------------------//

void GUI::calculate_window_size(){

    // calculate based on a full screen.
    int maxWindowWidth = 1920;
    int maxWindowHeight = 1080;

    int offset = 10;

    sf::Vector2f oneImage( grayImg->u16Width + offset, 
                            grayImg->u16Height + offset);
    
    int width =  int(maxWindowWidth - (4 * offset)) / oneImage.x;
    int height = int(maxWindowHeight - 100 - (4 * offset) ) / oneImage.y;
    
    set_max_canvas_rows(width, height);
    
    float windowWidth = oneImage.x * maxCanvasRows[0] + (2 * offset);
    float windowHeight = oneImage.y * maxCanvasRows[1] + (4 * offset) + 100;
    
    (windowWidth < 1000) ? windowSize.x = 1000: windowSize.x = windowWidth;
    (windowWidth < 200) ? windowSize.x = 200 + 30: windowSize.y = windowHeight + 30;
}

void GUI::set_max_canvas_rows(int r1, int r2){
    if(r1 >= 0 && r1 < maxCanvasRows[0])
        maxCanvasRows[0] = r1;
    if(r2 >= 0 && r2 < maxCanvasRows[1])
        maxCanvasRows[1] = r2; 
}

void GUI::select_canvas(sf::RenderWindow &window){
    for(unsigned i = 0; i < images.size(); i++){

        if(is_hovered(images[i]->sprite.getGlobalBounds(), window) &&
            is_button_pressed() ){

            if(!(!isSelected))
                isSelected->sprite.setColor(sf::Color::White);
            isSelected = images[i];
            isSelected->sprite.setColor(sf::Color(200, 200, 200));
        }
        if(is_button_pressed(sf::Mouse::Right)){
            if(!(!isSelected))
                isSelected->sprite.setColor(sf::Color::White);
            isSelected = nullptr;
        }
    }
}

void GUI::update_canvas_rows(){
    float guiHeight = 125.0f;
    float offset = 10.0f;
    float imageWidth = grayImg->u16Width;

    float row1 = windowSize.x/2.0f; 
    float row2 = windowSize.x/2.0f;

    row1 -= imageWidth * (currCanvasRows[0] * 0.5);
    row2 -= imageWidth * (currCanvasRows[1] * 0.5);
    if(currCanvasRows[0] != 1){
        row1 -= (offset * ((currCanvasRows[0]-1) * 0.5));
        row2 -= (offset * ((currCanvasRows[1]-1) * 0.5));
    }

    for(unsigned i = 0; i < images.size(); i++){
        if(maxCanvasRows[1] > 1){
            if(i % 2 == 0){
                images[i]->sprite.setPosition(row1, guiHeight + (2 * offset));
                row1 += imageWidth + offset;
            } else {
                images[i]->sprite.setPosition(row2, (guiHeight + (3 * offset)) + imageWidth);
                row2 += imageWidth + offset;
            }
        } else {
            images[i]->sprite.setPosition(row1, guiHeight);
            row1 += imageWidth + offset;
        }
    }
}

void GUI::apply_dither_filter(BLIL_DITHER dither){
    if(isSelected != nullptr && applyNewFilterFlag){

        if(dither == BLIL_DITHER_NONE)
            render_grayscale_to_texture(&isSelected->normal, grayImg);
        else {
            BLIL_gray_to_dithered(grayImg, &isSelected->imInfo.image, dither);
            render_binimage_to_texture(&isSelected->normal, &isSelected->imInfo.image);
        }
        isSelected->imInfo.originalDataLen = isSelected->imInfo.image.u32DataLen;
        isSelected->set_texture();
    }
    applyNewFilterFlag = false;
}

void GUI::apply_compression(BLIL_COMPRESSION compression){
    if(isSelected != nullptr && applyNewCompFlag){
        

        
        struct BinImage tmp;
        BLIL_init_bin_image(&tmp, binImageBuffer, BINIMAGE_DEFAULT_SIZE);

        if(isSelected->imInfo.image.eDither != BLIL_DITHER_NONE ){

            if(compression == BLIL_COMPRESSION_RLE){
                struct RLEHeader RLEConfig = {  0, 7 };
                BLIL_compress(&isSelected->imInfo.image, &tmpCompBinImage, compression, &RLEConfig);
            }
            if(compression == BLIL_COMPRESSION_HUF){
                struct HMEHeader HMencoding = {  8 };
                BLIL_compress(&isSelected->imInfo.image, &tmpCompBinImage, compression, &HMencoding);
            }
            if(compression == BLIL_COMPRESSION_HALFTONE){
                if(isSelected->imInfo.image.eDither == BLIL_DITHER_HALFTONE){
                    BLIL_compress(&isSelected->imInfo.image, &tmpCompBinImage, compression, 0);
                }
            }
            isSelected->imInfo.image = tmpCompBinImage;
        }
    }
    applyNewCompFlag = false;
}

void GUI::add_canvas(){
    int size = images.size();

    if(size < maxCanvasRows[0] * maxCanvasRows[1]){


        images.push_back( new sprite_struct() );

        images[size]->sprite.setTexture(imPathTexture);


        if(maxCanvasRows[1] > 1){
            (currCanvasRows[0] <= currCanvasRows[1]) ? currCanvasRows[0]++: currCanvasRows[1]++;
        } else {
            currCanvasRows[0]++;
        }
    }
    acceptNewCanvasFlag = false; 
}

void GUI::remove_canvas(){

    if(images.size() > 0){
        
        //TODO: one big fiasco, deleting shit...
        // doesn't delete content on pointer.
        delete images.back();
        images.pop_back();

        (currCanvasRows[1] >= currCanvasRows[0]) ? currCanvasRows[1]-- : currCanvasRows[0]--;
    }
    removeOldCanvasFlag = false; 
}

const char * textures[amountOfTextures][2] = {
    { PATH"UI.png", PATH"UI.png" },
    { PATH"open.png", PATH"open_hover.png"},
    { PATH"save.png",  PATH"save_hover.png"},
    { PATH"remove.png", PATH"remove_hover.png"}, 
    { PATH"add.png", PATH"add_hover.png"}, 
    { PATH"reset.png", PATH"reset_hover.png"},
    { PATH"GrayscaleIcon.png", PATH"GrayscaleIcon.png"}, 
    { PATH"BayerIcon.png", PATH"BayerIcon.png" },
    { PATH"FloydIcon.png", PATH"FloydIcon.png" },
    { PATH"ThresholdIcon.png", PATH"ThresholdIcon.png" },
    { PATH"HalftoneIcon.png", PATH"HalftoneIcon.png" },
    { PATH"HuffmanIcon.png", PATH"HuffmanIcon.png" },
    { PATH"HuffmanIcon.png", PATH"HuffmanIcon.png" },
    { PATH"RunLengthIcon.png", PATH"RunLengthIcon.png" },
    { PATH"close.png", PATH"close_hover.png"}, 
};

bool GUI::load_gui_textures(){
    float x = 0.0f; 
    float y = 0.0f;
    float iconWidth = 70.0f;

    imagePreview.setSize({59.0f, 59.0f});
    imagePreview.setTexture(&imPathTexture);
    imagePreview.setPosition( windowSize.x - (iconWidth - 5) * 2, 10);

    for(unsigned i = 0; i < amountOfTextures; i++){
        if(i == amountOfTextures-1){
            x = windowSize.x - iconWidth - 5;
        }
    
        gui_sprites[i].loadNSetTexture(textures[i][0], textures[i][1]);
        gui_sprites[i].sprite.setPosition(x, y);
        
        //background comes at first and had to be on y = 0, x = 0;
        if(i > 0){
            // make sure all your icons have the same width AKA 70.0f in this program.
            x += iconWidth;
            if(i == 2 || i == 4 || i == 10 )
                // space in between "groups" of icon AKA the black vertical line
                x += 5 ;
        }
        // allignment for nice and clean in the middle of de HUD
        y = 4;
    }  
    return true;
}

// fill a vector with filesnames in the "res/test-images" foler.
void GUI::get_image_filenames(){
    std::string fName = "FileNames.txt";
    std::string rPath = PATH;

    // basiccaly write output from "ls" in a file.
    exec_term_cmd("> " + rPath + fName + " && ls " + 
                                rPath + "test-images/ >> " + rPath + fName);


    std::ifstream in(rPath + fName);
    std::string str;
    while(std::getline(in, str)){
        if(str.size() > 0)
            filenames.push_back(str);
    }

    exec_term_cmd("rm " + rPath + fName);
}

// create a fake dropdownbox in SFML
// and yes I know this is shit, but it works for now
// this is pretty much a dump for hardcoded thrash
void GUI::create_open_dropdown(){
    float y = 90.0f;        
    for(unsigned i = 0; i < filenames.size(); i++){
        auto t = new sf::Text(filenames[i], f, 20);
        t->setPosition(5.0f, y);
        y += 30.0f;

        dialog_items.push_back(t);
    }

    dialogBG.setSize({150.0f, float(30.0f * dialog_items.size() + 10.0)});
    dialogBG.setPosition({0.0f, 80.0f});
    dialogBG.setFillColor(sf::Color::Black);
    dialogBG.setOutlineColor(sf::Color::Red);
    dialogBG.setOutlineThickness(2.0f);

    f.loadFromFile(PATH"arial.ttf");


}