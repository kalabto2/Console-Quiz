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
    mvwprintw(upperWin, 2, screenWidth/2 - 6, "QUIZ EXPORTER");
    wrefresh(upperWin);

    WINDOW * dialog = newwin(QUIZ_FACTORY_DIALOG_HEIGHT, QUIZ_FACTORY_DIALOG_WIDTH, 10, screenWidth/2 - QUIZ_FACTORY_DIALOG_WIDTH/2); // fce newwin vytvori okno
    box(dialog, 0,0); // vytvori hranice okolo okna
    mvwprintw(dialog, 2, 2, "Enter name of the exported file!");
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

void ShowRoom::StartQuiz() {
    wclear(stdscr);
    refresh();
    WINDOW * upperWin = newwin(5, screenWidth, 0, 0);
    box(upperWin, 0,0);
    mvwprintw(upperWin, 2, screenWidth/2 - 6, "START FILLING!");
    mvwprintw(upperWin, 2, 7, ("Quiz - " + quiz.getName()).c_str());
    mvwprintw(upperWin, 2, screenWidth - 7 - 20, ("id: " + quiz.getId()).c_str());
    wrefresh(upperWin);

    for (int j = 0; j < 5; j++) {   // TODO for each sheet
        int winHeight = screenHeight * 5;
        WINDOW *showWin = newwin(winHeight, screenWidth, 6, 0);
        scrollok(showWin, true);

        string output = quiz.print();

        int rows = 5;
        wmove(showWin, rows, 5);
        for (int i = 0; i < output.size(); i++) {
            if (output[i] == '\n') {
                wmove(showWin, ++rows, 5);
                wrefresh(showWin);
                continue;
            }
            string sym(1, output[i]);
            wprintw(showWin, sym.c_str());
        }
        wmove(showWin, screenHeight * 2, 5);

        if (j != 0)
            mvwprintw(showWin, screenHeight - 7, 5, "PREVIOUS SHEET");
        if (j < 5)
            mvwprintw(showWin, screenHeight - 5, 5, "NEXT SHEET");
        else
            mvwprintw(showWin, screenHeight - 5, 5, "FINISH QUIZ!");

        getch();
        wscrl(showWin, 10);
        wrefresh(showWin);
        getch();
        wscrl(showWin, 10);
        wrefresh(showWin);
        getch();
        wscrl(showWin, -10);
        wrefresh(showWin);
        getch();

        int c;
        while (true){
            c = getch();
            if (c == 'w' || c == KEY_UP){

            } else if (c == 's' || c == KEY_DOWN){

            } else if (c == 'a' || c == KEY_LEFT){

            } else if (c == 'd' || c == KEY_RIGHT){
                break;
            }
        }

    }

    /* TODO tady udelat oznameni po kvizu  + vyhodnoceni/ veci pro evaluation*/
}
