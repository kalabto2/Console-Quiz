//
// Created by tom on 19.04.20.
//

#include "Answer.h"
//#include "helpers.cpp"

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <fstream>


using namespace std;


Answer::Answer() {
    getmaxyx(stdscr,screenHeight, screenWidth);

    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%Y%m%d-%H:%M:%S",timeinfo);
    std::string str(buffer);
    id = str;
}

void Answer::save() {

}

void Answer::construct() {

}

string Answer::getId() {
    return  id;
}

bool Answer::autoEval(WINDOW *win, string info) {
    box(win, 0, 0); // vytvori hranice okolo okna
    mvwprintw(win, 2, 2, "Do you want auto-evaluation? (y/n)");
    wmove(win, 3, 2);    // presune kurzor do okna na x, y pozici
    wrefresh(win);

    bool autoEv = false;
    while (true){
        int a = getch();
        if (a == 'y' || a == KEY_RIGHT){
            autoEv = true;
            break;
        }
        else if (a == 'n')
            break;
    }

    return autoEv;
}


/* ------------------------------------------------------------------------------------------------------------------ */


TextAnswer::TextAnswer() : Answer() {}

void TextAnswer::save() {
    ofstream outFile(ANSWER_FILE_PATH + id);
    if (outFile.is_open())
    {
        outFile << "txtA" << endl;
        outFile << correctAnswer;
        outFile.close();
    }
}

void TextAnswer::construct() {
    WINDOW * inputWin = newwin((screenHeight - 5) / 2, screenWidth - 60, 5 + ((screenHeight - 5) / 2), 60); // fce newwin vytvori okno
    /*box(inputWin, 0, 0); // vytvori hranice okolo okna
    mvwprintw(inputWin, 2, 2, "Do you want auto-evaluation? (y/n)");
    wmove(inputWin, 3, 2);    // presune kurzor do okna na x, y pozici
    wrefresh(inputWin);

    bool autoEv = false;
    while (true){
        int a = getch();
        if (a == 'y' || a == KEY_RIGHT){
            autoEv = true;
            break;
        }
        else if (a == 'n')
            break;
    }*/
    bool autoEv = autoEval(inputWin, "");

    if (autoEv){
        mvwprintw(inputWin, 4, 2, "> ");
        curs_set(1);
        wrefresh(inputWin);
        //correctAnswer = getInput(inputWin);
    }
}


/* ------------------------------------------------------------------------------------------------------------------ */


ValueAnswer::ValueAnswer() : Answer() {}

void ValueAnswer::save() {
    ofstream outFile(ANSWER_FILE_PATH + id);
    if (outFile.is_open())
    {
        outFile << "valA" << endl;
        outFile << correctAnswer;
        outFile.close();
    }
}


/* ------------------------------------------------------------------------------------------------------------------ */


SingleChoiceAnswer::SingleChoiceAnswer() : Answer(), correctAnswer(0) {}

void SingleChoiceAnswer::save() {
    ofstream outFile(ANSWER_FILE_PATH + id);
    if (outFile.is_open())
    {
        outFile << "schA" << endl;
        outFile << correctAnswer;
        outFile.close();
    }
}


/* ------------------------------------------------------------------------------------------------------------------ */


MultipleChoiceAnswer::MultipleChoiceAnswer() : Answer() {}

void MultipleChoiceAnswer::save() {
    ofstream outFile(ANSWER_FILE_PATH + id);
    if (outFile.is_open())
    {
        outFile << "mchA" << endl;
        int i = 0;
        for (auto & choice : correctAnswer) {
            if (i != 0)
                outFile << " ";
            outFile << choice;
            i++;
        }
        outFile.close();
    }
}


/* ------------------------------------------------------------------------------------------------------------------ */


PairChoiceAnswer::PairChoiceAnswer() : Answer() {}

void PairChoiceAnswer::save() {
    ofstream outFile(ANSWER_FILE_PATH + id);
    if (outFile.is_open())
    {
        outFile << "pchA" << endl;
        int i = 0;
        for (auto & choice : correctAnswer) {
            if (i != 0)
                outFile << " ";
            outFile << choice.first << " " << choice.second;
            i++;
        }
        outFile.close();
    }
}
