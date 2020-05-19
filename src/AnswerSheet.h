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
    vector<shared_ptr<Answer> > answers;
    vector<int> score;

public:
    AnswerSheet ();
};

#endif //QUIZ_ANSWERSHEET_H
