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

void App::run(bool studentMode) {
    while (true) {
        MainMenu mainMenu (studentMode);
        MainMenu::MENU_ACTION menuAction;
        menuAction = mainMenu.run(studentMode);

        try {
            /// Makes certain action
            switch (menuAction) {
                case MainMenu::START_QUIZ: {
                    string quizId = ShowRoom::selectQuiz();
                    if (quizId.empty()) break;
                    ShowRoom showRoom(quizId);
                    showRoom.setAuthor(username);
                    showRoom.StartQuiz();
                    break;
                }
                case MainMenu::CREATE_QUIZ: {
                    QuizFactory quizFactory;
                    quizFactory.setName();
                    quizFactory.createQuiz();
                    break;
                }
                case MainMenu::EVALUATE_QUIZ: {
                    string quizId = ShowRoom::selectQuiz();
                    if (quizId.empty()) break;
                    string answerSheetId = ShowRoom::selectAnswersheet(quizId);
                    if (answerSheetId.empty()) break;
                    ShowRoom showRoom(quizId, answerSheetId);
                    showRoom.StartQuiz(false);
                    break;
                }
                case MainMenu::EXPORT_TO_TXT_QA: {
                }
                case MainMenu::EXPORT_TO_TXT_Q: {
                }
                case MainMenu::EXPORT_TO_TXT_QS: {
                    string quizId = ShowRoom::selectQuiz();
                    if (quizId.empty()) break;
                    Quiz quiz(quizId);
                    ShowRoom exports(quiz);
                    exports.Export(menuAction);
                    break;
                }
                case MainMenu::EXPORT_TO_TXT_QAS: {
                }
                case MainMenu::EXPORT_TO_TXT_AS: {
                    string quizId = ShowRoom::selectQuiz();
                    if (quizId.empty()) break;
                    string answerSheetId = ShowRoom::selectAnswersheet(quizId);
                    if (answerSheetId.empty()) break;
                    ShowRoom exports(quizId, answerSheetId);
                    exports.Export(menuAction);
                    break;
                }
                case MainMenu::NONE: { // TODO ?
                    break;
                }
                case MainMenu::EXIT:
                    return;
            }
        } catch (const char * err){
            clear();
            refresh();
            mvprintw(2, screenWidth/2 - 7, "Error occured:");
            mvprintw(3, screenWidth/2 - string(err).size()/2, err);
            mvprintw(4, screenWidth/2 - 12, "Press any key to continue");
            refresh();
            getch();
        }
    }
}

string App::getInfo() {
    string output = "EXECUTION: ./kalabto2  [MODE|PARAMETERS]:\n\n"
                    "PARAMETERS:\n\t--help\n\tprints info about application"
                    "\n\t--import\n\tstarts importing sequence"
                    "\n\nMODES:\n\tSTUDENT\n\tlaunch application in limited student mode"
                    "\n\tTEACHER\n\tlaunch whole application\n";
    return output;
}

void App::setUsername(const string &username) {
    App::username = username;
}

void App::import(int argv, char **args) {
    for (int i = 2; i < argv; i++){
        ifstream inFile(args[i]);
        string line, importPath;

        if (inFile.is_open()) {
            getline(inFile, line);
            if (line == "quiz")
                importPath = "files/quizzes/";
            else if (line == "sheet")
                importPath = "files/sheets/";
            else if (line == "answerSheet")
                importPath = "files/answerSheets/";
            else if (line == "sheet")
                importPath = "files/sheets/";
            else if (line == "txtQ" || line == "chcQ" || line == "srtQ")
                importPath = "files/questions/";
            else if (line == "txtA" || line == "valA" || line == "schA" || line == "mchA" || line == "pchA")
                importPath = "files/answers/";
        }

        ofstream dst(importPath + args[i]);
        dst << inFile.rdbuf();
    }
}

