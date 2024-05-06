#include "canvasShape.hpp"

circle::circle( sf::Color _color, float _radius) : 
    circ( _radius )
{
    circ.setFillColor( _color );
}

circle::circle( sf::Vector2f _position, sf::Color _color, float _radius ):
    circ( _radius )
{
    circ.setFillColor( _color );
    circ.setPosition( _position );
}

void circle::draw( sf::RenderWindow& window ){
    window.draw( circ );
}

sf::Vector2f circle::getPosition(){
    return circ.getPosition();
}

sf::Vector2f circle::getSize(){
    return sf::Vector2f{ circ.getRadius()*2, circ.getRadius()*2 };
}

void circle::setPosition( sf::Vector2f position ){
    circ.setPosition( position );
}

sf::Color circle::getColor(){ 
    return circ.getFillColor();
}

void circle::setColor( sf::Color _color ){
    circ.setFillColor( _color );
}

bool circle::contains( sf::Vector2f point ){
    return circ.getGlobalBounds().contains( point );
}

void circle::turnBorder( float thickness, sf::Color color ){
    circ.setOutlineColor( color );
    circ.setOutlineThickness( thickness );
}

void circle::setScale( sf::Vector2f factor ){
    circ.setScale( circ.getScale() + factor );
}

sf::Vector2f circle::getScale(){
    return circ.getScale();
}

rect::rect( sf::Color _color, sf::Vector2f _size ) :
    rectangle( _size )
{
    rectangle.setFillColor( _color );
}

rect::rect( sf::Vector2f _position, sf::Color _color, sf::Vector2f _size ):
    rectangle( _size )
{
    rectangle.setFillColor( _color );
    rectangle.setPosition( _position );
}

void rect::draw( sf::RenderWindow& window){
    window.draw( rectangle );
}

sf::Vector2f rect::getPosition(){
    return rectangle.getPosition();
}

sf::Vector2f rect::getSize(){
    return rectangle.getSize();
}

void rect::setPosition( sf::Vector2f position ){
    rectangle.setPosition( position );
}

void rect::setColor( sf::Color color ){
    rectangle.setFillColor( color );
}

sf::Color rect::getColor(){
    return rectangle.getFillColor();
}

bool rect::contains( sf::Vector2f point ){
    return rectangle.getGlobalBounds().contains( point );
}

void rect::turnBorder( float thickness, sf::Color color ){
    rectangle.setOutlineColor( color );
    rectangle.setOutlineThickness( thickness );
}

void rect::setScale( sf::Vector2f factor ){
    auto scale = rectangle.getScale();
    rectangle.setScale( rectangle.getScale() + factor );
}

sf::Vector2f rect::getScale(){
    return rectangle.getScale();
}