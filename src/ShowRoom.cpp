//
// Created by tom on 19.05.20.
//

#include <ncurses.h>
#include <numeric>
#include <algorithm>
#include <filesystem>

#include "ShowRoom.h"

const int QUIZ_FACTORY_DIALOG_HEIGHT = 10;
const int QUIZ_FACTORY_DIALOG_WIDTH = 50;

ShowRoom::ShowRoom(Quiz quiz) : quiz(quiz), answerSheet(quiz){
    getmaxyx(stdscr, screenHeight, screenWidth);
}

ShowRoom::ShowRoom(string quizId) : quiz(quizId), answerSheet(quiz){
    getmaxyx(stdscr, screenHeight, screenWidth);
}

ShowRoom::ShowRoom(string quizId, string answerSheetId) : quiz(quizId), answerSheet(quiz, answerSheetId){
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

    //bool printQuestion = true, printAnswer = true, printAnswerSpace = false;
    string output;
    if (action == MainMenu::EXPORT_TO_TXT_QA){
        output = quiz.print(true, true, false);
    } else if (action == MainMenu::EXPORT_TO_TXT_Q){
        //printAnswer = false;
        output = quiz.print(true, false, false);
    } else if (action == MainMenu::EXPORT_TO_TXT_QS){
        //printAnswer = false;
        //printAnswerSpace = true;
        output = quiz.print(true, false, true);
    } else if (action == MainMenu::EXPORT_TO_TXT_QAS){  // TODO
        output = answerSheet.print(true);
    } else if (action == MainMenu::EXPORT_TO_TXT_AS){   // TODO
        output = answerSheet.print(false);
    }
    //string output = quiz.print(printQuestion,printAnswer, printAnswerSpace);

    ofstream outFile(EXPORTS_FILE_PATH + string(name2));
    if (outFile.is_open())
    {
        outFile << output;
        outFile.close();
    }
}

void ShowRoom::StartQuiz(bool fillMode) {
    wclear(stdscr);
    refresh();
    WINDOW * upperWin = newwin(5, screenWidth, 0, 0);
    box(upperWin, 0,0);
    mvwprintw(upperWin, 2, screenWidth/2 - 6, (fillMode ? "START FILLING!" : "EVALUATE QUIZ"));
    mvwprintw(upperWin, 2, 7, ("Quiz - " + quiz.getName()).c_str());
    mvwprintw(upperWin, 2, screenWidth - 7 - 20, ("id: " + quiz.getId()).c_str());
    wrefresh(upperWin);

    vector <vector <int> > sheetCursorHeight;
    vector <string> sheets;
    tie(sheets, sheetCursorHeight) = quiz.getPrintedSheets(true, false);//todo here

    for (auto &i: sheetCursorHeight) {
        i[i.size() - 1] += 2;
        i.push_back(2);
    }

    for (size_t j = 0; j < sheets.size(); j++) {
        showWinScroll = 0;
        int winHeight = count(sheets[j].begin(), sheets[j].end(), '\n') + 8;
        WINDOW *showWin = newwin(winHeight, screenWidth, 6, 0);
        scrollok(showWin, true);

        string output = sheets[j];
        int numberOfOptions = sheetCursorHeight[j].size();
        scrollWin(showWin, output, 0);  // for first rendering

        bool previous = false;
        int c, selection = 0;
        while (true){
            c = getch();
            if (c == 'w' || c == KEY_UP){
                int lastSelection = selection;
                selection = (selection - 1 < 0 ? 0 : selection - 1);
                if (lastSelection == 0)
                    continue;
                scrollWin(showWin, output, -sheetCursorHeight[j][selection]);
            } else if (c == 's' || c == KEY_DOWN){
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
                if (fillMode)
                    answerSheet.renderInput(j, selection);
                else
                    answerSheet.renderEvaluation(j, selection);

                scrollWin(showWin, output, 0);
                wrefresh(showWin);
            } else if (c == ' ')
                scrollWin(showWin, output, 1);
        }

        if (previous){
            j -= 2;
            continue;
        }
    }
    if (!fillMode)
        answerSheet.setEvaluated(true);
    answerSheet.save();

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

string ShowRoom::selectAnswersheet(string quizId) {
    return selectFile(false, quizId);
}

string ShowRoom::selectQuiz() {
    return selectFile();
}

string ShowRoom::selectFile(bool findQuiz, string quizId) {
    int screenWidth, screenHeight;
    getmaxyx(stdscr, screenHeight, screenWidth);
    wclear(stdscr);
    refresh();
    WINDOW * upperWin = newwin(5, screenWidth, 0, 0); // fce newwin vytvori okno
    box(upperWin, 0,0); // vytvori hranice okolo okna
    mvwprintw(upperWin, 2, screenWidth/2 - 7, (findQuiz ? "QUIZ SELECTOR" : "ANSWERSHEET SELECTOR"));
    wrefresh(upperWin);

    vector<string> fileNames;
    vector< vector<string> > fileData;
    namespace fs = std::filesystem;

    std::string path = (findQuiz ? "./files/quizzes/" : "./files/answerSheets/");
    for (const auto & entry : fs::directory_iterator(path)) {
        vector<string> a = (findQuiz ? Quiz::preview(entry.path()) : AnswerSheet::preview(entry.path()));
        if (findQuiz || a[3] == quizId.substr(string("./files/quizzes/").size())) {
            fileData.push_back(a);
            fileNames.push_back(entry.path());
        }
    }

    WINDOW * showWin = newwin(screenHeight - 5, screenWidth, 6, 0); // fce newwin vytvori okno
    box(showWin, 0,0); // vytvori hranice okolo okna

    if (fileNames.empty()){
        mvwprintw(showWin, 2, 10, (findQuiz ? "NO QUIZ FOUND" : ("NO ANSWERSHEET TO " + quizId + " FOUND").c_str()));
        mvwprintw(showWin, 3, 10, "Press any key ...");
        wrefresh(showWin);
        getch();
        return "";
    }

    for (size_t i = 0; i < fileNames.size(); i++){
        mvwprintw(showWin, 2 + i * 2, 10, fileNames[i].substr(fileNames[i].size() - 17).c_str());
        mvwprintw(showWin, 2 + i * 2, 50, fileData[i][1].c_str());
        if (!findQuiz)
            mvwprintw(showWin, 2 + i * 2, 75, fileData[i][2].c_str());
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
            pointerPos += (pointerPos < 2 * fileNames.size() ? 2 : 0);
        } else if (a == KEY_UP || a == 'w') {
            mvwprintw(showWin, pointerPos, 3, "  ");
            pointerPos -= (pointerPos > 2 ? 2 : 0);
        }
        mvwprintw(showWin, pointerPos, 3, "=>");
        wrefresh(showWin);
    }

    return fileNames[pointerPos / 2 - 1];
}

void ShowRoom::setAuthor(string author) {
    answerSheet.setAuthor(author);
}
