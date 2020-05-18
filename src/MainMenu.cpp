//
// Created by tom on 11.04.20.
//

#include "MainMenu.h"


void MainMenu::extendedWindow(int type) {
    int winHeight, fileType;
    EXTENDED_MENU_TYPE windowType;
    string file;
    wclear(extendedWin);
    wrefresh(extendedWin);

    switch(type){
        case 0:{
            winHeight = MAIN_MENU_CONTINUE_HEIGHT;
            file = "files/continue";
            fileType = 1;
            windowType = QUESTION;
            break;
        }
        case 1:{
            winHeight = MAIN_MENU_LOAD_GAME_HEIGHT;
            file = "files/load_game";
            fileType = 2;
            windowType = QUESTION;
            break;
        }
        case 2:{
            winHeight = MAIN_MENU_EVALUATE_QUIZ_HEIGHT;
            file = "files/evaluate";
            fileType = 2;
            windowType = QUESTION;
            break;
        }
        case 3:{
            winHeight = MAIN_MENU_IMPORT_EXPORT_HEIGHT;
            file = "files/import_export";
            fileType = 1;
            windowType = INTERACTIVE;
            break;
        }
        case 4:{
            winHeight = MAIN_MENU_SETTINGS_HEIGHT;
            file = "files/settings_menu";
            fileType = 1;
            windowType = INTERACTIVE;
            break;
        }
        case 5:{
            winHeight = MAIN_MENU_HELP_HEIGHT;
            file = "files/help";
            fileType = 1;
            windowType = QUESTION;
            break;
        }
        case 6:{
            winHeight = MAIN_MENU_EXIT_HEIGHT;
            file = "files/exit";
            fileType = 1;
            windowType = QUESTION;
            break;
        }
        default :
            winHeight = 30;
            fileType = 3;
    }

    /*mvprintw(0,0,"   ");
    mvprintw(0,0,"%d",winHeight);
    mvprintw(1,0,"   ");
    mvprintw(1,0,"%d",screenHeight - 5 - winHeight);*/

    wresize(extendedWin, winHeight ,screenWidth - 10 - 3 * MAIN_MENU_WINDOW_WIDTH / 2);
    if ((screenHeight/2 + MAIN_MENU_WINDOW_HEIGHT/2 + winHeight/2) >= screenHeight)
        mvwin(extendedWin, screenHeight - 5 - winHeight, MAIN_MENU_WINDOW_WIDTH * 3 / 2 + 5);
    else
        mvwin(extendedWin, screenHeight/2 + MAIN_MENU_WINDOW_HEIGHT/2 - winHeight/2, MAIN_MENU_WINDOW_WIDTH * 3 / 2 + 5);
    box(extendedWin, 0, 0);
    wrefresh(extendedWin);

    string line;
    ifstream mapFile (file);

    /*if (mapFile.is_open())
    {
        int i = 0;

        switch (fileType){
            case 0:{
                while ( getline (mapFile,line) )
                {
                    if(i > 1)
                        mvwprintw(extendedWin, 1 + (i - 2 )/3, 5 + ((i - 2 ) % 3)*(screenWidth - 10 - 3 * MAIN_MENU_WINDOW_WIDTH / 2)/3, "%s", line.c_str());  // fce c_str() prevede string na char*
                    i++;
                }
                break;
            }
            case 1:{
                while ( getline (mapFile,line) )
                {
                    mvwprintw(extendedWin, 2 + i, 5, "%s", line.c_str());  // fce c_str() prevede string na char*
                    i++;
                }
                break;
            }
            case 2:{
                while ( getline (mapFile,line) )
                {
                    if(i > 1)
                        mvwprintw(extendedWin, 1 + (i - 2 )/4, 5 + ((i - 2 ) % 4)*(screenWidth - 10 - 4 * MAIN_MENU_WINDOW_WIDTH / 2)/4, "%s", line.c_str());  // fce c_str() prevede string na char*
                    i++;
                }
                break;
            }
            default:
                break;
        }
        refresh();
        mapFile.close();
    }*/

    if (mapFile.is_open())
    {
        int i = 0;

        switch (windowType){
            case QUESTION:{
                while ( getline (mapFile,line) )
                {
                    mvwprintw(extendedWin, 2 + i, 5, "%s", line.c_str());  // fce c_str() prevede string na char*
                    i++;
                }
                break;
            }
            case INTERACTIVE:{
                while ( getline (mapFile,line) )
                {
                    if(i > 1)
                        mvwprintw(extendedWin, 1 + (i - 2 )/2, 5 + ((i - 2 ) % 2)*(screenWidth - 10 - 2 * MAIN_MENU_WINDOW_WIDTH / 2)/2, "%s", line.c_str());
                    i++;
                }
                break;
            }
            default:
                break;
        }
        refresh();
        mapFile.close();
    }

}

MainMenu::MainMenu() {
    getmaxyx(stdscr, screenHeight, screenWidth);   // ziska rozmery obrazovky
    wclear(stdscr);

    string line;
    ifstream bannerFile ("files/banner");
    if (bannerFile.is_open())
    {
        int i = 0;
        while ( getline (bannerFile,line) )
        {
            mvprintw(2 + i, 5, "%s\n", line.c_str());  // fce c_str() prevede string na char*
            i++;
        }
        wrefresh(stdscr);
        bannerFile.close();
    }

    extendedWin = newwin(MAIN_MENU_CONTINUE_HEIGHT, screenWidth - 10 - 3 * MAIN_MENU_WINDOW_WIDTH / 2, screenHeight/2 + MAIN_MENU_WINDOW_HEIGHT/2 - MAIN_MENU_CONTINUE_HEIGHT/2, MAIN_MENU_WINDOW_WIDTH * 3 / 2 + 5 );
    mainWin = newwin(MAIN_MENU_WINDOW_HEIGHT, MAIN_MENU_WINDOW_WIDTH, screenHeight/2, MAIN_MENU_WINDOW_WIDTH/2); // fce newwin vytvori okno
    refresh(); // refreshne screen
    box(mainWin, 0,0); // vytvori hranice okolo okna statWin
    //mvwprintw(mainWin, 0, 10, "MAIN MENU"); // vypise do okna
    mvwprintw(mainWin, 2, 4, "START QUIZ"); // vypise do okna
    mvwprintw(mainWin, 4, 4, "CREATE QUIZ"); // vypise do okna
    mvwprintw(mainWin, 6, 4, "EVALUATE QUIZ"); // vypise do okna
    mvwprintw(mainWin, 8, 4, "EXPORT / IMPORT"); // vypise do okna
    mvwprintw(mainWin, 10, 4, "SETTINGS"); // vypise do okna
    mvwprintw(mainWin, 12, 4, "HELP"); // vypise do okna
    mvwprintw(mainWin, 14, 4, "EXIT"); // vypise do okna
    wrefresh(mainWin); // refreshne okno
}

void MainMenu::refresh() {
    wrefresh(mainWin);
    wrefresh(extendedWin);
}

MainMenu::MENU_ACTION MainMenu::run() {
    int curSelection = 0;
    int movement;
    while(true) {
        mvwprintw(mainWin, 2 + 2*curSelection, 2, "->");
        wrefresh(mainWin);

        extendedWindow(curSelection);
        wrefresh(extendedWin);

        movement = getch();

        mvwprintw(mainWin, 2 + 2*curSelection, 2, "  ");

        if (movement == 'w' || movement == KEY_UP)
            curSelection = curSelection > 0 ? curSelection - 1 : curSelection;
        else if (movement == 's' || movement == KEY_DOWN)
            curSelection = curSelection < 6 ? curSelection + 1 : curSelection;
        else if (movement == 27 ) // 27 == klavesa ESC
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
                                    (selection == 3 ? EXPORT_TO_TXT_QAS : EXPORT_TO_TXT_AS ))));
                        }
                        else if (c == 'n' || c == KEY_LEFT)
                            break;
                    }
                    break;
                }
                case 4:
                    return NONE;   // TODO
                case 5:
                    return NONE;   // TODO
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
