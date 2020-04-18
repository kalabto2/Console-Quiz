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
    Question(int id);

protected:
    int id;
};


/* ----------------------------------------------------- */


class TextQuestion : public Question {
public:
    TextQuestion(int id, string question);

protected:
    string question;
};


/* ----------------------------------------------------- */


class SingleChoiceQuestion : public Question {
public:
    SingleChoiceQuestion(int id, string question);

protected:
    string question;
};



#endif //QUIZ_QUESTION_H
