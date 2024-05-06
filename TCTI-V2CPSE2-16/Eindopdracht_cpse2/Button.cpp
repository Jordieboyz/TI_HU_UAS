#include "Button.hpp"


shape::shape( sf::CircleShape circle, std::string name, std::string _texture) :
    sf::Shape( circle ), 
    name( name )
{
    if( _texture != ""){
        text.loadFromFile( _texture );
        this->setTexture( &text );
    }
    size = sf::Vector2f{ circle.getRadius(), 0};
}

shape::shape( sf::RectangleShape rect, std::string name, std::string _texture) :
    sf::Shape( rect ), 
    name( name )
{
    if( _texture != ""){
        text.loadFromFile( _texture );
        this->setTexture( &text );
    }
    size = rect.getSize();
}


std::string shape::getName(){
    return name;
}

sf::Vector2f shape::getSize(){
    return size;
}

std::size_t shape::getPointCount() const { 
    return this->getPointCount(); 
}

sf::Vector2f shape::getPoint( std::size_t index ) const {
    return this->getPoint( index );
}


hudButton::hudButton( shape _shape ) :
    shap( _shape )
{}

sf::Color hudButton::getColor(){
    return shap.getFillColor();
}

void hudButton::setColor( sf::Color _color ){
    shap.setFillColor( _color );
}

void hudButton::draw( sf::RenderWindow & window ){
    window.draw( shap );
}

bool hudButton::contains( sf::Vector2f mousePosition ){
    if( shap.getGlobalBounds().contains( mousePosition )){ 
        return true;
    }
    return false;
}

sf::Vector2f hudButton::getSize(){
    return shap.getSize();
}

sf::Vector2f hudButton::getPosition(){
    return shap.getPosition();
}

void hudButton::setPosition( sf::Vector2f position){
    shap.setPosition( position );
}

std::string hudButton::getName(){
    return shap.getName();
}

void hudButton::turnBorder( float thickness, sf::Color color ){
    shap.setOutlineColor( color );
    shap.setOutlineThickness( thickness );
}

void hudButton::setScale( sf::Vector2f factors ){
    shap.setScale( shap.getScale() + factors );
}

sf::Vector2f hudButton::getScale(){
    return shap.getScale();
}