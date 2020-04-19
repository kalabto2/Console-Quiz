//
// Created by tom on 18.04.20.
//

#ifndef QUIZ_QUESTION_H
#define QUIZ_QUESTION_H

#include <string>
#include <utility>

using namespace std;

class Question {
public:
    //Question(int id);
    Question();
    virtual void save();
    virtual void construct();
protected:
    int id, screenHeight, screenWidth;

    const string QUESTION_FILE_PATH = "files/questions/";
};


/* ----------------------------------------------------- */


class TextQuestion : public Question {
public:
    //TextQuestion(int id, string question);
    TextQuestion(string question);
    TextQuestion();
    void setQuestion(string question);
    void construct() override;
    void save();
protected:
    string question;

};


/* ----------------------------------------------------- */


class SingleChoiceQuestion : public Question {
public:
    //SingleChoiceQuestion(int id, string question);

protected:
    string question;
};



#endif //QUIZ_QUESTION_H
