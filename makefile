CC = g++

LIB := -lglfw -lglad -lfreetype

SRC := $(wildcard ./ManyHats/*.cpp) $(wildcard ./ManyHats/*.c)

# figure out how to make this also replace .c
OBJ := $(SRC:./ManyHats/%.cpp=./build/%.o)
NAME := ./ManyHats/main

all: $(OBJ) $(GLSL)
	$(CC) -o $(NAME) $(OBJ) $(LIB)

./build/%.o: ./ManyHats/%.cpp    # TODO or .c
	$(CC) -o $@ -c $< -I/usr/local/opt/freetype/include/freetype2

.PHONY: clean run debug

clean:
	rm ./$(NAME)
	rm build/*

run: all
	./$(NAME)

debug:
	@echo $(SRC)
	@echo $(OBJ)
