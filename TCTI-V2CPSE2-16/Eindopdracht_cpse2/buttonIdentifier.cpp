#include "buttonIdentifier.hpp"

buttonIdentifier::buttonIdentifier( Object* _object, bool* _functionality, bool _isSelected, std::string _name ) : 
    object( _object ),
    name( _name ),
    isSelected( _isSelected ), 
    functionality( _functionality )
{}

buttonIdentifier::buttonIdentifier( Object* _object, std::string _name, bool _isSelected, bool* _functionality ) : 
    object( _object ),
    name( _name ),
    isSelected( _isSelected ), 
    functionality( _functionality )
{}

void buttonIdentifier::free() {
    delete object;
    delete this;
}