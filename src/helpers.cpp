//
// Created by tom on 30.04.20.
//

#ifndef HELPERS
#define HELPERS

#include <string>
#include <ncurses.h>

using namespace std;

string getInput (WINDOW * window){
    string text;

    while (true){
        int a = getch();

        if(a == KEY_BACKSPACE || a == (int)'\b' || a == 127) {
            int x, y;
            getyx(window, y, x);
            mvwprintw(window, y, --x, " ");
            wmove(window, y, x);
            wrefresh(window);
            if (!text.empty())
                text.pop_back();
            continue;
        }

        if ( a == KEY_ENTER || a == KEY_RIGHT)
            break;

        const char * tmp = new const char (a);
        wprintw(window, tmp);
        wrefresh(window);
        delete tmp;

        text += (char)a;
    }
    return text;
}

void statusWindow (string textInside){
    int screenWidth, screenHeight;
    getmaxyx(stdscr, screenHeight,screenWidth);

    WINDOW * upperWin = newwin(5, screenWidth, 0, 0); // fce newwin vytvori okno
    box(upperWin, 0,0); // vytvori hranice okolo okna
    mvwprintw(upperWin, 2, screenWidth/2 - textInside.length() / 2, textInside.c_str());
    wrefresh(upperWin);
}

#endif //HELPERS