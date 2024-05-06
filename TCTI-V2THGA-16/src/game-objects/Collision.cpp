/*
 * Collisions.cpp
 *
 *  Created on: 12 Jan 2021
 *      Author: MiloB
 */

#include "Collision.hpp"
#include <iostream>

Collision::Collision() {

}

Collision::~Collision() {

}

bool Collision::check_renderable_collision(Renderable *object1,
		Renderable *object2, float margin, bool handleObject1Collisions) {
	/*
	 * This function also has the responsibility of keeping object 1 of
	 * overlapping with object 2, object 1 is the moving target while
	 * object 2 is static.
	 */
												    // These values are for tweaking purposes
	sf::Rect<float> object1Rect((object1->get_pos()  + sf::Vector2f(0, 0)),
								(object1->get_size() - sf::Vector2f(0, 0)));
	sf::Rect<float> object2Rect((object2->get_pos()  + sf::Vector2f(margin, margin)),
								(object2->get_size() - sf::Vector2f(margin*2, margin*2)));

	sf::Rect<float> intersectionBounds(0,0,0,0);
	if( object1Rect.intersects(object2Rect, intersectionBounds) ){

		if(handleObject1Collisions){
			if(intersectionBounds.top == object2->get_pos().y){
				//Came from the top
				object1->move(sf::Vector2f( object1->get_pos().x , object1->get_pos().y - intersectionBounds.height));
			} else if((intersectionBounds.left + intersectionBounds.width) == (object2->get_pos().x + object2->get_size().x)){
				//Came from the Right
				object1->move(sf::Vector2f(intersectionBounds.left + intersectionBounds.width , object1->get_pos().y));
			} else if((intersectionBounds.top + intersectionBounds.height) == (object2->get_pos().y + object2->get_size().y)){
				//Came from the bottom
				object1->move(sf::Vector2f(object1->get_pos().x, object1->get_pos().y + intersectionBounds.height ));
			} else if(intersectionBounds.left == object2->get_pos().x){
				//Came from the left;
				object1->move(sf::Vector2f( intersectionBounds.left - object1->get_size().x, object1->get_pos().y));
			}
		}

		return true;
	} else {
		return false;
	}
}

void Collision::handle_player_collision(Player *object1, Renderable *object2) {
	sf::Rect<float> object1Rect((object1->get_pos()  - sf::Vector2f(0, 0)),
								(object1->get_size() + sf::Vector2f(0, 0))); //Increase the objectRect
	sf::Rect<float> object2Rect((object2->get_pos()  + sf::Vector2f(0, 0)),
								(object2->get_size() - sf::Vector2f(0, 0)));

	sf::Rect<float> intersectionBounds(0,0,0,0);
	if( object1Rect.intersects(object2Rect, intersectionBounds) ){
		if(intersectionBounds.top == object2->get_pos().y){
			//Came from the top
			object1->move(sf::Vector2f(object1->get_pos().x, object1->get_last_location().y));
		}
		if((intersectionBounds.left + intersectionBounds.width) == (object2->get_pos().x + object2->get_size().x)){
			//Came from the Right
			object1->move(sf::Vector2f(object1->get_last_location().x, object1->get_pos().y));
		}
		if((intersectionBounds.top + intersectionBounds.height) == (object2->get_pos().y + object2->get_size().y)){
			//Came from the bottom
			object1->move(sf::Vector2f(object1->get_pos().x, object1->get_last_location().y));
		}
		if(intersectionBounds.left == object2->get_pos().x){\
			//Came from the left;
			object1->move(sf::Vector2f(object1->get_last_location().x, object1->get_pos().y));
		}
//			return NONE_COLLISION_DIRECTION;
	} else {
	}

}
