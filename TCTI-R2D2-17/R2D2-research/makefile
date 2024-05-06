CC 				:= gcc
CXX				:= g++
LD				:= g++
AR				:= ar

CC_FLAGS		:= -pedantic -Wall -std=c99 -I BLIL
CXX_FLAGS		:= -pedantic -Wall -std=c++17 -I BLIL \
					-I test-environment
LD_FLAGS		:= -lsfml-graphics -lsfml-window -lsfml-system

BLIL_SRC		:= $(shell find BLIL/src -name "*.c")
BLIL_OBJ		:= $(patsubst %.c, %.o, $(BLIL_SRC))

TEST_ENV_SRC	:= $(shell find test-environment/src -name "*.cpp")
TEST_ENV_OBJ	:= $(patsubst %.cpp, %.o, $(TEST_ENV_SRC))

.PHONY: clean run

main: $(BLIL_OBJ) $(TEST_ENV_OBJ)
	$(LD) -o $@ $^ $(LD_FLAGS) 
	
run: main
	./main test-environment/res/test-images/lenne2.png

clean: 
	rm $(BLIL_OBJ) $(TEST_ENV_OBJ)

%.o: %.c
	$(CC) -c -o $@ $(CC_FLAGS) $^

%.o: %.cpp
	$(CXX) -c -o $@ $(CXX_FLAGS) $^