//
// Created by tom on 19.05.20.
//

#include <ncurses.h>
#include <numeric>
#include <algorithm>

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

    vector <vector <int> > sheetCursorHeight;
    vector <string> sheets;
    tie(sheets, sheetCursorHeight) = quiz.getPrintedSheets(true, true);
    //vector <vector<string> > printedQuestions = quiz.getPrintSheets(true,true,false);

    for (auto &i: sheetCursorHeight) {
        i[i.size() - 1] += 2;
        i.push_back(2);
    }

    for (size_t j = 0; j < sheets.size(); j++) {
        showWinScroll = 0;
        int winHeight = count(sheets[j].begin(), sheets[j].end(), '\n') + 8;
        //sheetCursorHeight[j][sheetCursorHeight[j].size() - 1] += 2;
        //sheetCursorHeight[j].push_back(2);
        WINDOW *showWin = newwin(winHeight, screenWidth, 6, 0);
        scrollok(showWin, true);

        string output = sheets[j];
        int numberOfOptions = sheetCursorHeight[j].size();

        /*int rows = 5;
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
        // wmove(showWin, screenHeight * 2, 5);

        if (j != 0)
            mvwprintw(showWin, winHeight - 7, 5, "PREVIOUS SHEET");
        if (j < sheets.size())
            mvwprintw(showWin, winHeight - 5, 5, "NEXT SHEET");
        else
            mvwprintw(showWin, winHeight - 5, 5, "FINISH QUIZ!");*/
        scrollWin(showWin, output, 0);
        /*getch();
        wscrl(showWin, 10);
        wrefresh(showWin);
        getch();
        wscrl(showWin, 10);
        wrefresh(showWin);
        getch();
        wscrl(showWin, -10);
        wrefresh(showWin);
        getch();*/
       /* wmove(showWin, 0, 5);
        for (auto & i: sheetCursorHeight[j])
            wprintw(showWin, (to_string(i) + " ").c_str());
        wmove(showWin, 1, 5);

        wprintw(showWin, to_string(numberOfOptions).c_str());

        //mvwprintw(showWin, 5, 2, "=>");
        wrefresh(showWin);*/

        bool previous = false;
        int c, selection = 0;
        while (true){
            c = getch();
            if (c == 'w' || c == KEY_UP){
                /*mvwprintw(showWin, sheetCursorHeight[j][(selection - 1 < 0 ? 0 : selection - 1)], 2, "  " );
                selection = (selection - 1 < 0 ? 0 : selection - 1);
                mvwprintw(showWin, sheetCursorHeight[j][(selection - 1 < 0 ? 0 : selection - 1)], 2, "=>");
                wrefresh(showWin);*/
                int lastSelection = selection;
                selection = (selection - 1 < 0 ? 0 : selection - 1);
                if (lastSelection == 0)
                    continue;
                scrollWin(showWin, output, -sheetCursorHeight[j][selection]);
            } else if (c == 's' || c == KEY_DOWN){
                /*mvwprintw(showWin, sheetCursorHeight[j][(selection - 1 < 0 ? 0 : selection - 1)], 2, "  " );
                selection = (selection + 1 > numberOfOptions - 1 ? numberOfOptions - 1 : selection + 1);
                mvwprintw(showWin, sheetCursorHeight[j][(selection - 1 < 0 ? 0 : selection - 1)], 2, "=>");
                wrefresh(showWin);*/
                int lastSelection = selection;
                selection = (selection + 1 > numberOfOptions ? numberOfOptions : selection + 1);
                if (selection <= 0 || lastSelection == numberOfOptions)
                    continue;
                scrollWin(showWin, output, sheetCursorHeight[j][selection - 1]);

            } else if (c == 'a' || c == KEY_LEFT){
                if (selection == numberOfOptions - 1){
                    if (j == 0)
                        continue;
                    previous = true;
                    break;
                }
            } else if (c == 'd' || c == KEY_RIGHT){
                if (selection == numberOfOptions)
                    break;
                if (selection == numberOfOptions - 1){
                    if (j == 0)
                        continue;
                    previous = true;
                    break;
                }
                quiz.renderInput(j,selection);
                scrollWin(showWin, output, 0);
            } else if (c == ' ')
                scrollWin(showWin, output, 1);
            /*mvwprintw(showWin, 1, 10, to_string(selection).c_str());
            wrefresh(showWin);*/
        }

        if (previous){
            j -= 2;
            continue;
        }
    }

    /* TODO tady udelat oznameni po kvizu  + vyhodnoceni/ veci pro evaluation */
}

void ShowRoom::scrollWin(WINDOW *window, string content, int scrolledLines) {
    mvwprintw(window, 5, 2, "  ");
    if (scrolledLines > 0)
        wscrl(window, scrolledLines);
    else if(scrolledLines <= 0 && showWinScroll + scrolledLines >= 0){
        wclear(window);
        box(window, 0, 0);
        int rows = 1;
        wmove(window, rows, 5);
        wprintw(window, "|");
        for (char i : content) {
            if (i == '\n') {
                wmove(window, ++rows, 5);
                wprintw(window, "|");
                continue;
            }
            string sym(1, i);
            wprintw(window, sym.c_str());
        }
        mvwprintw(window, rows + 3, 5, "PREVIOUS SHEET");
        mvwprintw(window, rows + 5, 5, "NEXT SHEET");
        wscrl(window, showWinScroll + scrolledLines);
    } else
        return;
    mvwprintw(window, 5, 2, "->");
    wrefresh(window);
    showWinScroll += scrolledLines;
}
