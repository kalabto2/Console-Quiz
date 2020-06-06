//
// Created by tom on 19.05.20.
//

#ifndef QUIZ_ANSWERSHEET_H
#define QUIZ_ANSWERSHEET_H

#include <string>

#include "Quiz.h"

using namespace std;

/** Represents answers of student to certain quiz */
class AnswerSheet {
private:
    /** name of answerSheet author. */
    string author;
    /** id of answerSheet. */
    string id;
    /** represents quiz, to which is answerSheet paired. */
    Quiz quiz;
    /** particular students answers to quiz. */
    vector<vector<shared_ptr<Answer> > > answers;
    /** Score of student on particular answers divided by sheets. */
    vector<vector<int> > score;
    /** state if answerSheet was manually evaluated. */
    bool evaluated = false;

public:
    /** Creates new blank answerSheet for quiz.
     * @param q represents quiz for answerSheet. */
    AnswerSheet (Quiz q);

    /** Loads answerSheet from file filePath and assign it to q.
     * @param q represents quiz.
     * @param filePath represents path to file with answerSheet.
     * @throw string exception, when file is not compatible. */
    AnswerSheet (Quiz q, const string& filePath);

    /** Renders, handles input and sets answer of student to question.
     * @param sheetIndex Index of sheet.
     * @param answerIndex Index of answer. */
    void renderInput (int sheetIndex, int answerIndex);

    /** Renders, handles input and sets score of answer in this answerSheet.
     * @param sheetIndex Index of sheet.
     * @param answerIndex Index of answer. */
    void renderEvaluation (int sheetIndex, int answerIndex);

    /** Saves object into file. */
    void save ();

    /** Prints decorated answerSheet according to parameters.
     * @param printQuestions - when true, questions will be printed.
     * @return printed answerSheet. */
    string print (bool printQuestions);

    /** Sets @param setting as evaluated state. */
    void setEvaluated (bool setting);

    /** Sets @param author as author. */
    void setAuthor(const string &author);

    /** holds path to directory with answerSheets files. */
    static const string ANSWERSHEET_FILE_PATH;

    /** Gets info about answerSheet.
     * @param filePath path to answerSheet file.
     * @return fileType, authors name and evaluation state */
    static vector<string> preview (const string & filePath);
};

#endif //QUIZ_ANSWERSHEET_H
