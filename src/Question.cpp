//
// Created by tom on 18.04.20.
//

#include "Question.h"

#include <ncurses.h>
#include <fstream>
#include <ctime>

const string Question::QUESTION_FILE_PATH = "files/questions/";

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

void Question::construct() {}

void Question::save() {}

void Question::renderAnswers(WINDOW *window) {}

shared_ptr<Answer> Question::getTypeAnswer(int i) {
    return nullptr;
}

string Question::getId() {
    return id;
}

int Question::getNumOfAnsw() {
    return 0;
}

shared_ptr<Question> Question::getQuestion(const string& questionId) {
    ifstream inFile(Question::QUESTION_FILE_PATH + questionId);
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
    return std::string("Vytisknula se superclass :(. Data ztracena ...");
}

Question::~Question() = default;


/* ------------------------------------------------------------------------------------------------------------------ */


TextQuestion::TextQuestion(const string& questionId) {
    getmaxyx(stdscr,screenHeight, screenWidth);
    id = questionId;

    ifstream inFile(QUESTION_FILE_PATH + questionId);
    string line;

    if (inFile.is_open()){
        for (int i = 0; getline(inFile, line); i++){
            if (i == 0) {
                if (line != "txtQ") {
                    inFile.close();
                    throw "Incompatible file type: expected 'txtQ'";
                }
            }
            else {
                question += line + '\n';
            }
        }
        inFile.close();
    } else
        throw "Couldnt open or find file of type 'txtQ'";
}

TextQuestion::TextQuestion() : Question() {}

void TextQuestion::construct() {
    const int SIDE_WIN_WIDTH = 60;
    WINDOW * inputWin = newwin((screenHeight - 5) / 2, screenWidth - SIDE_WIN_WIDTH, 5, SIDE_WIN_WIDTH);
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
        mvwprintw(inputWin, y, 2, "To save & exit press KEY ESCAPE");
        wrefresh(inputWin);
        int c = getch();
        if (c == 27)    // KEY ESC
            break;

        mvwprintw(inputWin, y, 2, "                               ");
        wmove(inputWin, y, 2);
        wrefresh(inputWin);
    }

    delwin(inputWin);
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

TextQuestion::~TextQuestion() = default;

/* ------------------------------------------------------------------------------------------------------------------ */

ChoiceQuestion::ChoiceQuestion() : Question() {}

void ChoiceQuestion::construct() {
    const int SIDE_WIN_WIDTH = 60;
    WINDOW * inputWin = newwin((screenHeight - 5) / 2, screenWidth - SIDE_WIN_WIDTH, 5, SIDE_WIN_WIDTH);
    box(inputWin, 0, 0);
    mvwprintw(inputWin, 2, 2, "Enter question to choices: (e.g. 'Which of following is true?')");
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
        mvwprintw(inputWin, y, 2, "To confirm description press KEY ESCAPE");
        wrefresh(inputWin);
        int c = getch();
        if (c == 27)
            break;

        mvwprintw(inputWin, y, 2, "                                       ");
        wmove(inputWin, y, 2);
        wrefresh(inputWin);
    }
    question = res;

    wclear(inputWin);
    box(inputWin, 0, 0);
    mvwprintw(inputWin, 2, 2, "Enter choices to question: (press KEY ENTER to confirm)");
    mvwprintw(inputWin, 3, 4, "1.  >");
    wmove(inputWin, 3, 10);
    wrefresh(inputWin);

    for (int i = 0; i < 20; i++){
        string res2;
        char input2[500];
        echo();
        wgetnstr(inputWin, input2, 499);
        noecho();
        res2 += string(input2);
        choices.push_back(res2);

        int y,x;
        getyx(inputWin,y,x);
        curs_set(0);
        mvwprintw(inputWin, y, 8, "  Press KEY ESC to Exit & Save Question, or add another choice (any other KEY)");
        wrefresh(inputWin);

        int a = getch();
        if (a == 27)    // KEY_ESC
            break;

        mvwprintw(inputWin, y, 4, to_string(i + 2).c_str());
        wprintw(inputWin, ".");
        mvwprintw(inputWin, y, 8, ">                                                                             ");
        wmove(inputWin, y, 10);
        curs_set(1);
        wrefresh(inputWin);
    }
    wclear(inputWin);
    delwin(inputWin);
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

ChoiceQuestion::ChoiceQuestion(const string& questionId) {
    getmaxyx(stdscr,screenHeight, screenWidth);
    id = questionId;

    ifstream inFile(QUESTION_FILE_PATH + questionId);
    string line;

    if (inFile.is_open()){
        for (int i = 0; getline(inFile, line); i++){
            if (i == 0) {
                if (line != "chcQ") {
                    inFile.close();
                    throw "Incompatible file type: expected 'chcQ'";
                }
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
    } else
        throw "Couldn't find or open file of type 'chcQ'";
}

string ChoiceQuestion::print() {
    string res;

    int i = 1;
    for (auto & choice : choices) {
        res += "\n\t\t" + to_string(i) + ".\t" + choice;
        i ++;
    }
    return question + "\n\tChoose from following(" + to_string(i - 1) + "):" + res + "\n";
}

ChoiceQuestion::~ChoiceQuestion() = default;

/* ------------------------------------------------------------------------------------------------------------------ */

SortingQuestion::SortingQuestion(const string& questionId) {
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
    } else
        throw "Couldn't find or open file of type 'srtQ'";
}

SortingQuestion::SortingQuestion() : Question() {}

void SortingQuestion::construct() {
    const int SIDE_WIN_WIDTH = 60;
    WINDOW * inputWin = newwin((screenHeight - 5) / 2, screenWidth - SIDE_WIN_WIDTH, 5, SIDE_WIN_WIDTH);
    box(inputWin, 0, 0);
    mvwprintw(inputWin, 2, 2, "Enter description to following sorting : (e.g. 'Sort by oldest ...')");
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
        mvwprintw(inputWin, y, 2, "To save & exit press KEY ESCAPE");
        wrefresh(inputWin);
        int c = getch();
        if (c == 27)
            break;

        mvwprintw(inputWin, y, 2, "                               ");
        wmove(inputWin, y, 2);
        wrefresh(inputWin);
    }
    question = res;

    wclear(inputWin);
    box(inputWin, 0, 0);
    mvwprintw(inputWin, 2, 2, "Enter text to be sorted: (press KEY ENTER to confirm)");
    mvwprintw(inputWin, 3, 4, "1.  >");
    wmove(inputWin, 3, 10);
    wrefresh(inputWin);

    for (int i = 0; i < 20; i++){
        string res2;
        char input2[500];
        echo();
        wgetnstr(inputWin, input2, 499);
        noecho();
        res2 += string(input2);
        choices.push_back(res2);

        int y,x;
        getyx(inputWin,y,x);
        curs_set(0);
        mvwprintw(inputWin, y, 8, "  Press KEY ESC to Exit & Save Question, or add another sorting choice (any other KEY)");
        wrefresh(inputWin);

        int a = getch();
        if (a == 27)    // KEY_ESC
            break;

        mvwprintw(inputWin, y, 4, to_string(i + 2).c_str());
        wprintw(inputWin, ".");
        mvwprintw(inputWin, y, 8, ">                                                                                     ");
        wmove(inputWin, y, 10);
        curs_set(1);
        wrefresh(inputWin);
    }
    wclear(inputWin);
    delwin(inputWin);
}

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
    mvwprintw(window, (screenHeight - 5) / 2 + 2, 6 , "* Text Answer           ");
    mvwprintw(window, (screenHeight - 5) / 2 + 4, 6 , "                        ");
    mvwprintw(window, (screenHeight - 5) / 2 + 6, 6 , "                        ");
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

SortingQuestion::~SortingQuestion() = default;


