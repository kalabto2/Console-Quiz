//
// Created by tom on 18.04.20.
//

#ifndef QUIZ_QUIZFACTORY_H
#define QUIZ_QUIZFACTORY_H

#include "Quiz.h"

/** Helping class to quiz. Manages quiz creating. */
class  QuizFactory {
public:
    /** Cleans screen, set-ups variables. */
    QuizFactory ();

    /** Represents setting of name of the quiz. Renders window, handles input and sets name. */
    void setName ();

    /** Manages creating of quiz */
    void createQuiz ();

    /** Renders 'Add Sheet' window, handles input and manages creating of sheet. */
    void addSheetDialog ();

protected:
    /** Represents created quiz. */
    Quiz quiz;
    /** Holds dimension of screen. */
    int screenHeight ,screenWidth;
};

#endif //QUIZ_QUIZFACTORY_H
