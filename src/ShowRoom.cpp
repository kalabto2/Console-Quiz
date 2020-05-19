//
// Created by tom on 19.05.20.
//

#include <ncurses.h>

#include "ShowRoom.h"

const int QUIZ_FACTORY_DIALOG_HEIGHT = 10;
const int QUIZ_FACTORY_DIALOG_WIDTH = 50;

ShowRoom::ShowRoom(Quiz quiz) : quiz(quiz) {
    getmaxyx(stdscr, screenHeight, screenWidth);
}

void ShowRoom::Export(MainMenu::MENU_ACTION action) {
    wclear(stdscr);
    refresh();
    WINDOW * upperWin = newwin(5, screenWidth, 0, 0); // fce newwin vytvori okno
    box(upperWin, 0,0); // vytvori hranice okolo okna
    mvwprintw(upperWin, 2, screenWidth/2 - 6, "QUIZ FACTORY");
    wrefresh(upperWin);

    WINDOW * dialog = newwin(QUIZ_FACTORY_DIALOG_HEIGHT, QUIZ_FACTORY_DIALOG_WIDTH, 10, screenWidth/2 - QUIZ_FACTORY_DIALOG_WIDTH/2); // fce newwin vytvori okno
    box(dialog, 0,0); // vytvori hranice okolo okna
    mvwprintw(dialog, 2, 2, "Enter the name of the quiz!");
    mvwprintw(dialog, 3, 2, "> ");
    curs_set(1);    // zviditelni kurzor
    wmove(dialog, 3, 4);    // presune kurzor do okna na x, y pozici
    wrefresh(dialog);

    char name2[100];
    echo();
    wgetstr(dialog, name2);
    noecho();
    curs_set(0);

    bool printQuestion = true, printAnswer = true, printAnswerSpace = false;
    if (action == MainMenu::EXPORT_TO_TXT_QA){

    } else if (action == MainMenu::EXPORT_TO_TXT_Q){
        printAnswer = false;
    } else if (action == MainMenu::EXPORT_TO_TXT_QS){
        printAnswer = false;
        printAnswerSpace = true;
    } else if (action == MainMenu::EXPORT_TO_TXT_QAS){  // TODO

    } else if (action == MainMenu::EXPORT_TO_TXT_AS){   // TODO

    }
    string output = quiz.print(printQuestion,printAnswer, printAnswerSpace);

    ofstream outFile(EXPORTS_FILE_PATH + string(name2));
    if (outFile.is_open())
    {
        outFile << output;
        outFile.close();
    }
}
