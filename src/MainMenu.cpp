//
// Created by tom on 11.04.20.
//

#include "MainMenu.h"


void MainMenu::extendedWindow(int type) {
    int winHeight;
    EXTENDED_MENU_TYPE windowType;
    string file;
    wclear(extendedWin);
    wrefresh(extendedWin);

    switch(type){
        case 0:{
            winHeight = MAIN_MENU_START_HEIGHT;
            file = "files/start";
            windowType = QUESTION;
            break;
        } case 1:{
            winHeight = MAIN_MENU_CREATE_QUIZ_HEIGHT;
            file = "files/create";
            windowType = QUESTION;
            break;
        } case 2:{
            winHeight = MAIN_MENU_EVALUATE_QUIZ_HEIGHT;
            file = "files/evaluate";
            windowType = QUESTION;
            break;
        } case 3:{
            winHeight = MAIN_MENU_IMPORT_EXPORT_HEIGHT;
            file = "files/import_export";
            windowType = INTERACTIVE;
            break;
        } case 4:{
            winHeight = MAIN_MENU_SETTINGS_HEIGHT;
            file = "files/settings_menu";
            windowType = INTERACTIVE;
            break;
        } case 5:{
            winHeight = MAIN_MENU_HELP_HEIGHT;
            file = "files/help";
            windowType = QUESTION;
            break;
        } case 6:{
            winHeight = MAIN_MENU_EXIT_HEIGHT;
            file = "files/exit";
            windowType = QUESTION;
            break;
        } default:{
            winHeight = 30;
            windowType = QUESTION;
        }
    }

    wresize(extendedWin, winHeight ,screenWidth - 10 - 3 * MAIN_MENU_WINDOW_WIDTH / 2);
    if ((screenHeight/2 + MAIN_MENU_WINDOW_HEIGHT/2 + winHeight/2) >= screenHeight)
        mvwin(extendedWin, screenHeight - 5 - winHeight, MAIN_MENU_WINDOW_WIDTH * 3 / 2 + 5);
    else
        mvwin(extendedWin, screenHeight/2 + MAIN_MENU_WINDOW_HEIGHT/2 - winHeight/2, MAIN_MENU_WINDOW_WIDTH * 3 / 2 + 5);
    box(extendedWin, 0, 0);
    wrefresh(extendedWin);

    string line;
    ifstream extendedWindowFile (file);

    if (extendedWindowFile.is_open())
    {
        int i = 0;

        switch (windowType){
            case QUESTION:{
                while ( getline (extendedWindowFile, line) ) {
                    mvwprintw(extendedWin, 2 + i, 5, "%s", line.c_str());
                    i++;
                }
                break;
            }
            case INTERACTIVE:{
                while ( getline (extendedWindowFile, line) ) {
                    if(i > 1)
                        mvwprintw(extendedWin, 1 + (i - 2 )/2, 5 + ((i - 2 ) % 2)*(screenWidth - 10 - 2 * MAIN_MENU_WINDOW_WIDTH / 2)/2, "%s", line.c_str());
                    i++;
                }
                break;
            }
        }
        refresh();
        extendedWindowFile.close();
    }
}

MainMenu::MainMenu(bool studentMode) {
    getmaxyx(stdscr, screenHeight, screenWidth);
    wclear(stdscr);

    string line;
    ifstream bannerFile ("files/banner");
    if (bannerFile.is_open())
    {
        int i = 0;
        while ( getline (bannerFile,line) )
        {
            mvprintw(2 + i, 5, "%s\n", line.c_str());
            i++;
        }
        wrefresh(stdscr);
        bannerFile.close();
    }

    extendedWin = newwin(MAIN_MENU_START_HEIGHT, screenWidth - 10 - 3 * MAIN_MENU_WINDOW_WIDTH / 2, screenHeight / 2 + MAIN_MENU_WINDOW_HEIGHT / 2 - MAIN_MENU_START_HEIGHT / 2, MAIN_MENU_WINDOW_WIDTH * 3 / 2 + 5 );
    mainWin = newwin(MAIN_MENU_WINDOW_HEIGHT, MAIN_MENU_WINDOW_WIDTH, screenHeight/2, MAIN_MENU_WINDOW_WIDTH/2); // fce newwin vytvori okno
    refresh();
    box(mainWin, 0,0);
    if (!studentMode) {
        mvwprintw(mainWin, 2, 4, "START QUIZ");
        mvwprintw(mainWin, 4, 4, "CREATE QUIZ");
        mvwprintw(mainWin, 6, 4, "EVALUATE QUIZ");
        mvwprintw(mainWin, 8, 4, "EXPORT / IMPORT");
        mvwprintw(mainWin, 10, 4, "SETTINGS");
        mvwprintw(mainWin, 12, 4, "HELP");
        mvwprintw(mainWin, 14, 4, "EXIT");
    }
    else{
        mvwprintw(mainWin, 2, 4, "START QUIZ");
        mvwprintw(mainWin, 4, 4, "HELP");
        mvwprintw(mainWin, 6, 4, "EXIT");
    }
    wrefresh(mainWin);
}

void MainMenu::refresh() {
    wrefresh(mainWin);
    wrefresh(extendedWin);
}

MainMenu::MENU_ACTION MainMenu::run(bool studentMode) {
    int curSelection = 0, movement;
    int numOfSelection = (studentMode ? 3 : 7);
    while(true) {
        if (studentMode){
            mvwprintw(mainWin, (curSelection == 0 ? 2 : 2 + (curSelection - 4) * 2), 2, "->");
        }
        else
            mvwprintw(mainWin, 2 + 2*curSelection, 2, "->");
        wrefresh(mainWin);

        extendedWindow(curSelection);
        wrefresh(extendedWin);

        movement = getch();

        if (studentMode){
            mvwprintw(mainWin, (curSelection == 0 ? 2 : 2 + (curSelection - 4) * 2), 2, "  ");
        }
        else
            mvwprintw(mainWin, 2 + 2*curSelection, 2, "  ");

        if (movement == 'w' || movement == KEY_UP){
            if (studentMode){
                if (curSelection == 6)
                    curSelection = 5;
                else if (curSelection == 5)
                    curSelection = 0;
            } else
                curSelection = curSelection > 0 ? curSelection - 1 : curSelection;
        }
        else if (movement == 's' || movement == KEY_DOWN){
            if (studentMode){
                if (curSelection == 0)
                    curSelection = 5;
                else if (curSelection == 5)
                    curSelection = 6;
            }
            else
                curSelection = curSelection < numOfSelection - 1 ? curSelection + 1 : curSelection;
        }
        else if (movement == 27 ) // 27 == KEY ESC
            return EXIT;
        else if (movement == KEY_ENTER || movement == KEY_RIGHT){
            mvwprintw(mainWin, 2 + 2*curSelection, 2, "  ");
            wrefresh(mainWin);

            switch(curSelection){
                case 0: {
                    mvwprintw(extendedWin, 2, 2, "=>");
                    wrefresh(extendedWin);
                    int c = getch();
                    if (c == 'y' || c == KEY_RIGHT)
                        return START_QUIZ;
                    break;
                }
                case 1: {
                    mvwprintw(extendedWin, 2, 2, "=>");
                    wrefresh(extendedWin);
                    int c = getch();
                    if (c == 'y' || c == KEY_RIGHT)
                        return CREATE_QUIZ;
                    break;
                }
                case 2:{
                    mvwprintw(extendedWin, 2, 2, "=>");
                    wrefresh(extendedWin);
                    int c = getch();
                    if (c == 'y' || c == KEY_RIGHT)
                        return EVALUATE_QUIZ;
                    break;
                }
                case 3:{
                    int c, selection = 0;

                    while (true) {
                        mvwprintw(extendedWin, 3 + selection, 2, "=>");
                        wrefresh(extendedWin);

                        c = getch();

                        mvwprintw(extendedWin, 3 + selection, 2, "  ");
                        wrefresh(extendedWin);
                        if (c == 'w' || c == KEY_UP)
                            selection = selection > 0 ? selection - 1 : selection;
                        else if (c == 's' || c == KEY_DOWN)
                            selection = selection < 4 ? selection + 1 : selection;
                        else if (c == 'y' || c == KEY_RIGHT) {
                            return  (selection == 0 ? EXPORT_TO_TXT_QA  :
                                    (selection == 1 ? EXPORT_TO_TXT_Q   :
                                    (selection == 2 ? EXPORT_TO_TXT_QS  :
                                    (selection == 3 ? EXPORT_TO_TXT_AS : EXPORT_TO_TXT_QAS ))));
                        }
                        else if (c == 'n' || c == KEY_LEFT)
                            break;
                    }
                    break;
                }
                case 4:{
                    mvwprintw(extendedWin, 3, 2, "=>");
                    wrefresh(extendedWin);
                    int c = getch();
                    if (c == 'y' || c == KEY_RIGHT)
                        return CHANGE_PSWD;
                    break;
                }
                case 5:
                    return NONE;
                case 6:{
                    mvwprintw(extendedWin, 2, 2, "=>");
                    wrefresh(extendedWin);
                    int c = getch();
                    if (c == 'y' || c == KEY_RIGHT)
                        return EXIT;
                    break;
                }
                default:
                    break;
            }
        }
    }
}

MainMenu::~MainMenu() {
    delwin(extendedWin);
    delwin(mainWin);
}
