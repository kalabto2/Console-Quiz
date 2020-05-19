//
// Created by tom on 18.04.20.
//

#ifndef QUIZ_QUESTION_H
#define QUIZ_QUESTION_H

#include "Answer.h"

#include <string>
#include <utility>
#include <vector>
#include <ncurses.h>
#include <memory>


using namespace std;

class Question {
public:
    Question();
    virtual void save();
    virtual void construct();
    virtual void renderAnswers(WINDOW * window);
    virtual shared_ptr<Answer> getTypeAnswer(int i);
    string getId ();
    virtual int getNumOfAnsw ();
    static shared_ptr<Question> getQuestion (string questionId);
    virtual string print ();
protected:
    int screenHeight, screenWidth;
    string id;

    const string QUESTION_FILE_PATH = "files/questions/";
};


/* ------------------------------------------------------------------------------------------------------------------ */


class TextQuestion : public Question {
public:
    TextQuestion(const string& questionId);
    TextQuestion();
    void setQuestion(string question);
    void construct() override;
    void save() override;
    void renderAnswers(WINDOW * window) override ;
    shared_ptr<Answer> getTypeAnswer(int i) override ;
    int getNumOfAnsw () override ;
    string print() override;
protected:
    string question;

};


/* ------------------------------------------------------------------------------------------------------------------ */


class ChoiceQuestion : public Question {
public:
    ChoiceQuestion (string questionId);
    ChoiceQuestion ();
    void construct () override;
    void save() override;
    void renderAnswers(WINDOW * window) override;
    shared_ptr<Answer> getTypeAnswer(int i) override;
    int getNumOfAnsw () override ;
    string print() override ;
protected:
    string question;
    vector<string> choices;
};



#endif //QUIZ_QUESTION_H
