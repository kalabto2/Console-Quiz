# PŘÍKAZY

PROGRAM=kalabto2
CC=g++
CFLAGS=-std=c++17 -Wall -pedantic -lncurses -lpthread #-Wextra -g -Wno-long-long -O0 -ggdb

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
$(PROGRAM): build/main.o build/MainMenu.o build/App.o build/QuizFactory.o build/Quiz.o build/Sheet.o build/Question.o build/Answer.o
	mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@

# Třídy
## Třída 'main.cpp'
build/main.o: src/main.cpp src/App.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

## Třída 'MainMenu.cpp'
build/MainMenu.o: src/MainMenu.cpp src/MainMenu.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

## Třída 'App.cpp'
build/App.o: src/App.cpp src/App.h src/MainMenu.h src/QuizFactory.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

## Třída 'QuizFactory.cpp'
build/QuizFactory.o: src/QuizFactory.cpp src/QuizFactory.h src/Quiz.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

## Třída 'Quiz.cpp'
build/Quiz.o: src/Quiz.cpp src/Quiz.h src/Sheet.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

## Třída 'Sheet.cpp'
build/Sheet.o: src/Sheet.cpp src/Sheet.h src/Question.h src/Answer.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

## Třída 'Question.cpp'
build/Question.o: src/Question.cpp src/Question.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

## Třída 'Answer.cpp'
build/Answer.o: src/Answer.cpp src/Answer.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@
