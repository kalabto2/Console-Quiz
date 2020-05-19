//
// Created by tom on 19.05.20.
//

#ifndef QUIZ_SHOWROOM_H
#define QUIZ_SHOWROOM_H

#include "Quiz.h"
#include "MainMenu.h"

class ShowRoom {
private:
    Quiz quiz;
    int screenWidth, screenHeight;

    const string EXPORTS_FILE_PATH = "files/exports/";

public:
    ShowRoom (Quiz quiz);
    void Export (MainMenu::MENU_ACTION action);
    void StartQuiz ();
};

#endif //QUIZ_SHOWROOM_H
