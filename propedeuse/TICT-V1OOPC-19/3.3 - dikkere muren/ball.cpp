#include "ball.hpp"

void ball::update(){
    location = location + speed; 
}

void ball::interact(drawable & other){
    if( this != & other){
        if( overlaps( other )){
            speed.x *= -1;
            speed.y *= -1;        
        }
    }
}   