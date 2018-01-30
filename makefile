CC = g++

LIB := -lglfw -lglad -lfreetype

SRC := $(wildcard ./src/*.cpp) $(wildcard ./src/*.c)
# figure out how to make this also replace .c
OBJ := $(SRC:./src/%.cpp=./build/%.o)
NAME := main

all: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIB)

./build/%.o: ./src/%.cpp    # TODO or .c

	$(CC) -o $@ -c $<   -I/usr/local/opt/freetype/include/freetype2

.PHONY: clean run debug

clean:
	rm ./$(NAME)
	rm build/*

run: all
	./$(NAME)
