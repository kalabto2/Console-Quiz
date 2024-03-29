# PŘÍKAZY

PROGRAM=kalabto2
CC=g++
CFLAGS=-std=c++14 -Wall -pedantic -lncurses # -Wextra -g -Wno-long-long -O0 -ggdb
#DIRNAME=files2/answers files2/answerSheets files2/exports files2/questions files2/quizzes files2/sheets

## Spuštění programu 'all'
.PHONY: all
all: compile doc

## Vygenerování dokumentace
.PHONY: doc
doc: src/main.cpp src/App.h
	doxygen Doxyfile

## Kompilace
compile: $(PROGRAM)

## Spuštění
run: compile
	./$(PROGRAM) TEACHER

## Spuštění programu 'main'
main: build/main
	./build/main

## Odstranění vygenerovatelných souborů
.PHONY: clean
clean:
	rm -rf ./build ./doc ./$(PROGRAM)

.PHONY: dir
dir:
	mkdir -p $(DIRNAME)

# PROGRAMY
## Program 'kalabto2'
$(PROGRAM): build/main.o build/MainMenu.o build/App.o build/QuizFactory.o build/Quiz.o build/Sheet.o build/Question.o build/Answer.o build/ShowRoom.o build/AnswerSheet.o
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
build/App.o: src/App.cpp src/App.h src/MainMenu.h src/QuizFactory.h src/ShowRoom.h
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

## Třída 'ShowRoom.cpp'
build/ShowRoom.o: src/ShowRoom.cpp src/ShowRoom.h src/Quiz.h src/MainMenu.h src/AnswerSheet.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

## Třída 'AnswerSheet.cpp'
build/AnswerSheet.o: src/AnswerSheet.cpp src/AnswerSheet.h src/Quiz.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@