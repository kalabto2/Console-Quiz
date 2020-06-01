//
// Created by tom on 19.05.20.
//

#ifndef QUIZ_SHOWROOM_H
#define QUIZ_SHOWROOM_H

#include "Quiz.h"
#include "MainMenu.h"
#include "AnswerSheet.h"


/** Helps render and handle user input while filling or evaluating quiz. */
class ShowRoom {
private:
    /** Represents quiz, which is shown. */
    Quiz quiz;
    /** Represents answerSheet, which is student filling, or teacher evaluating. */
    AnswerSheet answerSheet;
    /** Holds height dimension of screen. */
    int screenHeight;
    /** Holds width dimension of screen. */
    int screenWidth;
    /** Variable holds number of rows, that are scrolled in window. */
    int showWinScroll = 0;
    /** Path to files with exports. */
    const string EXPORTS_FILE_PATH = "files/exports/";

    /** Scrolls @param window to (@param scrolledLines)-number of lines.
     * @param window pointer to window.
     * @param content Content, which is scrolled.
     * @param scrolledLines number of lines to scroll. If are negative, scrolling is UP, else DOWN. When is 0, prints
     * content to window. */
    void scrollWin (WINDOW * window, const string& content, int scrolledLines);

public:
    /** Loads variable quiz, sets info about screen and creates blank answerSheet.
     * @param quizFilePath relative filePath to file with quiz. */
    ShowRoom (const string& quizFilePath);

    /** Loads variable quiz, sets info about screen and loads filled answerSheet.
     * @param quizFilePath relative filePath to file with quiz.
     * @param answerSheetFilePath relative filePath to file with answerSheet. */
    ShowRoom (const string& quizFilePath, const string& answerSheetFilePath);

    /** Exports quiz/answerSheet according to 'action'.
     * @param action Sets, what kind of export will be made. */
    void Export (MainMenu::MENU_ACTION action);

    /** Runs on 2 modes - Evaluation of answeSheet and Filling answerSheet. Renders quiz window, handles input.
     * @param fillMode if true, method runs on Filling mode. */
    void StartQuiz (bool fillMode = true);

    /** Sets variable author.
     * @param author name of author. */
    void setAuthor (const string& author);

    /** Renders window of quiz selection and handles input.
     * @return name of file. */
    static string selectQuiz ();

    /** Renders window of answerSheet selection and handles input.
     * @return name of file. */
    static string selectAnswersheet (const string& quizId);

    /** Renders window of quiz, or answerSheet selection and handles input.
     * @param findQuiz when true, runs on quiz selection mode.
     * @param quizId name of quizFile, to whom is answerSheet paired with.
     * @return name of file. */
    static string selectFile (bool findQuiz = true, const string& quizId = "");
};


#endif //QUIZ_SHOWROOM_H