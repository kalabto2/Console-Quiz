//
// Created by tom on 19.04.20.
//

#include "Sheet.h"
#include <ncurses.h>
#include <fstream>

Sheet::Sheet() {
    getmaxyx(stdscr,screenHeight,screenWidth);

    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%Y%m%d-%H:%M:%S",timeinfo);
    std::string str(buffer);
    id = str;
}

void Sheet::addQuestion(const shared_ptr<Question>& question) {
    questions.push_back(question);
}

void Sheet::addAnswer(shared_ptr<Answer> answer) {
    answers.push_back(answer);
}

void Sheet::createSheet() {
    wclear(stdscr);
    refresh();
    WINDOW * upperWin = newwin(5, screenWidth, 0, 0); // fce newwin vytvori okno
    box(upperWin, 0,0); // vytvori hranice okolo okna
    mvwprintw(upperWin, 2, screenWidth/2 - 6, "SHEET FACTORY");
    wrefresh(upperWin);

    while (true){
        if (choosePanel() == FINISH_SHEET)
            break;
    }
    save();

}

Sheet::SHEET_OPTION Sheet::choosePanel() {
    clear();
    refresh();
    WINDOW * sideWin = newwin(screenHeight - 5, 60, 5, 0); // fce newwin vytvori okno
    box(sideWin, 0, 0); // vytvori hranice okolo okna

    mvwprintw(sideWin, 0, 60/2-5, "SIDE PANEL");
    mvwprintw(sideWin, 2, 4, "QUESTION");
    mvwprintw(sideWin, 4, 6, "* Text Question");
    mvwprintw(sideWin, 6, 6, "* Choice Question");
    mvwprintw(sideWin, 8, 6, "* Sorting Question");
    mvwprintw(sideWin, 4, 3, "=>");

    mvwprintw(sideWin, (screenHeight - 5) / 2, 4, "ANSWER");
    //mvwprintw(sideWin, (screenHeight - 5) / 2 + 2, 6 , "* Text Answer");

    mvwprintw(sideWin, (screenHeight - 5) - 5, 4, "SAVE & ADD QUESTION");
    mvwprintw(sideWin, (screenHeight - 5) - 3, 4, "SAVE & FINISH SHEET");
    wrefresh(sideWin);

    int pointerPos = 4;

    while (true) {
        if (pointerPos == 4){
            shared_ptr<Question> qs (new TextQuestion());
            qs->renderAnswers(sideWin);
        }
        if (pointerPos == 6){
            shared_ptr<Question> qs (new ChoiceQuestion());
            qs->renderAnswers(sideWin);
        }
        if (pointerPos == 8){
            shared_ptr<Question> qs (new SortingQuestion());
            qs->renderAnswers(sideWin);
        }

        int a = getch();

        if (a == '\n' || a == 'd' || a == KEY_RIGHT || a == KEY_ENTER)
            break;

        if (a == KEY_DOWN || a == 's') {
            mvwprintw(sideWin, pointerPos, 3, "  ");
            pointerPos += (pointerPos < 8 ? 2 : 0);
        } else if (a == KEY_UP || a == 'w') {
            mvwprintw(sideWin, pointerPos, 3, "  ");
            pointerPos -= (pointerPos > 4 ? 2 : 0);
        }
        mvwprintw(sideWin, pointerPos, 3, "=>");
        wrefresh(sideWin);
    }

    shared_ptr<Question> qs;
    if (pointerPos == 4) {
        qs = shared_ptr<Question> (new TextQuestion());
    }
    else if (pointerPos == 6) {
        qs = shared_ptr<Question> (new ChoiceQuestion());
    }
    else if (pointerPos == 8) {
        qs = shared_ptr<Question> (new SortingQuestion());
    }
    qs->construct();
    qs->save();
    addQuestion(qs);


    const int ANSWER_ITEM_HEIGHT = (screenHeight - 5) / 2 + 2;
    pointerPos = ANSWER_ITEM_HEIGHT;
    mvwprintw(sideWin, pointerPos, 3, "=>");
    wrefresh(sideWin);
    while (true) {
        int a = getch();

        if (a == '\n' || a == 'd' || a == KEY_RIGHT || a == KEY_ENTER)
            break;

        if (a == KEY_DOWN || a == 's') {
            mvwprintw(sideWin, pointerPos, 3, "  ");
            pointerPos += (pointerPos < ANSWER_ITEM_HEIGHT + 2 * (qs->getNumOfAnsw() - 1) ? 2 : 0);
        } else if (a == KEY_UP || a == 'w') {
            mvwprintw(sideWin, pointerPos, 3, "  ");
            pointerPos -= (pointerPos > ANSWER_ITEM_HEIGHT ? 2 : 0);
        }
        mvwprintw(sideWin, pointerPos, 3, "=>");
        wrefresh(sideWin);
    }


    shared_ptr<Answer> ans;
    ans = qs->getTypeAnswer(((pointerPos - 27) / 2) + 1);
    ans->construct();
    ans->save();
    addAnswer(ans);


    pointerPos = screenHeight - 5 - 5;
    while (true){
        mvwprintw(sideWin, pointerPos, 1, "=>");
        wrefresh(sideWin);
        int a = getch();

        if (a == '\n' || a == 'd' || a == KEY_RIGHT || a == KEY_ENTER)
            break;

        if (a == KEY_DOWN || a == 's') {
            mvwprintw(sideWin, pointerPos, 1, "  ");
            pointerPos += (pointerPos < (screenHeight - 5 - 3) ? 2 : 0);
        } else if (a == KEY_UP || a == 'w') {
            mvwprintw(sideWin, pointerPos, 1, "  ");
            pointerPos -= (pointerPos > (screenHeight - 5 - 5) ? 2 : 0);
        }
    }

    return (pointerPos == screenHeight - 10 ? ADD_QUESTION : FINISH_SHEET);
}

void Sheet::save() {
    ofstream outFile(SHEET_FILE_PATH + id);
    if (outFile.is_open())
    {
        outFile << "sheet" << endl;

        for (size_t i = 0; i < questions.size(); i++){
            outFile << questions[i].get()->getId() << " " << answers[i].get()->getId() << endl;
        }

        outFile.close();
    }
}

string Sheet::getId() {
    return id;
}

Sheet::Sheet(string id) {
    this->id = id;
    getmaxyx(stdscr,screenHeight,screenWidth);

    ifstream inFile (SHEET_FILE_PATH + id);
    string line;
    if (inFile.is_open()){
        for (int i = 0; getline(inFile, line); i++){
            if (i == 0) {
                if (line != "sheet")
                    throw "Incompatible file type: expected 'sheet'";
            }
            else{
                // questions.push_back() TODO
                string questionId = line.substr(0, 17);
                string answerId = line.substr(18, 17);

                shared_ptr<Question> question;
                shared_ptr<Answer> answer;

                question = Question::getQuestion(questionId);
                answer = Answer::getAnswer(answerId);

                questions.push_back(question);
                answers.push_back(answer);
            }

        }
        inFile.close();
    }

}

string Sheet::print(bool printQuestion, bool printAnswer, bool printSpaceAnswer) {
    string result;

    /*for (size_t i = 0; i < questions.size(); i++){
        result += "----------------------------------------------------\n";
        if (printQuestion){
            result += "\tQ no. " + to_string(i + 1) + ".\n\t\t" + questions[i].get()->print();
        }
        if (printAnswer || printSpaceAnswer){
            result += "\n\tA no. " + to_string(i + 1) + ".\n\t\t" + answers[i].get()->print(printAnswer);
        }
        result += "----------------------------------------------------\n\n";
    }*/
    for (auto & QA : getPrintedQA(printQuestion, printAnswer, printSpaceAnswer)){
        result += QA;
    }

    return result;
}

vector<string> Sheet::getPrintedQA(bool printQuestion, bool printAnswer, bool printSpaceAnswer) {
    vector <string> result;

    for (size_t i = 0; i < questions.size(); i++){
        result.push_back("----------------------------------------------------\n");
        if (printQuestion){
            result[i] += "\tQ no. " + to_string(i + 1) + ".\n\t\t" + questions[i].get()->print();
        }
        if (printAnswer || printSpaceAnswer){
            result[i] += "\n\tA no. " + to_string(i + 1) + ".\n\t\t" + answers[i].get()->print(printAnswer);
        }
        result[i] += "----------------------------------------------------\n\n";
    }

    return result;
}

vector<int> Sheet::getLines(bool printQuestion, bool printAnswer, bool printSpaceAnswer) {
    vector <string> questionsAndAnswers = getPrintedQA(printQuestion, printAnswer, printSpaceAnswer);
    vector <int> result;

    int add = 0;
    for (auto & q : questionsAndAnswers){
        int numOfLines = 0;
        for (auto & c: q){
            if (c == '\n')
                numOfLines ++;
        }
        result.push_back(numOfLines);
        add = numOfLines + add;
    }

    return result;
}

void Sheet::renderInput(int answerIndex) {
    answers[answerIndex].get()->construct();
}

int Sheet::getNumberofQuestions() {
    return questions.size();
}
