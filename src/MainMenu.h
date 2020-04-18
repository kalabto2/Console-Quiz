//
// Created by tom on 11.04.20.
//

#ifndef KALABTO2_MAINMENU_H
#define KALABTO2_MAINMENU_H

#include <ncurses.h>
#include <string>
#include <fstream>

#define PAUSE_MENU_WINDOW_HEIGHT 10
#define MAIN_MENU_WINDOW_HEIGHT 20
#define MAIN_MENU_WINDOW_WIDTH 40
#define MAIN_MENU_CONTINUE_HEIGHT 5
#define MAIN_MENU_LOAD_GAME_HEIGHT 20
#define MAIN_MENU_CHOOSE_LEVEL_HEIGHT 30
#define MAIN_MENU_HELP_HEIGHT 43
#define MAIN_MENU_SETTINGS_HEIGHT 30
#define MAIN_MENU_SOMETHING_HEIGHT 10
#define MAIN_MENU_EXIT_HEIGHT 5

using namespace std;

class MainMenu {
protected:
    int screenHeight,screenWidth;
    WINDOW * mainWin;
    WINDOW * extendedWin;
    enum EXTENDED_MENU_TYPE {
        INTERACTIVE, QUESTION
    };
public:
    MainMenu();
    int run();
    void extendedWindow (int type);
};

#endif //KALABTO2_MAINMENU_H
