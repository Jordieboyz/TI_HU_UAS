#include "object.hpp"
#include "hud.hpp"
#include "Button.hpp"
#include "canvasShape.hpp"
#include "canvas.hpp"

#include "factory.hpp"
#include "buttonIdentifier.hpp"

int findIndexOfButtonName( std::vector<hudButton*>& buttons,  std::string _name ){
    return std::distance(buttons.begin(), std::find_if(buttons.begin(), buttons.end(), [&](hudButton* button)->bool { return button->getName() == _name;}));
}

void removeElement( std::vector<buttonIdentifier*>& vector, buttonIdentifier* b ){
    vector.erase( vector.begin() + std::distance(vector.begin(),std::find(vector.begin(), vector.end(), b)));
    b->free();
}

buttonIdentifier* createButtonIdentifier( std::vector<hudButton*>& _buttons, std::string name, bool* func ){
    buttonIdentifier* x = new buttonIdentifier( _buttons[ findIndexOfButtonName( _buttons, name ) ], func  );
    return x;
}

void selectUniqueFunction( std::vector<bool*>& array, bool* function = nullptr){
    for( auto a : array ){
        if( a == function ){
            *a = true;
        } else {
            *a = false;
        }
    }
}

std::string getSavedFile( std::vector<buttonIdentifier*>& vector){
    std::string fileName;
    std::cout << "Wil je een ander ontwerp toevoegen aan je huidige ontwerp? (ja / nee) \nzo ja, geef het pad van het \".txt\" bestand\n\tpad: ";
    std::cin >> fileName;
    if( fileName != "nee" ){
        std::ifstream file( fileName );
        getShapeFile( vector, file );
    } else {
        std::ifstream file( "res/objecten.txt" );
        getShapeFile( vector, file);
    }
    return fileName;
}

int main() {
    auto grid = sf::RectangleShape( sf::Vector2f{ grid_length, grid_height } );
    grid.setPosition( sf::Vector2f{ HUD_length , 0.f } );

    auto _canvas = canvas();
    auto _buttons = *_canvas.getButtonList();

    bool newShapeClicked, colorButtonClicked, deleteButtonClicked, selectButtonClicked, moveButtonClicked, saveButtonClicked, borderButtonClicked, plusButtonClicked, minusButtonClicked, openButtonClicked;
    std::vector<bool*> functionalities = {
        &newShapeClicked, &colorButtonClicked, &deleteButtonClicked, &selectButtonClicked, &moveButtonClicked, 
        &saveButtonClicked, &borderButtonClicked, &plusButtonClicked, &minusButtonClicked, &openButtonClicked
    };

    auto _rect = createButtonIdentifier( _buttons, "rectButton", &newShapeClicked  );
    auto _circle = createButtonIdentifier( _buttons, "circleButton", &newShapeClicked );
    auto _delete = createButtonIdentifier( _buttons, "deleteButton", &deleteButtonClicked );
    auto _select = createButtonIdentifier( _buttons, "selectButton", &selectButtonClicked );
    auto _move = createButtonIdentifier( _buttons, "moveButton", &moveButtonClicked );
    auto _save = createButtonIdentifier( _buttons, "saveButton", &saveButtonClicked );
    auto _border = createButtonIdentifier( _buttons, "borderButton", &borderButtonClicked );
    auto _plus = createButtonIdentifier( _buttons, "plusButton", &plusButtonClicked );
    auto _minus = createButtonIdentifier( _buttons, "minusButton", &minusButtonClicked );
    auto _open = createButtonIdentifier( _buttons, "openButton", &openButtonClicked );

    std::array< std::vector<buttonIdentifier*>, 2> canvasObjects = {
        std::vector<buttonIdentifier*>{
            createButtonIdentifier( _buttons, "blue",   &colorButtonClicked ),
            createButtonIdentifier( _buttons, "red",    &colorButtonClicked ),
            createButtonIdentifier( _buttons, "yellow", &colorButtonClicked ),
            createButtonIdentifier( _buttons, "green",  &colorButtonClicked ),
            createButtonIdentifier( _buttons, "magenta",&colorButtonClicked ),
            createButtonIdentifier( _buttons, "cyan",   &colorButtonClicked ),
            createButtonIdentifier( _buttons, "white",  &colorButtonClicked ),
            _rect, _circle, _delete, _select, _move, _save, _border, _plus, _minus, _open
        },
        std::vector<buttonIdentifier*>{}
    };

    sf::Color new_col = sf::Color::White;
    buttonIdentifier* temp = nullptr;
    std::string fileName = "new.txt";

    while( window.isOpen()){

        window.clear();  
        _canvas.draw( window );
        
        if ( temp != nullptr ){
            if( temp->isSelected == false ){
                temp->object->turnBorder( 0.0 );
            }
            if( temp->isSelected == true ){
                temp->object->turnBorder( 2.0, sf::Color::White );
            }
        }

        for( auto a : canvasObjects[0] ){
            a->object->draw( window );
            if( !newShapeClicked ){
                if( _canvas.checkTouch( a->object , window) ){

                    a->isSelected = true;
                     if( temp != nullptr  && !_move->isSelected ){
                        temp->object->turnBorder( 0.0 );
                    }

                    selectUniqueFunction( functionalities, a->functionality );
                    if( _rect->isSelected ){
                        temp = new buttonIdentifier( new rect( a->object->getColor(), shapeButtonSize ), "RECT", true );
                    }
                    else if( _circle->isSelected ){
                        temp = new buttonIdentifier( new circle( a->object->getColor(), shapeButtonSize.y/2.f ), "CIRCLE", true );
                    }
                    else if( colorButtonClicked ){
                        new_col = a->object->getColor();
                    }
                    else if( _delete->isSelected || _select->isSelected ){
                        temp = nullptr;

                    if( selectButtonClicked ){
                        if( temp != nullptr ){
                            temp->object->turnBorder( 0.0 );
                        }
                    }
                    }
                }
                a->isSelected = false;
            }
        }

        for( auto a : canvasObjects[1] ){
            if( !grid.getGlobalBounds().contains( a->object->getPosition()) ){
                removeElement( canvasObjects[1], a );
            }
            a->object->draw( window );
            if( _canvas.checkTouch( a->object , window) ){
                a->isSelected = true;
                if( deleteButtonClicked ){
                    removeElement( canvasObjects[1], a );
                }
                if( selectButtonClicked ){
                    if( temp != nullptr ){
                        temp->object->turnBorder( 0.0 );
                    }
                    temp = a;
                }
            } 
        }
        
        if( newShapeClicked ){
            temp->object->setPosition( (static_cast<sf::Vector2f>( sf::Mouse::getPosition( window )) - sf::Vector2f{ temp->object->getSize().x/2, temp->object->getSize().y/2}) );
            temp->object->draw( window );
        }

        if( moveButtonClicked ){
            if( temp != nullptr ){
                if( _canvas.checkTouch( temp->object, window )){
                    if( grid.getGlobalBounds().contains( temp->object->getPosition() )){
                        temp->object->move( (static_cast<sf::Vector2f>( sf::Mouse::getPosition( window )) - sf::Vector2f{ (temp->object->getSize().x/2)* temp->object->getScale().x, (temp->object->getSize().y/2)* temp->object->getScale().y}));
                        temp->object->draw( window );
                    } 
                }
            }
        }

        window.display();

        sf::Event event;
        while( window.pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                window.close();
            }
            if( event.type == sf::Event::MouseButtonReleased ){
                if( event.mouseButton.button == sf::Mouse::Left ){
                    // place isSelected on grid
                    if( newShapeClicked ){
                        if( grid.getGlobalBounds().contains( temp->object->getPosition() )){
                            canvasObjects[1].push_back( temp );
                             temp->isSelected = false;
                        } else {
                            temp->free();
                            temp = nullptr;
                        }
                       std::cout << canvasObjects[1].size() << std::endl;
                        newShapeClicked = false;
                    }
                    // change_color: shapes, selected shape
                    if( colorButtonClicked ){
                        _circle->object->setColor( new_col );
                        _rect->object->setColor( new_col );
                        if( temp != nullptr ){
                            temp->object->setColor( new_col );
                        }
                        colorButtonClicked = false;
                    }
                    if( temp != nullptr ){
                        if( borderButtonClicked ){
                            temp->object->turnBorder( 4.5, new_col );
                            borderButtonClicked = false;
                        }
                        if( plusButtonClicked ){
                            temp->object->setScale( sf::Vector2f{0.5, 0.5} );
                            plusButtonClicked = false;
                        }
                        if( minusButtonClicked ){
                            temp->object->setScale( sf::Vector2f{-0.5, -0.5});
                            if( temp->object->getScale().x <= 0 || temp->object->getScale().y <= 0){ removeElement( canvasObjects[1], temp ); temp = nullptr; }
                            minusButtonClicked = false;
                        }
                    }
                    if( openButtonClicked ){
                        fileName = getSavedFile( canvasObjects[1] );
                        openButtonClicked = false;
                    }
                    if( saveButtonClicked ){

                        _colorStruct colours[]{
                            { "blue",   sf::Color::Blue     },
                            { "red",    sf::Color::Red      },
                            { "yellow", sf::Color::Yellow   },
                            { "green",  sf::Color::Green    },
                            { "magenta",sf::Color::Magenta  },
                            { "cyan",   sf::Color::Cyan     },
                            { "white",  sf::Color::White     },
                        };

                        std::stringstream ss;
                        std::string color;
                        sf::Vector2f size;
                        for( auto x : canvasObjects[1] ){
                            for( auto i : colours ){
                                if( x->object->getColor() == i.color ){
                                    color = i.name;
                                }
                            }
                            if( x->name == "CIRCLE" ){ 
                                size = sf::Vector2f{ x->object->getSize().x/2 * x->object->getScale().x, x->object->getSize().y/2 * x->object->getScale().y };
                            } else { 
                                size = sf::Vector2f{ x->object->getSize().x * x->object->getScale().x, x->object->getSize().y * x->object->getScale().y }; 
                            }
                            ss << x->object->getPosition() << " " << x->name << " " << color << " " << size << std::endl;
                        }

                        std::ofstream oStream( fileName );
                        oStream << ss.str();
                        oStream.close();
                        saveButtonClicked = false;
                    }
                }
            }
        }
    } 
}  