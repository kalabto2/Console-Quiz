//
// Created by tom on 19.05.20.
//

#include <fstream>
#include <typeinfo>
#include "AnswerSheet.h"

AnswerSheet::AnswerSheet(Quiz quiz1) {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%Y%m%d-%H:%M:%S",timeinfo);
    std::string str(buffer);
    id = str;
    quiz = quiz1;

    for (auto & sheet: quiz.sheets){
        vector <shared_ptr<Answer> > shA;
        vector <int> shSc;
        for (auto & q: sheet.answers){
            shared_ptr<Answer> ans;
            if (typeid(*q.get()) == typeid(TextAnswer))
                ans = shared_ptr<Answer> (new TextAnswer());
            else if (typeid(*q.get()) == typeid(ValueAnswer))
                ans = shared_ptr<Answer> (new ValueAnswer());
            else if (typeid(*q.get()) == typeid(SingleChoiceAnswer))
                ans = shared_ptr<Answer> (new SingleChoiceAnswer());
            else if (typeid(*q.get()) == typeid(MultipleChoiceAnswer))
                ans = shared_ptr<Answer> (new MultipleChoiceAnswer());
            else if (typeid(*q.get()) == typeid(PairChoiceAnswer))
                ans = shared_ptr<Answer> (new PairChoiceAnswer());

            shA.push_back(ans);
            shSc.push_back(0);
        }
        answers.push_back(shA);
        score.push_back(shSc);
    }
}

void AnswerSheet::renderInput(int sheetIndex, int answerIndex) {
     /*mvprintw(0, 0, (to_string(answers[0].size()) + " " + to_string(answers.size()) + " " + to_string(sheetIndex) + " " + to_string(answerIndex)).c_str());
     refresh();
     getch();*/
     answers[sheetIndex][answerIndex].get()->construct(false);
}

void AnswerSheet::save() {
    ofstream outFile(ANSWERSHEET_FILE_PATH + id);
    if (outFile.is_open())
    {
        outFile << "answerSheet" << endl << author << endl << (evaluated ? "1" : "0") << endl << quiz.id << endl;

        for (size_t i = 0; i < answers.size(); i++){
            for (size_t j = 0; j < answers[i].size(); j++) {
                answers[i][j].get()->save();
                outFile << answers[i][j].get()->getId() << " " << to_string(score[i][j]) << endl;
            }
            outFile << endl;
        }

        outFile.close();
    }
}
