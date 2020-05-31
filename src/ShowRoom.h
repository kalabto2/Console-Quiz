//
// Created by tom on 19.05.20.
//

#ifndef QUIZ_SHOWROOM_H
#define QUIZ_SHOWROOM_H

#include "Quiz.h"
#include "MainMenu.h"
#include "AnswerSheet.h"

class ShowRoom {
private:
    Quiz quiz;
    AnswerSheet answerSheet;
    int screenWidth, screenHeight, showWinScroll = 0;
    void scrollWin (WINDOW * window, string content, int scrolledLines);

    const string EXPORTS_FILE_PATH = "files/exports/";

public:
    ShowRoom (Quiz quiz);
    ShowRoom (string quizId);
    ShowRoom (string quizId, string answerSheetId);
    void setAuthor (const string& author);
    void Export (MainMenu::MENU_ACTION action);
    void StartQuiz (bool fillMode = true);
    static string selectQuiz ();
    static string selectAnswersheet (const string& quizId);
    static string selectFile (bool findQuiz = true, const string& quizId = "");
};

#endif //QUIZ_SHOWROOM_H
