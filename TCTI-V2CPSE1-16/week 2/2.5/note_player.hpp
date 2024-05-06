#ifndef _NOTE_PLAYER_HPP
#define _NOTE_PLAYER_HPP

#include "note.hpp"
#include <iostream>
#include <string>
#include <sstream>


// ===========================================================================
//
// abstract interface for a note player
//
// ===========================================================================

class note_player {
public:   
   void play( const note & n );
   std::string convert( const note & n);
};

#endif