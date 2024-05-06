#ifndef NOTE_PLAYER_HPP
#define NOTE_PLAYER_HPP

#include "note.hpp"

class note_player {
public:   
   virtual void play( const note & n) = 0; 
};


#endif