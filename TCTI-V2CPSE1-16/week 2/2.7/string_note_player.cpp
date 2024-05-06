#include "string_note_player.hpp"

std::string string_note_player::convert( const note & n)
{
    std::ostringstream string_stream;

    string_stream << "\t\tp.play( note{ " << n.frequency <<  ", " << n.duration << " });\n";

    return string_stream.str();
}