
#include <iostream>

#include "game-states/GameStateMachine.hpp"
#include "particles/ParticleManager.hpp"

#define CLIENT

#ifdef CLIENT

sf::Color HSVtoRGB(float H, float S,float V){
    if(H>360 || H<0 || S>100 || S<0 || V>100 || V<0){
        return sf::Color(0,0,0); //Invalid values
    }
    float s = S/100;
    float v = V/100;
    float C = s*v;
    float X = C*(1-abs(fmod(H/60.0, 2)-1));
    float m = v-C;
    float r,g,b;
    if(H >= 0 && H < 60){
        r = C,g = X,b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X,g = C,b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0,g = C,b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0,g = X,b = C;
    }
    else if(H >= 240 && H < 300){
        r = X,g = 0,b = C;
    }
    else{
        r = C,g = 0,b = X;
    }
    int R = (r+m)*255;
    int G = (g+m)*255;
    int B = (b+m)*255;

    return sf::Color(R,G,B);
}

std::ostream& operator<<( std::ostream& os, const sf::Vector2f lhs ){
	return os << "{ " << lhs.x << ", " << lhs.y << " }";
}

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "SuperHotline");
	window.setFramerateLimit(FPS_SECOND);

	std::srand(std::time(0));

	GameStateMachine  stateMachine;

	GameData gData;
	ParticleManager Mang(&gData);

	sf::Texture cursorTexture;
	cursorTexture.loadFromFile("res/cursor.png");
	sf::Sprite cursor(cursorTexture);

	gData.pStateMachine = &stateMachine;
	gData.pRenderWindow = &window;
	gData.fTimeScaleFactor = 1.0f;
	gData.pParticleManager = &Mang;
//	gData.cursor = &cursor;



//	window.setMouseCursorVisible(false);

	stateMachine.set_state(new MainMenuState(&gData));


	float h = 0;
	float b = 70;
	float s = 70;


	bool increase = false;

	while (window.isOpen())
	{

		float speed = 0.9 * gData.fTimeScaleFactor;
		window.clear(HSVtoRGB(h,b,s));
		if(increase){
			h += speed;
			if(h >= 350){
				increase = false;
			}
		} else {
			h -= speed;
			if(h <= 0){
				increase = true;
			}
		}

		stateMachine.update();
		window.display();


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) { window.close(); };
			if (event.type != gData.evCurrentEvent.type) { gData.evCurrentEvent = event; };
			if(event.type == sf::Event::MouseButtonReleased){
				if(event.mouseButton.button == sf::Mouse::Left){
					gData.key_released = true;
				}
			} else {
				gData.key_released = false;
			}
		}
	}
}

#endif

#ifdef SERVER

#include "game-states/ServerState.hpp"

int main(void) {
	GameStateMachine  stateMachine;

	GameData gData;
	ParticleManager Mang(&gData);

	gData.pStateMachine = &stateMachine;
	gData.pRenderWindow = nullptr;
	gData.fTimeScaleFactor = 1.0f;
	gData.pParticleManager = &Mang;

	ServerState serv(&gData);
	while(1)
		serv.update();

	stateMachine.set_state(new MainMenuState(&gData));
}
#endif
