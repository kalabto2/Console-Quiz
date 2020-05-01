//
// Created by tom on 18.04.20.
//

#ifndef QUIZ_ANSWER_H
#define QUIZ_ANSWER_H

#include <string>
#include <set>
#include <utility>

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

protected:
    int correctAnswer;
};


/* ------------------------------------------------------------------------------------------------------------------ */


class MultipleChoiceAnswer : public Answer {
public:
    MultipleChoiceAnswer ();
    void save () override;
    void construct () override;

protected:
    set<int> correctAnswer;

};


/* ------------------------------------------------------------------------------------------------------------------ */


class PairChoiceAnswer : public Answer {
public:
    PairChoiceAnswer ();
    void save () override;
    void construct () override;

protected:
    set< pair<int, int> > correctAnswer;
};


#endif //QUIZ_ANSWER_H
