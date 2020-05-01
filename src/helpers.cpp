//
// Created by tom on 30.04.20.
//

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