//
// Created by tom on 18.04.20.
//

#ifndef QUIZ_SHEET_H
#define QUIZ_SHEET_H

#include "Question.h"
#include "Answer.h"

#include <vector>
#include <memory>

using namespace std;


/** Represents Sheet of quiz containing several questions and answers. Manages creation of them too. */
class Sheet {
public:
    /** Creates blank sheet with new unique id. */
    Sheet ();

    /** Loads sheet from file, constructs object.
     * @param id relative path to file containing sheet.
     * @throw string exception, if file is incompatible. */
    Sheet (const string& id);

    /** Adds question to sheet.
     * @param question object representating question. */
    void addQuestion (const shared_ptr<Question>& question);

    /** Adds answer to sheet.
     * @param answer object representating answer. */
    void addAnswer (const shared_ptr<Answer>& answer);

    /** Manages creation of new sheet. */
    void createSheet ();

    /** saves Sheet to file. */
    void save();

    /** Prints and decorates Sheet according to parameters.
     * @param printQuestion when true, questions are also printed into sheet.
     * @param printAnswer when true, answers are also printed into sheet.
     * @param printSpaceAnswer when true, space for answers are printed into sheet.
     * @return decorated sheet. */
    string print (bool printQuestion = true, bool printAnswer = true, bool printSpaceAnswer = true);

    /** Gets id.
     * @return id of file. */
    string getId();

    /** Prints and decorates Sheet according to parameters.
     * @param printQuestion when true, questions are also printed into sheet.
     * @param printAnswer when true, answers are also printed into sheet.
     * @param printSpaceAnswer when true, space for answers are printed into sheet.
     * @return decorated sheet divided by pair of questions + answers, so it can be handled separately. */
    vector<string> getPrintedQA (bool printQuestion = true, bool printAnswer = true, bool printSpaceAnswer = true);

    /** Returns length of pairs of questions and answers from method 'getPrintedQA'
     * @param printQuestion when true, questions are also printed into sheet.
     * @param printAnswer when true, answers are also printed into sheet.
     * @param printSpaceAnswer when true, space for answers are printed into sheet.
     * @return decorated sheet divided by sheets, co it can be handled separately. */
    vector<int> getLines (bool printQuestion = true, bool printAnswer = true, bool printSpaceAnswer = true);

    /** Relative path to directory, where sheets are saved. */
    static const string SHEET_FILE_PATH;

protected:
    /** Represents user input when creating sheet. */
    enum SHEET_OPTION {FINISH_SHEET, ADD_QUESTION};

    /** unique id of sheet. */
    string id;
    /** Holds number of rows of screen. */
    int screenHeight;
    /** Holds number of columns of screen. */
    int screenWidth;
    /** represents questions. Each question is paired with answer on same index. */
    vector<shared_ptr<Question> > questions;
    /** represents answers. Each answer is paired with question on same index. */
    vector<shared_ptr<Answer> >     answers;

    /** Renders, manages creating of questions and answers on one sheet.
     * @return FINISH_SHEET, if user wants finish sheet. Else user wants add another question. */
    SHEET_OPTION choosePanel ();

    /** Holds Control question. If no Control question is set, variable is empty. Therefor Control question cannot be empty. */
    string controlQuestion;
    /** Holds answer to Control question. If no Control question is set, variable is empty. Therefor Control answer cannot be empty. */
    string controlAnswer;

public:
    /** Sets Control question to sheet.
     * @param controlQuestion Holds content of Control question. */
    void setControlQuestion(const string &controlQuestion);

    /** Sets Answer to Control question to sheet.
     * @param controlAnswer Holds content of Control answer. */
    void setControlAnswer(const string &controlAnswer);

    /** @return variable 'controlQuestion' */
    const string &getControlQuestion() const;

    /** @return variable 'controlAnswer' */
    const string &getControlAnswer() const;

    friend class Quiz;
    friend class AnswerSheet;
};


#endif //QUIZ_SHEET_H
