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


/** Represents Base class of question. */
class Question {
public:
    /** Creates new question - new id, and loads screen info. */
    Question();

    /** Pure virtual method. Saves object to file. */
    virtual void save();

    /** Pure virtual method. Renders construction window, handles input and sets data. */
    virtual void construct();

    /** Pure virtual method. Renders type of answer, that are compatible with this question.
     * @param window window, where types of answer are printed. */
    virtual void renderAnswers(WINDOW * window);

    /** Pure virtual method.
     * @param i index determining type of answer.
     * @return new instance of answer of type set by i. */
    virtual shared_ptr<Answer> getTypeAnswer(int i);

    /** Pure virtual method. Gets number of compatible answers.
     * @return number of compatible answers. */
    virtual int getNumOfAnsw ();

    /** Pure virtual method. Prints decorated question.
     * @return printed question. */
    virtual string print ();

    /** Destructor to Base class question. */
    virtual ~Question();

    /** Gets questions unique id.
     * @return id. */
    string getId ();

    /** Determines and gets, what questions is in file.
     * @param questionId id of file.
     * @return instance of questions.
     * @throw string exception, if file type is incompatible. */
    static shared_ptr<Question> getQuestion (const string& questionId);

protected:
    /** Variables holds height dimension of screen. */
    int screenHeight;
    /** Variables holds width dimension of screen. */
    int screenWidth;

    /** Unique id of Question. Set by current date/time. */
    string id;

    /** Path to files with Questions files. */
    static const string QUESTION_FILE_PATH;
};


/* ------------------------------------------------------------------------------------------------------------------ */


/** Derived question represents Question with text field. */
class TextQuestion : public Question {
public:
    /** Loads question of file.
     * @param questionId name of file.
     * @throw string exception, if file is incompatible. */
    TextQuestion(const string& questionId);

    /** Creates new instance of question. */
    TextQuestion();

    /** Renders construction window, handles input and sets data. */
    void construct() override;

    /** Saves object to file. */
    void save() override;

    /** Renders type of answer, that are compatible with this question.
     * @param window window, where types of answer are printed. */
    void renderAnswers(WINDOW * window) override ;

    /** Prints decorated question.
     * @return printed question. */
    string print() override;

    /** gets type of answer compatible with this question.
     * @param i index determining type of answer.
     * @return new instance of answer of type set by i. */
    shared_ptr<Answer> getTypeAnswer(int i) override ;

    /** gets type of answer compatible with this question.
     * @return number of answers compatible to this question. */
    int getNumOfAnsw () override ;

    /** Destructs object. */
    ~TextQuestion() override;
protected:
    /** Answer to question, that user writes. */
    string question;

};


/* ------------------------------------------------------------------------------------------------------------------ */


/** Derived class represents questions with several questions. */
class ChoiceQuestion : public Question {
public:
    /** Loads question of file.
     * @param questionId name of file.
     * @throw string exception, if file is incompatible. */
    ChoiceQuestion (const string& questionId);

    /** Creates new instance of question. */
    ChoiceQuestion ();

    /** Renders construction window, handles input and sets data. */
    void construct () override;

    /** Saves object to file. */
    void save() override;

    /** Renders type of answer, that are compatible with this question.
     * @param window window, where types of answer are printed. */
    void renderAnswers(WINDOW * window) override;

    /** Prints decorated question.
     * @return printed question. */
    string print() override ;

    /** gets type of answer compatible with this question.
     * @param i index determining type of answer.
     * @return new instance of answer of type set by i. */
    shared_ptr<Answer> getTypeAnswer(int i) override;

    /** gets type of answer compatible with this question.
     * @return number of answers compatible to this question. */
    int getNumOfAnsw () override ;

    /** Destructs object. */
    ~ChoiceQuestion() override;

protected:
    /** Answer to question, that user writes. */
    string question;
    /** Choices to choice question. */
    vector<string> choices;
};


/* ------------------------------------------------------------------------------------------------------------------ */


/** Derived class representating questions with choices to sort. */
class SortingQuestion : public Question {
public:
    /** Loads question of file.
     * @param questionId name of file.
     * @throw string exception, if file is incompatible. */
    SortingQuestion (const string& questionId);

    /** Creates new instance of question. */
    SortingQuestion ();

    /** Renders construction window, handles input and sets data. */
    void construct () override;

    /** Saves object to file. */
    void save() override;

    /** Renders type of answer, that are compatible with this question.
     * @param window window, where types of answer are printed. */
    void renderAnswers(WINDOW * window) override;

    /** gets type of answer compatible with this question.
     * @param i index determining type of answer.
     * @return new instance of answer of type set by i. */
    shared_ptr<Answer> getTypeAnswer(int i) override;

    /** gets type of answer compatible with this question.
     * @return number of answers compatible to this question. */
    int getNumOfAnsw () override ;

    /** Prints decorated question.
     * @return printed question. */
    string print() override ;

    /** Destructs object. */
    ~SortingQuestion() override;

protected:
    /** Answer to question, that user writes. */
    string question;
    /** Choices to sort question to be sorted. */
    vector<string> choices;
};


#endif //QUIZ_QUESTION_H