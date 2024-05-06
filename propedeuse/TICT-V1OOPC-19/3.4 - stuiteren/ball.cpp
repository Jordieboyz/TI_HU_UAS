#include "ball.hpp"

void ball::update(){
    location = location + speed; 
}

void ball::interact(drawable & other){
    if( this != & other){
        if( overlaps( other )){
             //std::cout << "speed x:" << speed.x << std::endl << "speed y: " << speed.y << std::endl;
             //std::cout << "bounce x:" << other.getBounce().x << std::endl << "bounce y: " << other.getBounce().y << std::endl;
            speed.x *= other.getBounce().x;
            speed.y *= other.getBounce().y;        
        }
    }
} 