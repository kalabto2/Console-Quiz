//
// Created by tom on 18.04.20.
//

#ifndef QUIZ_QUESTION_H
#define QUIZ_QUESTION_H

#include <string>
#include <utility>
#include <vector>
#include <ncurses.h>

using namespace std;

class Question {
public:
    Question();
    virtual void save();
    virtual void construct();
    virtual void renderAnswers(WINDOW * window);
protected:
    int screenHeight, screenWidth;
    string id;

    const string QUESTION_FILE_PATH = "files/questions/";
};


/* ----------------------------------------------------- */


class TextQuestion : public Question {
public:
    TextQuestion(string question);
    TextQuestion();
    void setQuestion(string question);
    void construct() override;
    void save() override;
    void renderAnswers(WINDOW * window) override ;
protected:
    string question;

};


/* ----------------------------------------------------- */


class ChoiceQuestion : public Question {
public:
    ChoiceQuestion ();
    void construct () override;
    void save() override;
    void renderAnswers(WINDOW * window) override;
protected:
    string question;
    vector<string> choices;
};



#endif //QUIZ_QUESTION_H
