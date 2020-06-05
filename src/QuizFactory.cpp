//
// Created by tom on 18.04.20.
//

#include "QuizFactory.h"

#include <ncurses.h>
#include <string>

const int QUIZ_FACTORY_DIALOG_HEIGHT = 10;
const int QUIZ_FACTORY_DIALOG_WIDTH = 50;

QuizFactory::QuizFactory() {
    wclear(stdscr);
    refresh();
    getmaxyx(stdscr, screenHeight, screenWidth);
}

void QuizFactory::setName() {
    WINDOW * dialog = newwin(QUIZ_FACTORY_DIALOG_HEIGHT, QUIZ_FACTORY_DIALOG_WIDTH, 10, screenWidth/2 - QUIZ_FACTORY_DIALOG_WIDTH/2); // fce newwin vytvori okno
    box(dialog, 0,0);
    mvwprintw(dialog, 2, 2, "Enter the name of the quiz!");
    mvwprintw(dialog, 3, 2, "> ");
    curs_set(1);
    wmove(dialog, 3, 4);
    wrefresh(dialog);

    char name2[100];
    while (true) {
        curs_set(1);
        echo();
        wgetnstr(dialog, name2, 99);
        noecho();
        curs_set(0);
        if (!string(name2).empty())
            break;
        mvwprintw(dialog, 4, 2, "You entered empty name - at least 1 character.");
        wmove(dialog, 3, 4);
        wrefresh(dialog);
    }
    delwin(dialog);
    quiz.setName(string(name2));
}

void QuizFactory::createQuiz() {
    addSheetDialog();
    quiz.save();
}

void QuizFactory::addSheetDialog() {
    const int ADD_SHEET_DIALOG_HEIGHT = 10;
    const int ADD_SHEET_DIALOG_WIDTH = 100;

    int i = 0;
    while (true)  {
        clear();
        refresh();
        WINDOW * upperWin = newwin(5, screenWidth, 0, 0);
        box(upperWin, 0,0);
        mvwprintw(upperWin, 2, screenWidth/2 - 6, "QUIZ FACTORY");
        wrefresh(upperWin);
        delwin(upperWin);

        WINDOW * addSheetWin = newwin(ADD_SHEET_DIALOG_HEIGHT, ADD_SHEET_DIALOG_WIDTH, screenHeight / 2 - ADD_SHEET_DIALOG_HEIGHT / 2, screenWidth / 2 - ADD_SHEET_DIALOG_WIDTH / 2);
        box(addSheetWin, 0, 0);
        mvwprintw(addSheetWin, 2, 6, "NEW SHEET");
        mvwprintw(addSheetWin, 4, 6, "NEW SHEET WITH CONTROL QUESTION");
        if (i != 0)
            mvwprintw(addSheetWin, 6, 6, "END & SAVE QUIZ");
        mvwprintw(addSheetWin, 2, 3, "=>");
        wrefresh(addSheetWin);

        int pointerPos = 2;

        while (true) {
            int a = getch();

            if (a == '\n' || a == KEY_ENTER || a == KEY_RIGHT)
                break;

            if (a == KEY_DOWN || a == 's') {
                mvwprintw(addSheetWin, pointerPos, 3, "  ");
                pointerPos += (pointerPos < (i == 0 ? 4 : 6) ? 2 : 0);
            } else if (a == KEY_UP || a == 'w') {
                mvwprintw(addSheetWin, pointerPos, 3, "  ");
                pointerPos -= (pointerPos > 2 ? 2 : 0);
            }
            mvwprintw(addSheetWin, pointerPos, 3, "=>");
            wrefresh(addSheetWin);
        }
        delwin(addSheetWin);
        i ++;

        if (pointerPos == 2) {
            Sheet sheet;
            sheet.createSheet();
            quiz.addSheet(sheet);
            //quiz.addControlQuestion("");
            //quiz.addControlAnswer("");
        } else if (pointerPos == 4) {
            WINDOW * dialog = newwin(ADD_SHEET_DIALOG_HEIGHT, ADD_SHEET_DIALOG_WIDTH, screenHeight / 2 - ADD_SHEET_DIALOG_HEIGHT / 2, screenWidth / 2 - ADD_SHEET_DIALOG_WIDTH / 2);
            box(dialog, 0,0);
            mvwprintw(dialog, 2, 2, "Enter Question confirming entry to extra Sheet. (e.g. 'Enter voluntary part? (y/n)'");
            mvwprintw(dialog, 3, 2, "> ");
            curs_set(1);
            wmove(dialog, 3, 4);
            wrefresh(dialog);

            char name[100];
            while (true) {
                curs_set(1);
                echo();
                wgetnstr(dialog, name, 99);
                noecho();
                curs_set(0);
                if (!string(name).empty())
                    break;
                mvwprintw(dialog, 4, 2, "You entered no question - at least 1 character.");
                wmove(dialog, 3, 4);
                wrefresh(dialog);
            }
            delwin(dialog);
            //quiz.setExtraQuestion(string(name));
            //quiz.addControlQuestion(string(name));

            WINDOW * dialog2 = newwin(ADD_SHEET_DIALOG_HEIGHT, ADD_SHEET_DIALOG_WIDTH, screenHeight / 2 - ADD_SHEET_DIALOG_HEIGHT / 2, screenWidth / 2 - ADD_SHEET_DIALOG_WIDTH / 2);
            box(dialog2, 0,0);
            mvwprintw(dialog2, 2, 2, "Enter correct Answer to Question confirming entry to extra Sheet. (e.g. 'y')");
            mvwprintw(dialog2, 3, 2, "> ");
            curs_set(1);
            wmove(dialog2, 3, 4);
            wrefresh(dialog2);

            char name2[100];
            while (true) {
                curs_set(1);
                echo();
                wgetnstr(dialog2, name2, 99);
                noecho();
                curs_set(0);
                if (!string(name2).empty())
                    break;
                mvwprintw(dialog2, 4, 2, "You entered no answer - at least 1 character.");
                wmove(dialog2, 3, 4);
                wrefresh(dialog2);
            }
            delwin(dialog2);
            //quiz.setExtraAnswer(string(name2));
            //string blaf = string(name2);
            //quiz.addControlAnswer(blaf);

            Sheet sheet;
            sheet.setControlQuestion(string(name));
            sheet.setControlAnswer(string(name2));
            sheet.createSheet();    // here is sheet saved to file
            //quiz.addExtraSheet(sheet);
            quiz.addSheet(sheet);
        } else if (pointerPos == 6)
            break;
    }
}