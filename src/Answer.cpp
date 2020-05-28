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
#include <sys/stat.h>
#include <filesystem>


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
    if (std::filesystem::exists(ANSWER_FILE_PATH + id) && id.size() == 17)
        id += "-1";
    else if(std::filesystem::exists(ANSWER_FILE_PATH + id) && id.size() > 17){
        string base = id.substr(0, 17);
        string postfix = id.substr(18, id.size() - base.size() - 1);
        int x = stoi(postfix) + 1;
        postfix = to_string(x);
        id = base + "-" + postfix;
    }
    else return;
    Answer::save();
}

void Answer::construct(bool creatingMode) {

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

string Answer::print(bool printCorrectAnswer) {
    return "Error :: vypsala se supperclass - data byla ztracena";
}

bool Answer::equal(shared_ptr<Answer> &a) {
    return false;
}


/* ------------------------------------------------------------------------------------------------------------------ */


TextAnswer::TextAnswer() : Answer() {}

void TextAnswer::save() {
    Answer::save();
    ofstream outFile(ANSWER_FILE_PATH + id);
    if (outFile.is_open())
    {
        outFile << "txtA" << endl;
        outFile << correctAnswer;
        outFile.close();
    }
}

void TextAnswer::construct(bool creatingMode) {
    int winStartY = (creatingMode ? (screenHeight - 5) / 2 : (screenHeight - 15));
    int winStartX = (creatingMode ? screenWidth - 60 : 0);
    int winHeight = (creatingMode ? 5 + ((screenHeight - 5) / 2) : 15);
    int winWidth  = (creatingMode ? 5 + 60 : screenWidth);
    WINDOW * inputWin = newwin(winHeight, winWidth, winStartY, winStartX);
    box(inputWin, 0, 0);
    bool autoEv = (creatingMode ? autoEval(inputWin, "") : false);

    if (autoEv || !creatingMode){
        mvwprintw(inputWin, 2, 4, "TEXT ANSWER");
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
    if (!creatingMode) {
        wclear(inputWin);
        wrefresh(inputWin);
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

string TextAnswer::print(bool printCorrectAnswer) {
    string res;

    if (printCorrectAnswer){
        res += correctAnswer;
    }
    else {
        res +=
        "> ______________________________________________________________________________________________________________\n"
        "________________________________________________________________________________________________________________\n"
        "________________________________________________________________________________________________________________\n"
        "________________________________________________________________________________________________________________\n";
    }
    return res + "\n";
}

bool TextAnswer::equal(shared_ptr<Answer> &a) {
    return dynamic_cast<TextAnswer*>(a.get())->correctAnswer == correctAnswer;
}


/* ------------------------------------------------------------------------------------------------------------------ */


ValueAnswer::ValueAnswer() : Answer() {}

void ValueAnswer::save() {
    Answer::save();
    ofstream outFile(ANSWER_FILE_PATH + id);
    if (outFile.is_open())
    {
        outFile << "valA" << endl;
        outFile << correctAnswer;
        outFile.close();
    }
}

void ValueAnswer::construct(bool creatingMode) {
    int winStartY = (creatingMode ? (screenHeight - 5) / 2 : (screenHeight - 15));
    int winStartX = (creatingMode ? screenWidth - 60 : 0);
    int winHeight = (creatingMode ? 5 + ((screenHeight - 5) / 2) : 15);
    int winWidth  = (creatingMode ? 5 + 60 : screenWidth);
    WINDOW * inputWin = newwin(winHeight, winWidth, winStartY, winStartX);
    box(inputWin, 0, 0);
    bool autoEv = (creatingMode ? autoEval(inputWin, "") : false);

    if (autoEv || !creatingMode){
        mvwprintw(inputWin, 2, 4, "VALUE ANSWER");
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
    if (!creatingMode) {
        wclear(inputWin);
        wrefresh(inputWin);
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

string ValueAnswer::print(bool printCorrectAnswer) {
    string res;

    if (printCorrectAnswer){
        res += correctAnswer;
    }
    else {
        res +=
                "> ______________________________________________________________________________________________________________\n";
    }
    return res + "\n";
}

bool ValueAnswer::equal(shared_ptr<Answer> &a) {
    return dynamic_cast<ValueAnswer*>(a.get())->correctAnswer == correctAnswer;
}


/* ------------------------------------------------------------------------------------------------------------------ */


SingleChoiceAnswer::SingleChoiceAnswer() : Answer(), correctAnswer(0) {}

void SingleChoiceAnswer::save() {
    Answer::save();
    ofstream outFile(ANSWER_FILE_PATH + id);
    if (outFile.is_open())
    {
        outFile << "schA" << endl;
        outFile << correctAnswer;
        outFile.close();
    }
}

void SingleChoiceAnswer::construct(bool creatingMode) {
    int winStartY = (creatingMode ? (screenHeight - 5) / 2 : (screenHeight - 15));
    int winStartX = (creatingMode ? screenWidth - 60 : 0);
    int winHeight = (creatingMode ? 5 + ((screenHeight - 5) / 2) : 15);
    int winWidth  = (creatingMode ? 5 + 60 : screenWidth);
    WINDOW * inputWin = newwin(winHeight, winWidth, winStartY, winStartX);
    box(inputWin, 0, 0);
    bool autoEv = (creatingMode ? autoEval(inputWin, "") : false);

    if (autoEv || !creatingMode){
        mvwprintw(inputWin, 2, 4, "SINGLE CHOICE ANSWER");
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
    if (!creatingMode) {
        wclear(inputWin);
        wrefresh(inputWin);
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

string SingleChoiceAnswer::print(bool printCorrectAnswer) {
    string res;

    if (printCorrectAnswer){
        res += to_string(correctAnswer);
    }
    else {
        res +=
                "> ______________________________________________________________________________________________________________\n";
    }
    return res + "\n";
}

bool SingleChoiceAnswer::equal(shared_ptr<Answer> &a) {
    return dynamic_cast<SingleChoiceAnswer*>(a.get())->correctAnswer == correctAnswer;
}


/* ------------------------------------------------------------------------------------------------------------------ */


MultipleChoiceAnswer::MultipleChoiceAnswer() : Answer() {}

void MultipleChoiceAnswer::save() {
    Answer::save();
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

void MultipleChoiceAnswer::construct(bool creatingMode) {
    int winStartY = (creatingMode ? (screenHeight - 5) / 2 : (screenHeight - 15));
    int winStartX = (creatingMode ? screenWidth - 60 : 0);
    int winHeight = (creatingMode ? 5 + ((screenHeight - 5) / 2) : 15);
    int winWidth  = (creatingMode ? 5 + 60 : screenWidth);
    WINDOW * inputWin = newwin(winHeight, winWidth, winStartY, winStartX);
    box(inputWin, 0, 0);
    bool autoEv = (creatingMode ? autoEval(inputWin, "") : false);

    if (autoEv || !creatingMode){
        mvwprintw(inputWin, 2, 4, "MULTIPLE CHOICE ANSWER");
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
    if (!creatingMode) {
        wclear(inputWin);
        wrefresh(inputWin);
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

string MultipleChoiceAnswer::print(bool printCorrectAnswer) {
    string res;

    if (printCorrectAnswer){
        for (auto & i : correctAnswer){
            res += (i == *(correctAnswer.rbegin()) ? to_string(i) : to_string(i) + ", ");
        }
    }
    else {
        res +=
                "> ______________________________________________________________________________________________________________\n";
    }
    return res + "\n";
}

bool MultipleChoiceAnswer::equal(shared_ptr<Answer> &a) {
    return dynamic_cast<MultipleChoiceAnswer*>(a.get())->correctAnswer == correctAnswer;
}


/* ------------------------------------------------------------------------------------------------------------------ */


PairChoiceAnswer::PairChoiceAnswer() : Answer() {}

void PairChoiceAnswer::save() {
    Answer::save();
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

void PairChoiceAnswer::construct(bool creatingMode) {
    int winStartY = (creatingMode ? (screenHeight - 5) / 2 : (screenHeight - 15));
    int winStartX = (creatingMode ? screenWidth - 60 : 0);
    int winHeight = (creatingMode ? 5 + ((screenHeight - 5) / 2) : 15);
    int winWidth  = (creatingMode ? 5 + 60 : screenWidth);
    WINDOW * inputWin = newwin(winHeight, winWidth, winStartY, winStartX);
    box(inputWin, 0, 0);
    bool autoEv = (creatingMode ? autoEval(inputWin, "") : false);

    if (autoEv || !creatingMode){
        mvwprintw(inputWin, 2, 4, "PAIR CHOICE ANSWER");
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
    if (!creatingMode) {
        wclear(inputWin);
        wrefresh(inputWin);
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

string PairChoiceAnswer::print(bool printCorrectAnswer) {
    string res;

    if (printCorrectAnswer){
        for (auto & i : correctAnswer){
            for (auto & j : i){
                res += (j == *(i.rbegin()) ? to_string(j) : to_string(j) + " + ");
            }
            res += (i == *correctAnswer.rbegin() ? "" : ", ");
        }
    }
    else {
        res +=
                "> ______________________________________________________________________________________________________________\n";
    }
    return res + "\n";
}

bool PairChoiceAnswer::equal(shared_ptr<Answer> &a) {
    return dynamic_cast<PairChoiceAnswer*>(a.get())->correctAnswer == correctAnswer;
}

/* ------------------------------------------------------------------------------------------------------------------ */
/*
SortingAnswer::SortingAnswer() : Answer() {}

bool SortingAnswer::equal(shared_ptr<Answer> &a) {
    return dynamic_cast<SortingAnswer*>(a.get())->correctAnswer == correctAnswer;
}

void SortingAnswer::save() {

}

void SortingAnswer::construct(bool creatingMode) {
    int winStartY = (creatingMode ? (screenHeight - 5) / 2 : (screenHeight - 15));
    int winStartX = (creatingMode ? screenWidth - 60 : 0);
    int winHeight = (creatingMode ? 5 + ((screenHeight - 5) / 2) : 15);
    int winWidth  = (creatingMode ? 5 + 60 : screenWidth);
    WINDOW * inputWin = newwin(winHeight, winWidth, winStartY, winStartX);
    box(inputWin, 0, 0);
    bool autoEv = (creatingMode ? autoEval(inputWin, "") : false);

    if (autoEv || !creatingMode){
        mvwprintw(inputWin, 2, 4, "SORTING ANSWER");
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
    if (!creatingMode) {
        wclear(inputWin);
        wrefresh(inputWin);
    }
}

void SortingAnswer::preprocess(string answer) {
    string number;
    bool comma = false;

    for (auto & ch : answer){
        if (iswspace(ch))
            continue;
        if (ch == ',' && comma){
            correctAnswer.push_back(stoi(number));
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
    correctAnswer.push_back(stoi(number));
    number = "";
}

string SortingAnswer::print(bool printCorrectAnswer) {
    string res;

    if (printCorrectAnswer){
        for (auto & i : correctAnswer){
            res += (i == *(correctAnswer.rbegin()) ? to_string(i) : to_string(i) + ", ");
        }
    }
    else {
        res +=
                "> ______________________________________________________________________________________________________________\n";
    }
    return res + "\n";
}

SortingAnswer::SortingAnswer(string answerId) {

}
*/