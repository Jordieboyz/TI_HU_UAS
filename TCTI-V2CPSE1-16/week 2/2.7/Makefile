gcc := g++ -std=c++17
ln := g++ -std=c++17
rm := rm -f

.PHONY: build nclean

build: gen.exe melody.cpp

nclean:
	$(rm) *.o *.exe melody.cpp 

gen.exe: gen.o rtttl_player.o string_note_player.o
	$(ln) gen.o rtttl_player.o string_note_player.o -o gen.exe
	
gen.o: generator.cpp rtttl_player.hpp string_note_player.hpp note_player.hpp
	$(gcc) -c generator.cpp -o gen.o

rtttl_player.o: rtttl_player.cpp rtttl_player.hpp string_note_player.hpp note_player.hpp
	$(gcc) -c rtttl_player.cpp -o rtttl_player.o

string_note_player.o: string_note_player.cpp string_note_player.hpp note.hpp 
	$(gcc) -c string_note_player.cpp -o string_note_player.o

melody.cpp : gen.exe
	./gen.exe > melody.cpp


HEADERS += melody.hpp
SOURCES += melody.cpp
HEADERS += note_player_gpio.hpp
SOURCES += note_player_gpio.cpp

RELATIVE := $(RELATIVE)../../../v2cpse1-examples/
include $(RELATIVE)Makefile.due