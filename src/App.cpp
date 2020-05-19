//
// Created by tom on 11.04.20.
//
#include <ncurses.h>

#include "App.h"
#include "MainMenu.h"
#include "QuizFactory.h"
#include "ShowRoom.h"

App::App() {
    initscr(); // inicializuje screen, nastavi pamet
    cbreak(); // skonci program na CTRL+C
    noecho(); // nevypisjue se input
    keypad(stdscr, true); // zapne sipky ... (pri false je vypne)
    curs_set(0); // zneviditelni kurzor. 2. parametr bud 0/1/2 resp. neviditelny/normal/hodne_viditelny

    getmaxyx(stdscr, screenHeight, screenWidth);   // ziska rozmery obrazovky
    start_color(); // nastavi barvy ...

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
    endwin(); // dealokuje pamet a ukonci ncurses
}

void App::run() {
    while (true) {
        MainMenu mainMenu;
        MainMenu::MENU_ACTION menuAction;
        menuAction = mainMenu.run();

        switch (menuAction) {
            case MainMenu::START_QUIZ: {
                QuizFactory quizFactory;
                string quizId = quizFactory.selectQuiz();
                Quiz quiz(quizId); // loads quiz from file
                ShowRoom showRoom(quiz);
                showRoom.StartQuiz();

                // todo
                break;
            }
            case MainMenu::CREATE_QUIZ: {
                QuizFactory quizFactory;
                quizFactory.setName();
                quizFactory.createQuiz();
                break;
            }
            case MainMenu::EVALUATE_QUIZ: {
                // TODO
            }
            case MainMenu::EXPORT_TO_TXT_QA: {}
            case MainMenu::EXPORT_TO_TXT_Q: {}
            case MainMenu::EXPORT_TO_TXT_QS: {}
            case MainMenu::EXPORT_TO_TXT_QAS: {}    // TODO
            case MainMenu::EXPORT_TO_TXT_AS: {      // TODO
                QuizFactory quizFactory;
                string quizId = quizFactory.selectQuiz();
                Quiz quiz(quizId); // loads quiz from file
                ShowRoom exports(quiz);
                exports.Export(menuAction);
                break;
            }
            case MainMenu::NONE: {
                // TODO ?
            }
            case MainMenu::EXIT:
                return;
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