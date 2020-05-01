//
// Created by tom on 18.04.20.
//

#include "Question.h"

#include <utility>
#include <ncurses.h>
#include <fstream>
#include <ctime>

#include "helpers.cpp"
/*
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
}*/


Question::Question() {
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

void Question::construct() {

}

void Question::save() {

}

void Question::renderAnswers(WINDOW *window) {

}

shared_ptr<Answer> Question::getTypeAnswer(int i) {
    return nullptr;
}

string Question::getId() {
    return id;
}

int Question::getNumOfAnsw() {
    return 0;
}


/* ------------------------------------------------------------------------------------------------------------------ */

TextQuestion::TextQuestion(string question) : question(question) {}

TextQuestion::TextQuestion() : Question() {}

void TextQuestion::setQuestion(string question){
    this->question = std::move(question);
}

void TextQuestion::construct() {
    WINDOW * inputWin = newwin((screenHeight - 5) / 2, screenWidth - 60, 5, 60); // fce newwin vytvori okno
    box(inputWin, 0, 0); // vytvori hranice okolo okna
    mvwprintw(inputWin, 2, 2, "Enter text of the question. (e.g. 'Which city is capital of Czech Republic')");
    curs_set(1);    // zviditelni kurzor
    wmove(inputWin, 3, 2);    // presune kurzor do okna na x, y pozici
    wrefresh(inputWin);

    /*std::string text;

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

    question = text;*/
    question = getInput(inputWin);
    curs_set(0);
}

void TextQuestion::save() {
    ofstream outFile(QUESTION_FILE_PATH + id);
    if (outFile.is_open())
    {
        outFile << "txtQ" << endl;
        outFile << question;
        outFile.close();
    }
}

void TextQuestion::renderAnswers(WINDOW * window) {
    mvwprintw(window, (screenHeight - 5) / 2 + 2, 6 , "* Text Answer           ");
    mvwprintw(window, (screenHeight - 5) / 2 + 4, 6 , "* Value Answer          ");
    mvwprintw(window, (screenHeight - 5) / 2 + 6, 6 , "                        ");
    wrefresh(window);
}

shared_ptr<Answer> TextQuestion::getTypeAnswer(int i) {
    if (i == 1)
        return shared_ptr<Answer> (new TextAnswer ());
    else if (i == 2)
        return shared_ptr<Answer> (new ValueAnswer());

    return nullptr;
}

int TextQuestion::getNumOfAnsw() {
    return 2;
}

/* ------------------------------------------------------------------------------------------------------------------ */

ChoiceQuestion::ChoiceQuestion() : Question() {}

void ChoiceQuestion::construct() {
    WINDOW * inputWin = newwin((screenHeight - 5) / 2, screenWidth - 60, 5, 60); // fce newwin vytvori okno
    box(inputWin, 0, 0); // vytvori hranice okolo okna
    mvwprintw(inputWin, 2, 2, "Enter question to choices: (e.g. 'Which of following is true?')");
    curs_set(1);    // zviditelni kurzor
    wmove(inputWin, 3, 2);    // presune kurzor do okna na x, y pozici
    wrefresh(inputWin);

    question = getInput(inputWin);

    wclear(inputWin);
    box(inputWin, 0, 0); // vytvori hranice okolo okna
    mvwprintw(inputWin, 2, 2, "Enter choices to question: (press KEY RIGHT to confirm)");
    mvwprintw(inputWin, 3, 4, "1.  >");
    wmove(inputWin, 3, 10);    // presune kurzor do okna na x, y pozici
    wrefresh(inputWin);

    for (int i = 0; i < 20; i++){
        choices.emplace_back(getInput(inputWin));

        int y,x;
        getyx(inputWin,y,x);
        curs_set(0);
        mvwprintw(inputWin, y + 1, 8, "  Press KEY RIGHT to Exit & Save Question, or add another choice (any other KEY)");
        wrefresh(inputWin);

        int a = getch();
        if (a == KEY_RIGHT)
            break;

        mvwprintw(inputWin, y + 1, 4, to_string(i + 2).c_str());
        wprintw(inputWin, ".");
        mvwprintw(inputWin, y + 1, 8, ">                                                                               ");
        wmove(inputWin, y + 1, 10);
        curs_set(1);
        wrefresh(inputWin);
    }
    wclear(inputWin);
}

void ChoiceQuestion::save() {
    ofstream outFile(QUESTION_FILE_PATH + id);
    if (outFile.is_open())
    {
        outFile << "chcQ" << endl;
        for (auto & choice : choices){
            outFile << choice << endl;
        }
        outFile << endl;
        outFile << question;
        outFile.close();
    }
}

void ChoiceQuestion::renderAnswers(WINDOW *window) {
    mvwprintw(window, (screenHeight - 5) / 2 + 2, 6 , "* Single Choice Answer  ");
    mvwprintw(window, (screenHeight - 5) / 2 + 4, 6 , "* Multiple Choice Answer");
    mvwprintw(window, (screenHeight - 5) / 2 + 6, 6 , "* Pair Choice Answer    ");
    wrefresh(window);
}

shared_ptr<Answer> ChoiceQuestion::getTypeAnswer(int i) {
    if (i == 1)
        return shared_ptr<Answer> (new SingleChoiceAnswer());
    else if (i == 2)
        return shared_ptr<Answer> (new MultipleChoiceAnswer());
    else if (i == 3)
        return shared_ptr<Answer> (new PairChoiceAnswer());

    return nullptr;
}

int ChoiceQuestion::getNumOfAnsw() {
    return 3;
}

