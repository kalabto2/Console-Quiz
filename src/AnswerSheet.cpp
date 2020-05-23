//
// Created by tom on 19.05.20.
//

#include <fstream>
#include <typeinfo>
#include <sstream>
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

vector<string> AnswerSheet::preview(const string& id) {
    vector <string> res;
    ifstream inFile(id);

    if (inFile.is_open()){
        string line;
        int i = 0;

        while ( getline (inFile,line) )
        {
            if (i == 2) {
                res.push_back((line == "1" ? "evaluated" : "not evaluated"));
            } else if (i == 3){
                res.push_back(line);
                break;
            }
            else
                res.push_back(line);
            i++;
        }
        inFile.close();
    }

    return res;
}

AnswerSheet::AnswerSheet(Quiz quiz1, string id) {
    quiz = quiz1;
    ifstream inFile(id);
    this->id = id.substr(ANSWERSHEET_FILE_PATH.size() + 2);

    if (inFile.is_open()) {
        string line;
        vector<shared_ptr<Answer> > sheet;
        vector<int> scoreOfSheet;
        for (int i = 0; getline (inFile,line); i++){
            if (i == 0) {
                if (line != "answerSheet")
                    throw "Incompatible file type: expected 'answerSheet'";
            }
            else if (i == 1)
                author = line;
            else if (i == 2)
                evaluated = line == "1";
            else if (i == 3)
                ;
            else{
                if (line.empty()){
                    if (sheet.empty())
                        continue;
                    answers.push_back(sheet);
                    sheet.clear();
                    score.push_back(scoreOfSheet);
                    scoreOfSheet.clear();
                    continue;
                }
                istringstream iss (line);
                string tmp;
                iss >> tmp;
                sheet.push_back(Answer::getAnswer(tmp));
                iss >> tmp;
                scoreOfSheet.push_back(stoi(tmp));
            }
        }

        inFile.close();
    }
}
