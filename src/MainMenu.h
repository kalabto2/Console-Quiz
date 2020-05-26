//
// Created by tom on 11.04.20.
//

#ifndef KALABTO2_MAINMENU_H
#define KALABTO2_MAINMENU_H

#include <ncurses.h>
#include <string>
#include <fstream>

#define MAIN_MENU_WINDOW_HEIGHT 20
#define MAIN_MENU_WINDOW_WIDTH 40
#define MAIN_MENU_CONTINUE_HEIGHT 5
#define MAIN_MENU_LOAD_GAME_HEIGHT 5
#define MAIN_MENU_EVALUATE_QUIZ_HEIGHT 5
#define MAIN_MENU_IMPORT_EXPORT_HEIGHT 20
#define MAIN_MENU_SETTINGS_HEIGHT 30
#define MAIN_MENU_HELP_HEIGHT 43
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
    enum MENU_ACTION {
        EXIT, START_QUIZ, CREATE_QUIZ, EVALUATE_QUIZ, EXPORT_TO_TXT_QA, EXPORT_TO_TXT_Q,
        EXPORT_TO_TXT_AS, NONE, EXPORT_TO_TXT_QS, EXPORT_TO_TXT_QAS
    };

    MainMenu(bool studentMode = false);
    ~MainMenu();
    MENU_ACTION run(bool studentMode = false);
    void extendedWindow (int type);
    void refresh();


};

#endif //KALABTO2_MAINMENU_H
