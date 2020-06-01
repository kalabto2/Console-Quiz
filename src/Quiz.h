//
// Created by tom on 18.04.20.
//

#ifndef QUIZ_QUIZ_H
#define QUIZ_QUIZ_H

#include <vector>
#include "Sheet.h"

using namespace std;

/** Represents quiz. Manages data about quiz. */
class Quiz {
public:
    /** Creates new quiz - sets ID according to time of creation */
    Quiz ();

    /** Loads quiz from file and creates an object.
     * @param filePath Relative filepath to file
     * @throw string exception, if file is not compatible */
    Quiz (const string& filePath);

    /** Copies and adds sheet
     @param sh Sheet to be added */
    void addSheet (const Sheet& sh);

    /** Saves object to file. Name is an id. */
    void save ();

    /** Returns name and file type of quiz
     * @param filePath filepath to quiz file
     * @return first 2 lines of quiz file */
    static vector<string> preview (const string& filePath);

    /** Prints quiz according to parameters.
     * @param printQuestion when true, prints every question.
     * @param printAnswer when true, prints also correct answer to question (if there is any).
     * @param printSpaceAnswer when true, prints space for filling under each question.
     * @return printed quiz */
    string print (bool printQuestion = true, bool printAnswer = true, bool printSpaceAnswer = true);

    /** Gets printed sheets divided by sheets and number of lines, where questions starts.
     * @param printQuestion when true, prints every question.
     * @param printAnswer when true, prints also correct answer to question (if there is any).
     * @param printSpaceAnswer when true, prints space for filling under each question.
     * @return printed sheets divided by sheets and number of lines, where questions starts. */
    tuple < vector<string>, vector< vector<int> > > getPrintedSheets (bool printQuestion = true, bool printAnswer = false, bool printSpaceAnswer = false);

    /** @return name of object */
    string getName ();

    /** @return id of object. */
    string getId ();

    /** Sets variable name
     * @param name to be setted */
    void setName (const string & name);

    /*void renderInput (int sheetIndex, int answerIndex);
    vector< vector<string> > getPrintSheets (bool printQuestion = true, bool printAnswer = false, bool PrintSpaceAnswer = false);
    vector<int> getNumberOfQuestions ();*/
protected:
    /** Holds sheets of quiz */
    vector<Sheet> sheets;
    /** Holds id of quiz created from creating time */
    string id;
    /** Holds name of quiz. */
    string name;
    /** file path to storage of quizzes files. */
    string QUIZ_FILE_PATH = "files/quizzes/";

    friend class AnswerSheet;
};

#endif //QUIZ_QUIZ_H
