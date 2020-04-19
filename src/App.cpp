//
// Created by tom on 11.04.20.
//
#include <ncurses.h>

#include "App.h"
#include "MainMenu.h"
#include "QuizFactory.h"

App::App() {
    initscr(); // inicializuje screen, nastavi pamet
    cbreak(); // skonci program na CTRL+C
    noecho(); // nevypisjue se input
    keypad(stdscr, true); // zapne sipky ... (pri false je vypne)
    curs_set(0); // zneviditelni kurzor. 2. parametr bud 0/1/2 resp. neviditelny/normal/hodne_viditelny

    getmaxyx(stdscr, screenHeight, screenWidth);   // ziska rozmery obrazovky
    start_color(); // nastavi barvy ...

    // settings_menu = new Settings();
    // game = nullptr;

    /*if (!has_colors()){
         printw("Doesnt support colors");
         getch();
         return;
     }

    start_color(); // nastavi barvy ...

    init_pair(1,COLOR_RED,COLOR_WHITE); // vytvori barevny par podklad, barva pisma

    attron(COLOR_PAIR(1)); // zapne vlastnost
    attron(A_BOLD);
    attron(A_BLINK);
    printw("Let's move!"); // vytiskne na screen
    attroff(COLOR_PAIR(1)); // vypne vlastnost
    attroff(A_BOLD);
    attroff(A_BLINK);*/
}

App::~App() {
    // delete settings_menu;
    // delete game;
    endwin(); // dealokuje pamet a ukonci ncurses
}

void App::run() {
    while (true) {
        MainMenu mainMenu;
        int menuAction;
        menuAction = mainMenu.run();

        switch (menuAction) {
            case 0: {/*
                string line;
                ifstream continueFile("continue");
                if (continueFile.is_open()) {
                    int i = 0;
                    while (getline(continueFile, line)) {
                        if (i == 6)
                            break;
                        i++;
                    }
                    continueFile.close();

                    ACTION_AFTER_GAME action;
                    game = new Game(line);
                    action = game->run();

                    if (action == EXIT)
                        return;
                    if (action == BACK_TO_MENU)
                        break;
                    if (action == WON){

                    }
                    if (action == LOST){

                    }
                }*/
                break;
            }
            case 1: {                   // TODO
                QuizFactory quizFactory;
                quizFactory.setName();
                quizFactory.createQuiz();
                //mainMenu.refresh();
                continue;
            }
            case 4: {
                // TODO
            }
            case 5: {
                // TODO
            }
            case 6:
                return; // EXIT
            default: {/*
                if (menuAction >= 200 && menuAction < 300) {    // CHOOSE LEVEL
                    string line;
                    ifstream chooseLvlFile("evaluate");
                    if (chooseLvlFile.is_open()) {
                        int i = 0;
                        while (getline(chooseLvlFile, line)) {
                            if (i == (2 + 3 + 2 + 4 * (menuAction - 200)))
                                break;
                            i++;
                        }
                        chooseLvlFile.close();

                        game = new Game(line);
                        game->run();
                    }
                    break;
                }*/
            }
        }
    }
}