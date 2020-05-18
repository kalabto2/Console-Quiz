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
#include <algorithm>
#include <sstream>


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

shared_ptr<Answer> Answer::getAnswer(string answerId) {
    ifstream inFile("files/answers/" + answerId);
    string line;

    if (inFile.is_open()){
        getline(inFile, line);
        inFile.close();
    }

    if (line == "txtA")
        return shared_ptr<Answer> (new TextAnswer(answerId));
    else if (line == "valA")
        return shared_ptr<Answer> (new ValueAnswer(answerId));
    else if (line == "schA")
        return shared_ptr<Answer> (new SingleChoiceAnswer(answerId));
    else if (line == "mchA")
        return shared_ptr<Answer> (new MultipleChoiceAnswer(answerId));
    else if (line == "pchA")
        return shared_ptr<Answer> (new PairChoiceAnswer(answerId));

    throw "Incompatible file type: expected 'txtA', 'valA', 'schA', 'mchA' or 'pchA' ";
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
    WINDOW * inputWin = newwin((screenHeight - 5) / 2, screenWidth - 60, 5 + ((screenHeight - 5) / 2), 60);
    bool autoEv = autoEval(inputWin, "");

    if (autoEv){
        mvwprintw(inputWin, 4, 4, "Enter correct answer (e.g. 'Prague'):");
        mvwprintw(inputWin, 5, 2, "> ");
        curs_set(1);
        wrefresh(inputWin);
        char tmp[100];
        echo();
        wgetstr(inputWin, tmp);
        noecho();
        curs_set(0);
        correctAnswer = string(tmp);
    }
}

TextAnswer::TextAnswer(string answerId) {
    getmaxyx(stdscr,screenHeight, screenWidth);
    id = answerId;

    ifstream inFile(ANSWER_FILE_PATH + answerId);
    string line;

    if (inFile.is_open()){
        for (int i = 0; getline(inFile, line); i++){
            if (i == 0) {
                if (line != "txtA")
                    throw "Incompatible file type: expected 'txtA'";
            }
            else {
                correctAnswer += line + '\n';
            }
        }
        inFile.close();
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

void ValueAnswer::construct() {
    WINDOW * inputWin = newwin((screenHeight - 5) / 2, screenWidth - 60, 5 + ((screenHeight - 5) / 2), 60); // fce newwin vytvori okno
    bool autoEv = autoEval(inputWin, "");

    if (autoEv){
        mvwprintw(inputWin, 4, 4, "Enter correct value (e.g. '55'):");
        mvwprintw(inputWin, 5, 2, "> ");
        curs_set(1);
        wrefresh(inputWin);
        char tmp[100];
        echo();
        wgetstr(inputWin, tmp);
        noecho();
        curs_set(0);
        correctAnswer = string(tmp);
    }
}

ValueAnswer::ValueAnswer(string answerId) {
    getmaxyx(stdscr,screenHeight, screenWidth);
    id = answerId;

    ifstream inFile(ANSWER_FILE_PATH + answerId);
    string line;

    if (inFile.is_open()){
        for (int i = 0; getline(inFile, line); i++){
            if (i == 0) {
                if (line != "valA")
                    throw "Incompatible file type: expected 'valA'";
            }
            else {
                correctAnswer += line;
            }
        }
        inFile.close();
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

void SingleChoiceAnswer::construct() {
    WINDOW * inputWin = newwin((screenHeight - 5) / 2, screenWidth - 60, 5 + ((screenHeight - 5) / 2), 60); // fce newwin vytvori okno
    bool autoEv = autoEval(inputWin, "");

    if (autoEv){
        mvwprintw(inputWin, 4, 4, "Enter number of correct choice (e.g. '2' -- only number):");
        mvwprintw(inputWin, 5, 2, "> ");
        curs_set(1);
        wrefresh(inputWin);
        char tmp[100];
        echo();
        wgetstr(inputWin, tmp);
        noecho();
        curs_set(0);
        preprocess(string(tmp));
    }
}

void SingleChoiceAnswer::preprocess(string answer) {
    string number;
    bool ws = true;

    for (auto & ch : answer){
        if (iswspace(ch) && ws)
            continue;
        if (isdigit(ch)){
            number += ch;
            ws = false;
            continue;
        }
        break;
    }

    correctAnswer = stoi(number);
}

SingleChoiceAnswer::SingleChoiceAnswer(string answerId) {
    getmaxyx(stdscr,screenHeight, screenWidth);
    id = answerId;

    ifstream inFile(ANSWER_FILE_PATH + answerId);
    string line;

    if (inFile.is_open()){
        for (int i = 0; getline(inFile, line); i++){
            if (i == 0) {
                if (line != "schA")
                    throw "Incompatible file type: expected 'schA'";
            }
            else if (i == 1){
                correctAnswer = stoi(line);
            }
        }
        inFile.close();
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

void MultipleChoiceAnswer::construct() {
    WINDOW * inputWin = newwin((screenHeight - 5) / 2, screenWidth - 60, 5 + ((screenHeight - 5) / 2), 60); // fce newwin vytvori okno
    bool autoEv = autoEval(inputWin, "");

    if (autoEv){
        mvwprintw(inputWin, 4, 4, "Enter number of correct choices (e.g. '2, 4, 1' -- seperated by comma in any order):");
        mvwprintw(inputWin, 5, 2, "> ");
        curs_set(1);
        wrefresh(inputWin);
        char tmp[100];
        echo();
        wgetstr(inputWin, tmp);
        noecho();
        curs_set(0);
        preprocess(string(tmp));
    }
}

void MultipleChoiceAnswer::preprocess(string answer) {
    string number;
    bool comma = false;

    for (auto & ch : answer){
        if (iswspace(ch))
            continue;
        if (ch == ',' && comma){
            correctAnswer.insert(stoi(number));
            number = "";
            comma = false;
            continue;
        }
        if (isdigit(ch)){
            number += ch;
            comma = true;
            continue;
        }
        break;
    }
    correctAnswer.insert(stoi(number));
    number = "";
}

MultipleChoiceAnswer::MultipleChoiceAnswer(string answerId) {
    getmaxyx(stdscr,screenHeight, screenWidth);
    id = answerId;

    ifstream inFile(ANSWER_FILE_PATH + answerId);
    string line;

    if (inFile.is_open()){
        for (int i = 0; getline(inFile, line); i++){
            if (i == 0) {
                if (line != "mchA")
                    throw "Incompatible file type: expected 'mchA'";
            }
            else if (i == 1){
                istringstream iss(line);
                for(string s; iss >> s; )
                    correctAnswer.insert(stoi(s));
            }
        }
        inFile.close();
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
            for (auto & k : choice){
                outFile << k << " ";
            }
            //outFile << *choice.begin() << " " << *choice.end() << choice.;
            i++;
        }
        outFile.close();
    }
}

void PairChoiceAnswer::construct() {
    WINDOW * inputWin = newwin((screenHeight - 5) / 2, screenWidth - 60, 5 + ((screenHeight - 5) / 2), 60); // fce newwin vytvori okno
    bool autoEv = autoEval(inputWin, "");

    if (autoEv){
        mvwprintw(inputWin, 4, 4, "Enter paired number of correct choices (e.g. '2 + 3, 4 + 6, 1 + 5' -- separated by comma, paired with plus and in any order):");
        mvwprintw(inputWin, 5, 2, "> ");
        curs_set(1);
        wrefresh(inputWin);
        char tmp[100];
        echo();
        wgetstr(inputWin, tmp);
        noecho();
        curs_set(0);
        preprocess(string(tmp));
    }
}

void PairChoiceAnswer::preprocess(string answer) {
    bool digit = true, plus = false, comma = false, second = false;
    set <int> pair;
    string number;

    answer.erase(remove_if(answer.begin(), answer.end(), ::isspace), answer.end());

    for (auto & ch : answer ){
        if (isdigit(ch) && digit){
            number += ch;
            if (second)
                comma = true;
            else
                plus = true;
            continue;
        }
        if (ch == '+' && plus){
            pair.insert(stoi(number));
            number = "";
            second = true;
            plus = false;
            continue;
        }
        if (ch == ',' && comma){
            pair.insert(stoi(number));
            number = "";
            correctAnswer.insert(pair);
            pair.clear();
            comma = false;
            second = false;
            continue;
        }
        break;
    }
    pair.insert(stoi(number));
    number = "";
    correctAnswer.insert(pair);
    pair.clear();
}

PairChoiceAnswer::PairChoiceAnswer(string answerId) {
    getmaxyx(stdscr,screenHeight, screenWidth);
    id = answerId;

    ifstream inFile(ANSWER_FILE_PATH + answerId);
    string line;

    if (inFile.is_open()){
        for (int i = 0; getline(inFile, line); i++){
            if (i == 0) {
                if (line != "pchA")
                    throw "Incompatible file type: expected 'pchA'";
            }
            else if (i == 1){
                istringstream iss(line);
                set<int> pair;
                for(string s; iss >> s; ){
                    pair.insert(stoi(s));
                    if (pair.size() == 2){
                        correctAnswer.insert(pair);
                        pair.clear();
                    }
                }
            }
        }
        inFile.close();
    }
}
