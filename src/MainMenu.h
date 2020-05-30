//
// Created by tom on 11.04.20.
//

#ifndef KALABTO2_MAINMENU_H
#define KALABTO2_MAINMENU_H

#include <ncurses.h>
#include <string>
#include <fstream>

const int MAIN_MENU_WINDOW_HEIGHT = 20;
const int MAIN_MENU_WINDOW_WIDTH = 40;
const int MAIN_MENU_CONTINUE_HEIGHT = 5;
const int MAIN_MENU_LOAD_GAME_HEIGHT = 5;
const int MAIN_MENU_EVALUATE_QUIZ_HEIGHT = 5;
const int MAIN_MENU_IMPORT_EXPORT_HEIGHT = 20;
const int MAIN_MENU_SETTINGS_HEIGHT = 30;
const int MAIN_MENU_HELP_HEIGHT = 43;
const int MAIN_MENU_EXIT_HEIGHT = 5;

using namespace std;

/** Class represents main menu in App. Renders it to screen and decides, which action will be done */
class MainMenu {
protected:
    /** variables holds size of screen */
    int screenHeight,screenWidth;
    /** represents main window and detailed window, which is changing according to main menu selection */
    WINDOW * mainWin, * extendedWin;
    /** describes type of file to be loaded */
    enum EXTENDED_MENU_TYPE { INTERACTIVE, QUESTION };

public:
    /** describes action from main menu */
    enum MENU_ACTION {
        EXIT, START_QUIZ, CREATE_QUIZ, EVALUATE_QUIZ, EXPORT_TO_TXT_QA, EXPORT_TO_TXT_Q,
        EXPORT_TO_TXT_AS, NONE, EXPORT_TO_TXT_QS, EXPORT_TO_TXT_QAS, CHANGE_PSWD
    };

    /** Renders init screen including QUIZ banner and main menu options
     * @param[in] studentMode if true, runs in 'STUDENT' mode and renders only needed options in menu */
    MainMenu(bool studentMode = false);

    /** deletes both windows */
    ~MainMenu();

    /** Handles user input and returns, which action will be done, controls extended window.
     * @param[in] studentMode if true, runs in 'STUDENT' mode - limited actions. Else runs limitless
     * @return type of action to be started */
    MENU_ACTION run(bool studentMode = false);

    /** Renders extended window according to main menu selection
     * @param[in] type number of selection - starting from 0 as 'highest' option in menu */
    void extendedWindow (int type);

    /** Refreshes both windows*/
    void refresh();
};

#endif //KALABTO2_MAINMENU_H
