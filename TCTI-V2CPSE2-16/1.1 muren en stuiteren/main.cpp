#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <cmath>

//classes
#include "ball.hpp"
#include "rectangle.hpp"

sf::Vector2f window_size;

class action {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:
	action( std::function< bool() > condition, std::function< void() > work ) : 
		condition( condition ), 
		work( work ) 
	{}

	action( sf::Keyboard::Key key, std::function< void() > work ) :
		condition(	[ key ]()->bool { return sf::Keyboard::isKeyPressed( key ); } ),
		work(work)
	{}

	void operator()(){
		if( condition() ){
			work();
		}
	}
};

int main(){
	std::cout << "Starting application \"Bouncing Ball\"\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
	window_size = sf::Vector2f{  (float)window.getSize().x, (float)window.getSize().y };

	float border_size = 20.f;
	auto wall_color = sf::Color::White;

	rectangle wallUp	{ 	wall_color, sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ window_size.x, border_size }};
	rectangle wallLeft	{ 	wall_color, sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ border_size, window_size.y }};
	rectangle wallRight	{ 	wall_color, sf::Vector2f{ window_size.x, window_size.y }, sf::Vector2f{ -border_size, -window_size.y }};
	rectangle wallDown	{ 	wall_color, sf::Vector2f{ window_size.x, window_size.y }, sf::Vector2f{ -window_size.x, -border_size }};
	
	rectangle blokje	{ sf::Color::Green, sf::Vector2f{ 225.f, 130.f } , sf::Vector2f{ 100.f, 100.f }};
	ball my_ball		{ sf::Color::Red, 	sf::Vector2f{ 100.f, 100.f }, 20.f, 10.f };

	float speed = 5.f;	
	action actions[] = {
		action( sf::Keyboard::Left,  	[&](){ blokje.move( sf::Vector2f( -speed,  0.f )); 	}),
		action( sf::Keyboard::Right, 	[&](){ blokje.move( sf::Vector2f( +speed,  0.f )); 	}),
		action( sf::Keyboard::Up,    	[&](){ blokje.move( sf::Vector2f(  0.f, -speed )); 	}),
		action( sf::Keyboard::Down, 	[&](){ blokje.move( sf::Vector2f(  0.f, +speed )); 	}),

		action( []()->bool { return true; 								},	[&](){ my_ball.move( sf::Vector2f{ 1.f, 1.f }  ); }),
		
		action( [&]()->bool { return wallLeft.collisionX( my_ball ); 	},  [&](){ my_ball.move( sf::Vector2f{ -1.f, 1.f } ); }),
		action( [&]()->bool { return wallRight.collisionX( my_ball ); 	},  [&](){ my_ball.move( sf::Vector2f{ -1.f, 1.f } ); }),
		action( [&]()->bool { return wallUp.collisionY( my_ball ); 		},  [&](){ my_ball.move( sf::Vector2f{ 1.f, -1.f } ); }),
		action( [&]()->bool { return wallDown.collisionY( my_ball );	},  [&](){ my_ball.move( sf::Vector2f{ 1.f, -1.f } ); }),

		action( [&]()->bool { return blokje.collisionX( my_ball );  	},  [&](){ my_ball.move( sf::Vector2f{ -1.f, 1.f } ); }),
		action( [&]()->bool { return blokje.collisionY( my_ball );  	},  [&](){ my_ball.move( sf::Vector2f{ 1.f, -1.f } ); }),
	};

	while (window.isOpen()) {
		for( auto & action : actions ){
			action();
		}

		window.clear();

		wallDown.draw( window );
		wallUp.draw( window );
		wallRight.draw( window );
		wallLeft.draw( window );
		blokje.draw( window );
		my_ball.draw( window );
		
		window.display();


		sf::sleep( sf::milliseconds( 20 ));

        sf::Event event;		
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}	
	
	}
	std::cout << "Terminating application\n";
	return 0;
}

