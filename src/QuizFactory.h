//
// Created by tom on 18.04.20.
//

#ifndef QUIZ_QUIZFACTORY_H
#define QUIZ_QUIZFACTORY_H

#include "Quiz.h"

class  QuizFactory {
public:
    QuizFactory ();
    void setName ();
    void createQuiz ();
    void addSheetDialog ();
protected:
    Quiz quiz;
    int screenHeight;
    int screenWidth;
};

#endif //QUIZ_QUIZFACTORY_H
