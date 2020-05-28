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

shared_ptr<Question> Question::getQuestion(string questionId) {
    ifstream inFile("files/questions/" + questionId);
    string line;

    if (inFile.is_open()){
        getline(inFile, line);
        inFile.close();
    }

    if (line == "txtQ")
        return shared_ptr<Question> (new TextQuestion(questionId));
    else if (line == "chcQ")
        return shared_ptr<Question> (new ChoiceQuestion(questionId));
    else if (line == "srtQ")
        return shared_ptr<Question> (new SortingQuestion(questionId));

    throw "Incompatible file type: expected 'txtQ', 'chcQ' or 'srtQ'";
}

string Question::print() {
    return std::string("Vytisknula se superclass :(. Data ztracena");
}


/* ------------------------------------------------------------------------------------------------------------------ */

TextQuestion::TextQuestion(const string& questionId) {
    getmaxyx(stdscr,screenHeight, screenWidth);
    id = questionId;

    ifstream inFile(QUESTION_FILE_PATH + questionId);
    string line;

    if (inFile.is_open()){
        for (int i = 0; getline(inFile, line); i++){
            if (i == 0) {
                if (line != "txtQ")
                    throw "Incompatible file type: expected 'txtQ'";
            }
            else {
                question += line + '\n';
            }
        }
        inFile.close();
    }
}

TextQuestion::TextQuestion() : Question() {}

void TextQuestion::setQuestion(string question){
    this->question = std::move(question);
}

void TextQuestion::construct() {
    WINDOW * inputWin = newwin((screenHeight - 5) / 2, screenWidth - 60, 5, 60);
    box(inputWin, 0, 0);
    mvwprintw(inputWin, 2, 2, "Enter text of the question. (e.g. 'Which city is capital of Czech Republic')");
    curs_set(1);
    wmove(inputWin, 3, 2);
    wrefresh(inputWin);

    string res;
    char input[500];
    for (int i = 0; ; i++){
        echo();
        wgetnstr(inputWin, input, 499);
        noecho();
        res += (i == 0 ? "" : "\n") + string(input);
        int y,x;
        getyx(inputWin, y, x);
        mvwprintw(inputWin, y, 2, "To save & exit pres KEY ESCAPE");
        wrefresh(inputWin);
        int c = getch();
        if (c == 27)
            break;

        mvwprintw(inputWin, y, 2, "                              ");
        wmove(inputWin, y, 2);
        wrefresh(inputWin);
    }

    question = res;
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

string TextQuestion::print() {
    return question;
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

ChoiceQuestion::ChoiceQuestion(string questionId) {
    getmaxyx(stdscr,screenHeight, screenWidth);
    id = questionId;

    ifstream inFile(QUESTION_FILE_PATH + questionId);
    string line;

    if (inFile.is_open()){
        for (int i = 0; getline(inFile, line); i++){
            if (i == 0) {
                if (line != "chcQ")
                    throw "Incompatible file type: expected 'chcQ'";
            }
            else if (!line.empty()){
                choices.push_back(line);
            }
            else
                break;
        }
        while (getline(inFile, line)){
            question += line + '\n';
        }
        inFile.close();
    }
}

string ChoiceQuestion::print() {
    string res;

    int i = 1;
    for (auto & choice : choices) {
        res += "\n\t\t" + to_string(i) + ".\t" + choice;
        i ++;
    }
    return question + "\n\tChoose from following:" + res + "\n";
}

/* ------------------------------------------------------------------------------------------------------------------ */

SortingQuestion::SortingQuestion(string questionId) {
    getmaxyx(stdscr,screenHeight, screenWidth);
    id = questionId;

    ifstream inFile(QUESTION_FILE_PATH + questionId);
    string line;

    if (inFile.is_open()){
        for (int i = 0; getline(inFile, line); i++){
            if (i == 0) {
                if (line != "srtQ")
                    throw "Incompatible file type: expected 'srtQ'";
            }
            else if (!line.empty()){
                choices.push_back(line);
            }
            else
                break;
        }
        while (getline(inFile, line)){
            question += line + '\n';
        }
        inFile.close();
    }
}

SortingQuestion::SortingQuestion() : Question() {}

void SortingQuestion::construct() {
    WINDOW * inputWin = newwin((screenHeight - 5) / 2, screenWidth - 60, 5, 60); // fce newwin vytvori okno
    box(inputWin, 0, 0); // vytvori hranice okolo okna
    mvwprintw(inputWin, 2, 2, "Enter description to following sorting : (e.g. 'Sort by oldest ...')");
    curs_set(1);    // zviditelni kurzor
    wmove(inputWin, 3, 2);    // presune kurzor do okna na x, y pozici
    wrefresh(inputWin);

    question = getInput(inputWin);

    wclear(inputWin);
    box(inputWin, 0, 0); // vytvori hranice okolo okna
    mvwprintw(inputWin, 2, 2, "Enter text to be sorted: (press KEY RIGHT to confirm)");
    mvwprintw(inputWin, 3, 4, "1.  >");
    wmove(inputWin, 3, 10);    // presune kurzor do okna na x, y pozici
    wrefresh(inputWin);

    for (int i = 0; i < 20; i++){
        choices.emplace_back(getInput(inputWin));

        int y,x;
        getyx(inputWin,y,x);
        curs_set(0);
        mvwprintw(inputWin, y + 1, 8, "  Press KEY RIGHT to Exit & Save Question, or add another sorting choice (any other KEY)");
        wrefresh(inputWin);

        int a = getch();
        if (a == KEY_RIGHT)
            break;

        mvwprintw(inputWin, y + 1, 4, to_string(i + 2).c_str());
        wprintw(inputWin, ".");
        mvwprintw(inputWin, y + 1, 8, ">                                                                                       ");
        wmove(inputWin, y + 1, 10);
        curs_set(1);
        wrefresh(inputWin);
    }
    wclear(inputWin);}

void SortingQuestion::save() {
    ofstream outFile(QUESTION_FILE_PATH + id);
    if (outFile.is_open())
    {
        outFile << "srtQ" << endl;
        for (auto & choice : choices){
            outFile << choice << endl;
        }
        outFile << endl;
        outFile << question;
        outFile.close();
    }}

void SortingQuestion::renderAnswers(WINDOW *window) {
    mvwprintw(window, (screenHeight - 5) / 2 + 2, 6 , "* Sorting Answer        ");
    wrefresh(window);
}

shared_ptr<Answer> SortingQuestion::getTypeAnswer(int i) {
    if (i == 1)
        return shared_ptr<Answer> (new TextAnswer());
    return nullptr;
}

int SortingQuestion::getNumOfAnsw() {
    return 1;
}

string SortingQuestion::print() {
    string res;

    int i = 1;
    for (auto & choice : choices) {
        res += "\n\t\t" + to_string(i) + ".\t" + choice;
        i ++;
    }
    return question + "\n\tSort following:" + res + "\n";
}


