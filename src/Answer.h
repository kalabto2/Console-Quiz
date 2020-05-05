//
// Created by tom on 18.04.20.
//

#ifndef QUIZ_ANSWER_H
#define QUIZ_ANSWER_H

#include <string>
#include <set>
#include <utility>
#include <ncurses.h>

using namespace std;

class Answer {
public:
    Answer ();
    virtual void save ();
    virtual void construct ();
    string getId ();
protected:
    string id;
    int screenHeight, screenWidth;

    const string ANSWER_FILE_PATH = "files/answers/";

    bool autoEval (WINDOW * win, string info);
};


/* ------------------------------------------------------------------------------------------------------------------ */


class TextAnswer : public Answer {
public:
    TextAnswer ();
    void save () override;
    void construct () override;

protected:
    string correctAnswer = "";
};


/* ------------------------------------------------------------------------------------------------------------------ */


class ValueAnswer : public Answer {
public:
    ValueAnswer ();
    void save () override;
    void construct () override;

protected:
    string correctAnswer = "";
};


/* ------------------------------------------------------------------------------------------------------------------ */


class SingleChoiceAnswer : public Answer {
public:
    SingleChoiceAnswer ();
    void save () override;
    void construct () override;
    void preprocess (string answer);
protected:
    int correctAnswer;
};


/* ------------------------------------------------------------------------------------------------------------------ */


class MultipleChoiceAnswer : public Answer {
public:
    MultipleChoiceAnswer ();
    void save () override;
    void construct () override;
    void preprocess (string answer);
protected:
    set<int> correctAnswer;

};


/* ------------------------------------------------------------------------------------------------------------------ */


class PairChoiceAnswer : public Answer {
public:
    PairChoiceAnswer ();
    void save () override;
    void construct () override;
    void preprocess (string answer);
protected:
    set< set<int> > correctAnswer;
};


#endif //QUIZ_ANSWER_H
