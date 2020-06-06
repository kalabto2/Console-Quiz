//
// Created by tom on 19.04.20.
//

#include "Quiz.h"
#include <fstream>

const string Quiz::QUIZ_FILE_PATH = "files/quizzes/";

Quiz::Quiz() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%Y%m%d-%H:%M:%S",timeinfo);
    std::string str(buffer);
    id = str;
}

Quiz::Quiz(const string& filePath) {
    ifstream inFile(filePath);
    id = filePath.substr(filePath.size() - 17);

    if (inFile.is_open()) {
        string line;

        for (int i = 0; getline (inFile,line); i++){
            if (i == 0) {
                if (line != "quiz") {
                    inFile.close();
                    throw "Incompatible file type: expected 'quiz'";
                }
            }
            else if (i == 1)
                name = line;
            else {
                try {
                    sheets.emplace_back(line);
                } catch (const char * err){
                    inFile.close();
                    throw err;
                }
            }
        }
        if (sheets.empty())
            throw "No sheets in quiz";
        inFile.close();
    } else
        throw "Couldn't open, or find quiz file";
}

void Quiz::addSheet(const Sheet& sheet) {
    sheets.push_back(sheet);
}

void Quiz::save() {
    ofstream outFile(QUIZ_FILE_PATH + id);
    if (outFile.is_open())
    {
        outFile << "quiz" << endl << name << endl;
        for (auto & sheet : sheets){
            outFile << sheet.getId() << endl;
        }
        outFile.close();
    }
}

vector<string> Quiz::preview(const string& filePath) {
    vector <string> res;
    ifstream inFile(filePath);

    if (inFile.is_open()){
        string line;
        int i = 0;

        while ( getline (inFile,line) )
        {
            if (i == 2) break;
            res.push_back(line);
            i++;
        }
        if (i < 2)
            throw "Incompatible file type in quiz directory. Expected 'quiz' type";
        inFile.close();
    } else
        throw "Could not open file of type 'quiz'";

    return res;
}

string Quiz::print(bool printQuestion, bool printAnswer, bool printSpaceAnswer) {
    string result;

    ifstream bannerFile (BANNER_FILE);
    if (bannerFile.is_open())
    {
        string line;
        int i = 0;
        while ( getline (bannerFile,line) )
        {
            result += "\t" + line + "\n";
            i++;
        }
        wrefresh(stdscr);
        bannerFile.close();
    }
    result += "\n\tQuiz name: " + name + "\t\tcreated " + id + "\n";

    int i = 1;
    for (auto & sheet : sheets) {
        string controlQ = sheet.getControlQuestion();
        string controlA = sheet.getControlAnswer();
        result +=
        "------------------------------------------------------------------------------------------------------------------------"
        "\nSheet no. " + to_string(i) + (controlQ.empty() ? "" : "\t\tSHEET CONTROL: " + controlQ) + (controlQ.empty() || !printAnswer ? "" : "\t\tENTRY ANSWER: " + controlA) + "\n"
        "------------------------------------------------------------------------------------------------------------------------"
        "\n" + sheet.print(printQuestion, printAnswer, printSpaceAnswer);
        i++;
    }

    return result;
}

string Quiz::getName() {
    return name;
}

string Quiz::getId() {
    return id;
}

void Quiz::setName(const string & name) {
    this->name = name;
}

tuple < vector<string>, vector< vector<int> > > Quiz::getPrintedSheets(bool printQuestion, bool printAnswer, bool printSpaceAnswer) {
    vector<string> printedResult;
    vector< vector<int> > questionPointer;

    int i = 1;
    for (auto & sheet : sheets) {
        auto lineInfo = sheet.getLines(printQuestion, printAnswer, printSpaceAnswer);
        questionPointer.push_back(lineInfo);
        printedResult.push_back(
         "------------------------------------------------------------------------------------------------------------------------"
         "\nSheet no. " + to_string(i) + "\n"
         "------------------------------------------------------------------------------------------------------------------------"
         "\n" + sheet.print(printQuestion, printAnswer, printSpaceAnswer));
        i++;
    }

    return make_tuple(printedResult, questionPointer);
}

vector<string> Quiz::getControlQuestions() {
    vector<string> res;
    for (auto & q : sheets){
        res.push_back(q.getControlQuestion());
    }
    return res;
}

vector<string> Quiz::getControlAnswers() {
    vector<string> res;
    for (auto & q : sheets){
        res.push_back(q.getControlAnswer());
    }
    return res;
}
