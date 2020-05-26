//
// Created by tom on 19.05.20.
//

#ifndef QUIZ_ANSWERSHEET_H
#define QUIZ_ANSWERSHEET_H

#include <string>

#include "Quiz.h"

using namespace std;

class AnswerSheet {
private:
    string author;
    string id;
    Quiz quiz;
    vector<vector<shared_ptr<Answer> > > answers;
    vector<vector<int> > score;
    vector<int> numOfQuestions;
    bool evaluated = false;
public:
    AnswerSheet (Quiz q);
    AnswerSheet (Quiz q, string id);
    void renderInput (int sheetIndex, int answerIndex);
    void renderEvaluation (int sheetIndex, int answerIndex);
    void save ();
    string print (bool printQuestions);
    //tuple < vector<string>, vector< vector<int> > > getPrintedSheets (bool printQuestion, bool printAnswer);
    void setEvaluated (bool setting);

    void setAuthor(const string &author);

    static vector<string> preview (const string & id);

    string ANSWERSHEET_FILE_PATH = "files/answerSheets/";
};

#endif //QUIZ_ANSWERSHEET_H
