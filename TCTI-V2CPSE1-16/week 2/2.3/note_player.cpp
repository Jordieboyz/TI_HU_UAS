#include "note_player.hpp"


void note_player::play( const note & n )
{
   hwlib::cout << n.frequency << " en " << n.duration << "\n";
}