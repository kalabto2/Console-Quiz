# PŘÍKAZY

PROGRAM=kalabto2
CC=g++
CFLAGS=-std=c++11 -Wall -pedantic -lncurses -lpthread #-Wextra -g -Wno-long-long -O0 -ggdb

## Spuštění programu 'all'
.PHONY: all
all: compile doc

## Vygenerování dokumentace
.PHONY: doc
doc: src/main.cpp

## Kompilace
compile: $(PROGRAM)

## Spuštění
run: compile
	./$(PROGRAM)

## Spuštění programu 'main'
main: build/main
	./build/main

## Odstranění vygenerovatelných souborů
.PHONY: clean
clean:
	rm -rf ./build ./doc ./$(PROGRAM)


# PROGRAMY
## Program 'kalabto2'
$(PROGRAM): build/main.o build/MainMenu.o build/Quiz.o
	mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@

# Třídy
## Třída 'main.cpp'
build/main.o: src/main.cpp src/Quiz.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

## Třída 'MainMenu.cpp'
build/MainMenu.o: src/MainMenu.cpp src/MainMenu.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

## Třída 'Quiz.cpp'
build/Quiz.o: src/Quiz.cpp src/Quiz.h src/MainMenu.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@