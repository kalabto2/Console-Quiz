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
    void addQuestion (shared_ptr<Question> question);
    void addAnswer (shared_ptr<Answer> answer);
    void createSheet ();
protected:
    int id;
    vector<shared_ptr<Question> > questions;
    vector<shared_ptr<Answer> >     answers;
    int screenWidth, screenHeight;

    void choosePanel ();

    const string SHEET_FILE_PATH = "src/sheets/";
};

#endif //QUIZ_SHEET_H
