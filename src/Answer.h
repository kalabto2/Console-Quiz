//
// Created by tom on 18.04.20.
//

#ifndef QUIZ_ANSWER_H
#define QUIZ_ANSWER_H

#include <string>
#include <set>
#include <utility>
#include <ncurses.h>
#include <memory>

using namespace std;

class Answer {
public:
    Answer ();
    virtual void save ();
    virtual void construct ();
    virtual string print (bool printCorrectAnswer = true);
    string getId ();
    static shared_ptr<Answer> getAnswer (string answerId);
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
    TextAnswer (string answerId);
    void save () override;
    void construct () override;
    string print(bool printCorrectAnswer = true) override ;

protected:
    string correctAnswer = "";
};


/* ------------------------------------------------------------------------------------------------------------------ */


class ValueAnswer : public Answer {
public:
    ValueAnswer ();
    ValueAnswer (string answerId);
    void save () override;
    void construct () override;
    string print (bool printCorrectAnswer = true) override ;

protected:
    string correctAnswer = "";
};


/* ------------------------------------------------------------------------------------------------------------------ */


class SingleChoiceAnswer : public Answer {
public:
    SingleChoiceAnswer ();
    SingleChoiceAnswer (string answerId);
    void save () override;
    void construct () override;
    void preprocess (string answer);
    string print(bool printCorrectAnswer = true) override ;
protected:
    int correctAnswer;
};


/* ------------------------------------------------------------------------------------------------------------------ */


class MultipleChoiceAnswer : public Answer {
public:
    MultipleChoiceAnswer ();
    MultipleChoiceAnswer (string answerId);
    void save () override;
    void construct () override;
    void preprocess (string answer);
    string print(bool printCorrectAnswer = true) override ;
protected:
    set<int> correctAnswer;

};


/* ------------------------------------------------------------------------------------------------------------------ */


class PairChoiceAnswer : public Answer {
public:
    PairChoiceAnswer ();
    PairChoiceAnswer (string answerId);
    void save () override;
    void construct () override;
    void preprocess (string answer);
    string print(bool printCorrectAnswer = true) override ;
protected:
    set< set<int> > correctAnswer;
};


#endif //QUIZ_ANSWER_H
