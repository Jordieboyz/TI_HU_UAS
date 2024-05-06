gcc := g++ -std=c++17
ln := g++ -std=c++17
rm := rm -f

.PHONY: build clean

build: main.exe wilhelmus.asm build_app

run: run_app

clean: 
	$(rm) *.o main.exe

main.exe: main.o 
	$(ln) main.o -o main.exe

main.o: main.cpp 
	$(gcc) -c main.cpp -o main.o

wilhelmus.asm: main.exe
	./main.exe > wilhelmus.asm

build_app:       
	$(MAKE) -C ../4.4

run_app:       
	$(MAKE) -C ../4.4 run


