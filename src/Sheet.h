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

class Sheet {
public:
    Sheet ();
    Sheet (string id);
    void addQuestion (const shared_ptr<Question>& question);
    void addAnswer (shared_ptr<Answer> answer);
    void createSheet ();
    void save();
    string getId();
    string print (bool printQuestion = true, bool printAnswer = true, bool printSpaceAnswer = true);
protected:
    enum SHEET_OPTION {FINISH_SHEET, ADD_QUESTION};
    const string SHEET_FILE_PATH = "files/sheets/";

    string id;
    int screenWidth, screenHeight;
    vector<shared_ptr<Question> > questions;
    vector<shared_ptr<Answer> >     answers;

    SHEET_OPTION choosePanel ();
};

#endif //QUIZ_SHEET_H
