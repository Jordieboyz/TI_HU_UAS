#include "victim.hpp"

void victim::update(){
    const int locX = rectangle::start_x;
    const int locY = rectangle::start_y;
    const int sizeX = drawable::size.x;
    const int sizeY = drawable::size.y;
    // std::cout << drawable::location << std::endl;
    // std::cout << drawable::size << std::endl << std::endl;
    // std::cout << "start_x: " << rectangle::start_x << " start_y: " << rectangle::start_y << " end_x: " << rectangle::end_x << " end_y: " << rectangle::end_y << std::endl;
    // std::cout << "drawable::location: " << drawable::location << " drawable::size: " << drawable::size << std::endl << std::endl;
    if(updateTime){
        if(rectangle::start_x < locX+(sizeX/2)){
            drawable::location.x += 1;           
            rectangle::start_x += 1;
        }
        if(rectangle::start_y < locY+(sizeY/2)){         
            drawable::location.y += 1;
            rectangle::start_y += 1;
        }
        if(rectangle::end_x > rectangle::end_x-(sizeX/2)){
            rectangle::end_x -= 1;
            drawable::size.x -= 1;
        }
        if(rectangle::end_y > rectangle::end_y-(sizeY/2)){
            rectangle::end_y -= 1;
            drawable::size.y -= 1;
        }            
        updateTime = false;
    }
}


void victim::interact(drawable& other){
    if(this != & other){
        if(overlaps( other ) && (drawable::location != hwlib::xy(0,0) || drawable::size != hwlib::xy(0, 0))){
            std::cout <<"victim raakt iets" << std::endl;
             updateTime = true;
        }
    }
}