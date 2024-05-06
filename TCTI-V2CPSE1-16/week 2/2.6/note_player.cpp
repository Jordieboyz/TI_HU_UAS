#include "note_player.hpp"



void note_player::play( const note & n )
{
    std::cout << n.frequency << ", " << n.duration << "\n";
}

std::string note_player::convert( const note & n)
{
    std::ostringstream string_stream;

    string_stream << "\t\tp.play( note{ " << n.frequency <<  ", " << n.duration << " });\n";

    return string_stream.str();
}