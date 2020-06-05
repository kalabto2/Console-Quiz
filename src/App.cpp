//
// Created by tom on 11.04.20.
//
#include <ncurses.h>

#include "App.h"
#include "MainMenu.h"
#include "QuizFactory.h"
#include "ShowRoom.h"

const string App::PASSWORD_FILE = "files/password";

App::App() {
    initscr(); // initialize screen, sets memory
    cbreak(); // ends app on CTRL+C
    noecho(); // no echo on input
    keypad(stdscr, true); // turns on arrow keys
    curs_set(0); // Hides cursor. Parameter - 0/1/2 resp. hide/normal/very visible

    getmaxyx(stdscr, screenHeight, screenWidth);   // gets dimensions of screen
    start_color(); // sets colours
}

App::~App() {
    endwin();
}

void App::run(bool studentMode) {
    while (true) {
        MainMenu mainMenu (studentMode);
        MainMenu::MENU_ACTION menuAction;
        menuAction = mainMenu.run(studentMode);

        try {
            /// Makes certain action
            switch (menuAction) {
                case MainMenu::START_QUIZ: {        // FIXME ?
                    string quizId = ShowRoom::selectQuiz();  // May throw exceptions
                    if (quizId.empty()) break;
                    ShowRoom showRoom(quizId);   // May throw exceptions
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
                case MainMenu::EVALUATE_QUIZ: {     // FIXME ?
                    string quizId = ShowRoom::selectQuiz(); // May throw exceptions
                    if (quizId.empty()) break;
                    string answerSheetId = ShowRoom::selectAnswersheet(quizId); // May throw exceptions
                    if (answerSheetId.empty()) break;
                    ShowRoom showRoom(quizId, answerSheetId);   // May throw exceptions
                    showRoom.StartQuiz(false);
                    break;
                }
                case MainMenu::EXPORT_TO_TXT_QA: {
                }
                case MainMenu::EXPORT_TO_TXT_Q: {
                }
                case MainMenu::EXPORT_TO_TXT_QS: {  // May throw exceptions
                    string quizId = ShowRoom::selectQuiz();     // May throw exceptions
                    if (quizId.empty()) break;
                    ShowRoom exports(quizId);   // May throw exceptions
                    exports.Export(menuAction); // May throw exception
                    break;
                }
                case MainMenu::EXPORT_TO_TXT_QAS: {
                }
                case MainMenu::EXPORT_TO_TXT_AS: {  // May throw exceptions
                    string quizId = ShowRoom::selectQuiz();     // May throw exceptions
                    if (quizId.empty()) break;
                    string answerSheetId = ShowRoom::selectAnswersheet(quizId); // May throw exceptions
                    if (answerSheetId.empty()) break;
                    ShowRoom exports(quizId, answerSheetId);        // May throw exceptions
                    exports.Export(menuAction);     // May throw exception
                    break;
                }
                case MainMenu::NONE: {
                    break;
                }
                case MainMenu::EXIT:
                    return;
                case MainMenu::CHANGE_PSWD:{        /// May throw exception
                    setPassword();
                    break;
                }
            }
        } catch (const char * err){
            clear();
            refresh();
            mvprintw(2, screenWidth/2 - 7, "Error occured:");
            mvprintw(3, screenWidth/2 - string(err).size()/2, err);
            mvprintw(4, screenWidth/2 - 12, "Press any key to continue");
            refresh();
            getch();
        } catch (exception &err) {
            clear();
            refresh();
            mvprintw(2, screenWidth/2 - 7, "Error occured:");
            mvprintw(3, screenWidth/2 - 7, err.what());
            mvprintw(4, screenWidth/2 - 12, "Press any key to continue");
            refresh();
            getch();
        }
    }
}

void App::setPassword() {
    const int DIALOG_HEIGHT = 7, DIALOG_WIDTH = 80;
    clear();
    refresh();
    WINDOW * dialog = newwin(DIALOG_HEIGHT, DIALOG_WIDTH, 10, screenWidth/2 - DIALOG_WIDTH/2);
    box(dialog, 0,0);
    mvwprintw(dialog, 2, 2, "Enter new password!");
    mvwprintw(dialog, 3, 2, "> ");
    curs_set(1);
    wmove(dialog, 3, 4);
    wrefresh(dialog);

    char name2[100];
    echo();
    wgetnstr(dialog, name2, 99);
    noecho();
    curs_set(0);

    delwin(dialog);

    ofstream outFile(App::PASSWORD_FILE);
    if (outFile.is_open()) {
        outFile << name2;
        outFile.close();
    } else
        throw "Password couldn't be set. File couldn't be opened.";
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

string App::getPassword() {
    string pswd = "password";
    ifstream inFile(App::PASSWORD_FILE);

    if (inFile.is_open()) {
        getline(inFile, pswd);
    }
    return pswd;
}
