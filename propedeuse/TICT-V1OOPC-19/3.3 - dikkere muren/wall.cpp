#include "wall.hpp"


void wall::update(){
    update_count++;
      
    if(update_count%update_interval==0){
        filled = !filled;
    }
}

void wall::draw() {
    if(filled){
        for (int i = location.x; i < end.x+1; i++){
            for (int j = location.y; j < end.y+1; j++){
                w.write(hwlib::xy(i, j), hwlib::color(255, 255, 255));
            }
        }
    } else {
        rectangle::draw();
    }
}