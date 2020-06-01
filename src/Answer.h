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

/** Represents answer, holds common data. */
class Answer {
public:
    /** Creates empty answer - new id */
    Answer ();

    /** Saves answer to file. If file already exists, adds unique number to id. */
    virtual void save ();

    /** Pure virtual method. Constructs Answer. */
    virtual void construct (bool creatingMode = true);

    /** Pure virtual method. Prints decorated answer according to @param printCorrectAnswer
     * @return answer */
    virtual string print (bool printCorrectAnswer = true);

    /** Pure virtual method. Returns true, if this answer is equal to @param a . */
    virtual bool equal (shared_ptr<Answer> & a);

    /** Destructor to base class. */
    virtual ~Answer();

    /** @param answerId id of answer-file.
     * @return subclass according to file type.
     * @throw string exception, if loaded file is incompatible */
    static shared_ptr<Answer> getAnswer (const string& answerId);

    /** @return Id of answer*/
    string getId ();

protected:
    /** holds id of answer */
    string id;
    /** holds height dimension of screen */
    int screenHeight;
    /** holds width dimension of screen */
    int screenWidth;

    /** relative path to answer-files */
    const string ANSWER_FILE_PATH = "files/answers/";

    /** Renders and handles auto-evaluation question to window.
     * @param win Window, where question should be printed.
     * @param info additional text info to window.
     * @return true, if auto evaluation is needed. */
    static bool autoEval (WINDOW * win, string info);

    friend class Sheet;
    friend class AnswerSheet;
};


/* ------------------------------------------------------------------------------------------------------------------ */


/** Represents subtype of answer - answer with text field. */
class TextAnswer : public Answer {
public:
    /** Creates new TextAnswer */
    TextAnswer ();

    /** Loads TextAnswer from file.
     * @param answerId Id of answer.
     * @throw string exception, if loaded file is incompatible */
    TextAnswer (const string& answerId);

    /** Renders window for creating answer, handles input
     * @param creatingMode when true, window renders in 'creating' mode. Else renders in 'completing' mode. */
    void construct (bool creatingMode = true) override;

    /** Prints answer.
     * @param printCorrectAnswer when true, 'correctAnswer' is printed. Else space for answer is printed.
     * @return printed and decorated TextAnswer. */
    string print(bool printCorrectAnswer = true) override ;

    /** Saves answer to file. */
    void save () override;

    /** Determines, if this object and object 'a' are equal in subclasses variables.
     * @param a another object to compare.
     * @return true, when equation is true ... */
    bool equal (shared_ptr<Answer> & a) override ;

    /** Destructor to derived class. */
    ~TextAnswer() override ;

protected:
    /** Represents answer of STUDENT or sample answer of TEACHER.
     * If is sample answer, empty value means no auto evaluation. */
    string correctAnswer = "";

    friend class Sheet;
    friend class AnswerSheet;
};


/* ------------------------------------------------------------------------------------------------------------------ */


/** Represents subtype of answer - answer with text field for value. */
class ValueAnswer : public Answer {
public:
    /** Creates new ValueAnswer */
    ValueAnswer ();

    /** Loads ValueAnswer from file.
     * @param answerId Id of answer.
     * @throw string exception, if loaded file is incompatible */
    ValueAnswer (const string& answerId);

    /** Renders window for creating answer, handles input
     * @param creatingMode when true, window renders in 'creating' mode. Else renders in 'completing' mode. */
    void construct (bool creatingMode = true) override;

    /** Prints answer.
     * @param printCorrectAnswer when true, 'correctAnswer' is printed. Else space for answer is printed.
     * @return printed and decorated TextAnswer. */
    string print (bool printCorrectAnswer = true) override ;

    /** Saves answer to file. */
    void save () override;

    /** Determines, if this object and object 'a' are equal in subclasses variables.
     * @param a another object to compare.
     * @return true, when equation is true ... */
    bool equal (shared_ptr<Answer> & a) override ;

    /** Destructor to derived class. */
    ~ValueAnswer() override ;

protected:
    /** Represents answer of STUDENT or sample answer of TEACHER.
     * If is sample answer, empty value means no auto evaluation. */
    string correctAnswer = "";

    friend class Sheet;
    friend class AnswerSheet;
};


/* ------------------------------------------------------------------------------------------------------------------ */


/** Represents subtype of answer - answer with text field for one number from choice. */
class SingleChoiceAnswer : public Answer {
public:
    /** Creates new SingleChoiceAnswer */
    SingleChoiceAnswer ();

    /** Loads SingleChoiceAnswer from file.
     * @param answerId Id of answer.
     * @throw string exception, if loaded file is incompatible. */
    SingleChoiceAnswer (const string& answerId);

    /** Renders window for creating answer, handles input
     * @param creatingMode when true, window renders in 'creating' mode. Else renders in 'completing' mode. */
    void construct (bool creatingMode = true) override;

    /** Prints answer.
     * @param printCorrectAnswer when true, 'correctAnswer' is printed. Else space for answer is printed.
     * @return printed and decorated TextAnswer. */
    string print(bool printCorrectAnswer = true) override ;

    /** Saves answer to file. */
    void save () override;

    /** Transforms 'answer' to integer and saves it. If it cannot be done, saves as 0
     * @param answer answer to preprocess. */
    void preprocess (const string& answer);

    /** Determines, if this object and object 'a' are equal in subclasses variables.
     * @param a another object to compare.
     * @return true, when equation is true ... */
    bool equal (shared_ptr<Answer> & a) override ;

    /** Destructor to derived class. */
    ~SingleChoiceAnswer() override ;

protected:
    /** Represents answer of STUDENT or sample answer of TEACHER.
     * If is sample answer, empty value means no auto evaluation. */
    int correctAnswer = 0;

    friend class Sheet;
    friend class AnswerSheet;
};


/* ------------------------------------------------------------------------------------------------------------------ */


/** Represents subtype of answer - answer with text field for several number from choice. */
class MultipleChoiceAnswer : public Answer {
public:
    /** Creates new MultipleChoiceAnswer */
    MultipleChoiceAnswer ();

    /** Loads MultipleChoiceAnswer from file.
     * @param answerId Id of answer.
     * @throw string exception, if loaded file is incompatible. */
    MultipleChoiceAnswer (const string& answerId);

    /** Renders window for creating answer, handles input
     * @param creatingMode when true, window renders in 'creating' mode. Else renders in 'completing' mode. */
    void construct (bool creatingMode = true) override;

    /** Prints answer.
     * @param printCorrectAnswer when true, 'correctAnswer' is printed. Else space for answer is printed.
     * @return printed and decorated TextAnswer. */
    string print(bool printCorrectAnswer = true) override ;

    /** Saves answer to file. */
    void save () override;

    /** Transforms answer into set of integers and saves it. If it cannot be done, saves as empty set
     * @param answer answer to preprocess*/
    void preprocess (const string& answer);

    /** Determines, if this object and object 'a' are equal in subclasses variables.
     * @param a another object to compare.
     * @return true, when equation is true ... */
    bool equal (shared_ptr<Answer> & a) override ;

    /** Destructor to derived class. */
    ~MultipleChoiceAnswer() override ;

protected:
    /** Represents answer of STUDENT or sample answer of TEACHER.
     * If is sample answer, empty value means no auto evaluation. */
    set<int> correctAnswer;

    friend class Sheet;
    friend class AnswerSheet;

};


/* ------------------------------------------------------------------------------------------------------------------ */


/** Represents subtype of answer - answer with text field for paired choices. */
class PairChoiceAnswer : public Answer {
public:
    /** Creates new PairChoiceAnswer */
    PairChoiceAnswer ();

    /** Loads PairChoiceAnswer from file.
     * @param answerId Id of answer.
     * @throw string exception, if loaded file is incompatible. */
    PairChoiceAnswer (const string& answerId);

    /** Renders window for creating answer, handles input
     * @param creatingMode when true, window renders in 'creating' mode. Else renders in 'completing' mode. */
    void construct (bool creatingMode = true) override;

    /** Prints answer.
     * @param printCorrectAnswer when true, 'correctAnswer' is printed. Else space for answer is printed.
     * @return printed and decorated TextAnswer. */
    string print(bool printCorrectAnswer = true) override ;

    /** Saves answer to file. */
    void save () override;

    /** Transforms 'answer' into set of sets of integers and saves it. If it cannot be done, saves as empty set.
     * @param answer answer to preprocess. */
    void preprocess (string answer);

    /** Determines, if this object and object 'a' are equal in subclasses variables.
     * @param a another object to compare.
     * @return true, when equation is true ... */
    bool equal (shared_ptr<Answer> & a) override ;

    /** Destructor to derived class. */
    ~PairChoiceAnswer() override ;

protected:
    /** Represents answer of STUDENT or sample answer of TEACHER.
     * If is sample answer, empty value means no auto evaluation. */
    set< set<int> > correctAnswer;

    friend class Sheet;
    friend class AnswerSheet;
};


#endif //QUIZ_ANSWER_H
