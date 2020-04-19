//
// Created by tom on 18.04.20.
//

#include "Question.h"

#include <utility>
#include <ncurses.h>
#include <fstream>


Question::Question() {
    getmaxyx(stdscr,screenHeight, screenWidth);
}

void Question::construct() {

}

void Question::save() {

}

/* ----------------------------------------------------- */

//TextQuestion::TextQuestion(int id, string question) : Question(id), question(std::move(question)) {}

TextQuestion::TextQuestion(string question) : question(question) {}

TextQuestion::TextQuestion() : Question() {}

void TextQuestion::setQuestion(string question){
    this->question = question;
}

void TextQuestion::construct() {
    WINDOW * inputWin = newwin((screenHeight - 5) / 2, screenWidth - 60, 5, 60); // fce newwin vytvori okno
    box(inputWin, 0, 0); // vytvori hranice okolo okna
    mvwprintw(inputWin, 2, 2, "Enter text of the question. (e.g. 'Which city is capital of Czech Republic')");
    curs_set(1);    // zviditelni kurzor
    wmove(inputWin, 3, 2);    // presune kurzor do okna na x, y pozici
    wrefresh(inputWin);

    std::string text;

    while (true){
        int a = getch();

        if(a == KEY_BACKSPACE || a == (int)'\b' || a == 127) {
            int x, y;
            getyx(inputWin, y, x);
            mvwprintw(inputWin, y, --x, " ");
            wmove(inputWin, y, x);
            wrefresh(inputWin);
            if (!text.empty())
                text.pop_back();
            continue;
        }

        if ( a == KEY_ENTER || a == KEY_RIGHT)
            break;

        const char * tmp = new const char (a);
        wprintw(inputWin, tmp);
        wrefresh(inputWin);
        delete tmp;

        text += (char)a;
    }

    question = text;
}

void TextQuestion::save() {
    ofstream outFile(QUESTION_FILE_PATH + "123"); // TODO opravit na automaticke dle id
    if (outFile.is_open())
    {
        outFile << question;
        outFile.close();
    }
}

/* ----------------------------------------------------- */

