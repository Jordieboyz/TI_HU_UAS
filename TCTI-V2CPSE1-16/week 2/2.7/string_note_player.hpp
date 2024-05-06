#ifndef STRING_NOTE_PLAYER_HPP
#define STRING_NOTE_PLAYER_HPP

#include "note.hpp"
#include <iostream>
#include <string>
#include <sstream>


class string_note_player{
public:
   std::string convert( const note & n);
};

#endif