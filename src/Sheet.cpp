//
// Created by tom on 19.04.20.
//

#include "Sheet.h"
#include <ncurses.h>

Sheet::Sheet() {
    getmaxyx(stdscr,screenHeight,screenWidth);
}

void Sheet::addQuestion(shared_ptr<Question> question) {

}

void Sheet::addAnswer(shared_ptr<Answer> answer) {

}

void Sheet::createSheet() {
    wclear(stdscr);
    refresh();
    WINDOW * upperWin = newwin(5, screenWidth, 0, 0); // fce newwin vytvori okno
    box(upperWin, 0,0); // vytvori hranice okolo okna
    mvwprintw(upperWin, 2, screenWidth/2 - 6, "SHEET FACTORY");
    wrefresh(upperWin);

    choosePanel();

    getch();
}

void Sheet::choosePanel() {
    WINDOW * sideWin = newwin(screenHeight - 5, 60, 5, 0); // fce newwin vytvori okno
    box(sideWin, 0, 0); // vytvori hranice okolo okna

    mvwprintw(sideWin, 0, 60/2-5, "SIDE PANEL");
    mvwprintw(sideWin, 2, 4, "QUESTION");
    mvwprintw(sideWin, 4, 6, "* Text Question");

    mvwprintw(sideWin, (screenHeight - 5) / 2, 4, "ANSWER");
    mvwprintw(sideWin, (screenHeight - 5) / 2 + 2, 6 , "* Text Answer");

    mvwprintw(sideWin, (screenHeight - 5) - 5, 4, "SAVE & ADD QUESTION");
    mvwprintw(sideWin, (screenHeight - 5) - 3, 4, "SAVE & FINISH SHEET");
    wrefresh(sideWin);
}
