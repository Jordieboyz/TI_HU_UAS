#include "graphicInterface.hpp"

void graphicInterface::main(){
    sf::RenderWindow window{ sf::VideoMode{ window_sizeX, window_sizeY }, "TicTacToe" };

    move m;
    int undo = 0;
    while( window.isOpen()){
        if (gameOver != true){
        
            text.setString( "it's   " + players[list_of_commands[0][0]%2].getName() + "'s    turn" );
            text.setPosition( sf::Vector2f{ ((float)window_sizeX/2)-(text.getGlobalBounds().width/2), 0 } );

            drawBoard( after());
            for( int i = 0; i < (int)bstate.size(); i++){
                for( int j = 0; j < (int)bstate[i].size(); j++){
                    window.draw( bstate[i][j] );
                    if( bstate[i][j].getGlobalBounds().contains( ( static_cast<sf::Vector2f>(sf::Mouse::getPosition())))){
                            m = { i, j }; 
                    } 
                }
            }
            
            if( list_of_commands[0][0] > 4){
                int winner = checkWinner( after() );
                if( winner != 0){  
                    gameOver = true;
                    window.clear();
                    for (auto a : players){
                        if( winner == a.getPlayerNumber()){
                            text.setString( a.getName() + " won!!");   
                            text.setFillColor( sf::Color::Green );
                        }
                    }
                    if( winner == -1 ){
                        text.setString( "it's a tie..." );   
                        text.setFillColor( sf::Color::Red );
                    }
                    text.setPosition( sf::Vector2f{ ((float)window_sizeX/2)-(text.getGlobalBounds().width/2), ((float)window_sizeY/2)-(text.getGlobalBounds().height/2) } );
                    
                    t.setString( "Click the right button on the mouse to exit");
                    t.setPosition( sf::Vector2f{ ((float)window_sizeX/2)-(t.getGlobalBounds().width/2), ((float)window_sizeY)-(t.getCharacterSize()+10) } );
                }
                window.draw( t );
            }

            window.draw( text );
            window.display(); 
        } else {
            if ( sf::Mouse::isButtonPressed( sf::Mouse::Right ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Space )){
                break;
            }
        }    
        sf::Event event;
        while( window.pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                    window.close();
            }
            if ( event.type == sf::Event::MouseButtonPressed ){
                if (event.mouseButton.button == sf::Mouse::Left ){
                    undo = 0;
                    add_move( m ); 
                }
                if (event.mouseButton.button == sf::Mouse::Right ){
                    if (undo == 0){
                        undo++;
                        remove_move( list_of_commands[0][0] );    
                    }
                }  
            }
        }
    }
}