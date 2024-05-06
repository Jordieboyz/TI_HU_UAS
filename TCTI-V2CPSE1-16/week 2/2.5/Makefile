gcc := g++ -std=c++17
ln := g++ -std=c++17
rm := rm -f

.PHONY: build clean run

build: main.exe melody.cpp
run: build

clean: 
	$(rm) *.o main.exe 

main.exe: main.o rtttl_player.o note_player.o 
	$(ln) main.o rtttl_player.o note_player.o -o main.exe
	
main.o: generator.cpp rtttl_player.hpp note_player.hpp 
	$(gcc) -c generator.cpp -o main.o

rtttl_player.o: rtttl_player.cpp rtttl_player.hpp note_player.hpp
	$(gcc) -c rtttl_player.cpp -o rtttl_player.o

note_player.o: note_player.cpp note_player.hpp note.hpp 
	$(gcc) -c note_player.cpp -o note_player.o

melody.cpp : main.exe
	./main.exe > melody.cpp
