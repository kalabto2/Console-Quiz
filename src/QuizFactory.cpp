//
// Created by tom on 18.04.20.
//

#include "QuizFactory.h"

#include <ncurses.h>
#include <string>
#include <iostream>
#include <filesystem>

const int QUIZ_FACTORY_DIALOG_HEIGHT = 10;
const int QUIZ_FACTORY_DIALOG_WIDTH = 50;

QuizFactory::QuizFactory() {
    wclear(stdscr);
    refresh(); // refresh screen
    getmaxyx(stdscr, screenHeight, screenWidth);   // ziska rozmery obrazovky
}

void QuizFactory::setName() {
    WINDOW * dialog = newwin(QUIZ_FACTORY_DIALOG_HEIGHT, QUIZ_FACTORY_DIALOG_WIDTH, 10, screenWidth/2 - QUIZ_FACTORY_DIALOG_WIDTH/2); // fce newwin vytvori okno
    box(dialog, 0,0); // vytvori hranice okolo okna
    mvwprintw(dialog, 2, 2, "Enter the name of the quiz!");
    mvwprintw(dialog, 3, 2, "> ");
    curs_set(1);    // zviditelni kurzor
    wmove(dialog, 3, 4);    // presune kurzor do okna na x, y pozici
    wrefresh(dialog);

    /*while (true){
        int a = wgetch(dialog);

        if(a == KEY_BACKSPACE || a == (int)'\b' || a == 127) {
            int x, y;
            getyx(dialog, y, x);
            mvwprintw(dialog, y, --x, " ");
            wmove(dialog, y, x);
            wrefresh(dialog);
            if (name != "")
                name.pop_back();
            continue;
        }

        if ( a == KEY_ENTER || a == '\n')
            break;

        const char * tmp = new const char (a);
        wprintw(dialog, tmp);
        wrefresh(dialog);
        delete tmp;

        name += (char)a;
    }*/

    char name2[100];
    echo();
    wgetstr(dialog, name2);
    noecho();
    curs_set(0);
    quiz.setName(string(name2));

    /*mvwprintw(dialog, 4, 2, name.c_str());
    wrefresh(dialog);
    getch();*/
}

void QuizFactory::createQuiz() {
    wclear(stdscr);
    refresh();
    WINDOW * upperWin = newwin(5, screenWidth, 0, 0); // fce newwin vytvori okno
    box(upperWin, 0,0); // vytvori hranice okolo okna
    mvwprintw(upperWin, 2, screenWidth/2 - 6, "QUIZ FACTORY");
    wrefresh(upperWin);

    addSheetDialog();
    quiz.save();
    // getch();
}

void QuizFactory::addSheetDialog() {
    const int ADD_SHEET_DIALOG_HEIGHT = 10;
    const int ADD_SHEET_DIALOG_WIDTH = 60;

    while (true)  {
        clear();
        refresh();
        WINDOW * addSheetWin = newwin(ADD_SHEET_DIALOG_HEIGHT, ADD_SHEET_DIALOG_WIDTH, screenHeight / 2 - ADD_SHEET_DIALOG_HEIGHT / 2, screenWidth / 2 - ADD_SHEET_DIALOG_WIDTH / 2); // fce newwin vytvori okno
        box(addSheetWin, 0, 0); // vytvori hranice okolo okna
        mvwprintw(addSheetWin, 2, 6, "NEW SHEET");
        mvwprintw(addSheetWin, 4, 6, "END & SAVE QUIZ");
        mvwprintw(addSheetWin, 2, 3, "=>");
        wrefresh(addSheetWin);

        int pointerPos = 2;

        while (true) {
            int a = getch();

            if (a == '\n' || a == KEY_ENTER || a == KEY_RIGHT)
                break;

            if (a == KEY_DOWN || a == 's') {
                mvwprintw(addSheetWin, pointerPos, 3, "  ");
                pointerPos += (pointerPos < 4 ? 2 : 0);
            } else if (a == KEY_UP || a == 'w') {
                mvwprintw(addSheetWin, pointerPos, 3, "  ");
                pointerPos -= (pointerPos > 2 ? 2 : 0);
            }
            mvwprintw(addSheetWin, pointerPos, 3, "=>");
            wrefresh(addSheetWin);

        }

        if (pointerPos == 2) {
            Sheet sheet;
            sheet.createSheet();
            quiz.addSheet(sheet);
        } else if (pointerPos == 4) {
            break;
        }

    }
}
/*
string QuizFactory::selectAnswersheet() {
    return selectQuiz(false);
}

string QuizFactory::selectQuiz(bool findQuiz) {
    wclear(stdscr);
    refresh();
    WINDOW * upperWin = newwin(5, screenWidth, 0, 0); // fce newwin vytvori okno
    box(upperWin, 0,0); // vytvori hranice okolo okna
    mvwprintw(upperWin, 2, screenWidth/2 - 6, (findQuiz ? "QUIZ SELECTOR" : "ANSWERSHEET SELECOTR"));
    wrefresh(upperWin);

    vector<string> quizFileNames;
    vector< vector<string> > quizFileData;
    namespace fs = std::filesystem;

    std::string path = (findQuiz ? "./files/quizzes/" : "./files/answerSheets/");
    for (const auto & entry : fs::directory_iterator(path)) {
        quizFileData.push_back(Quiz::preview(entry.path()));
        quizFileNames.push_back(entry.path());
    }

    WINDOW * showWin = newwin(screenHeight - 5, screenWidth, 6, 0); // fce newwin vytvori okno
    box(showWin, 0,0); // vytvori hranice okolo okna

    for (size_t i = 0; i < quizFileNames.size(); i++){
        mvwprintw(showWin, 2 + i * 2, 10, quizFileNames[i].substr(quizFileNames[i].size() - 17).c_str());
        mvwprintw(showWin, 2 + i * 2, 50, quizFileData[i][1].c_str());
    }
    wrefresh(showWin);


    int pointerPos = 2;
    mvwprintw(showWin, 2, 3, "=>");
    wrefresh(showWin);

    while (true) {
        int a = getch();

        if (a == '\n' || a == KEY_ENTER || a == KEY_RIGHT)
            break;

        if (a == KEY_DOWN || a == 's') {
            mvwprintw(showWin, pointerPos, 3, "  ");
            pointerPos += (pointerPos < 2 * quizFileNames.size() ? 2 : 0);
        } else if (a == KEY_UP || a == 'w') {
            mvwprintw(showWin, pointerPos, 3, "  ");
            pointerPos -= (pointerPos > 2 ? 2 : 0);
        }
        mvwprintw(showWin, pointerPos, 3, "=>");
        wrefresh(showWin);
    }

    return quizFileNames[pointerPos / 2 -1];
}
*/