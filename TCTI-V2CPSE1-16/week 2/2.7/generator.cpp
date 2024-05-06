#include "string_note_player.hpp"
#include "rtttl_player.hpp"

const char one[]          = "NumberOne:d=16,o=5,b=168:4f.,8c6,16b5,16c6,16b5,16c6,8b5,8c6,4g#5,4f.,8f,8g#5,8c6,4c#6,4g#5,4c#6,4d#6,8c6,8c#6,8c6,8c#6,2c6";


int main(){
    auto p = string_note_player();
    string_converter( p, one );
}