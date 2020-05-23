//
// Created by tom on 19.04.20.
//

#include "Quiz.h"
#include <fstream>

void Quiz::setName(string name) {
    this->name = name;
}

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

void Quiz::addSheet(Sheet sheet) {
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

vector<string> Quiz::preview(const string& id) {
    vector <string> res;
    ifstream inFile(id);

    if (inFile.is_open()){
        string line;
        int i = 0;

        while ( getline (inFile,line) )
        {
            if (i == 2) break;
            res.push_back(line);
            i++;
        }
        inFile.close();
    }

    return res;
}

Quiz::Quiz(const string& fileName) {
    ifstream inFile(fileName);
    id = fileName.substr(fileName.size() - 17);

    if (inFile.is_open()) {
        string line;

        for (int i = 0; getline (inFile,line); i++){
            if (i == 0) {
                if (line != "quiz")
                    throw "Incompatible file type: expected 'quiz'";
            }
            else if (i == 1)
                name = line;
            else
                sheets.push_back(Sheet(line));
        }

        inFile.close();
    }
}

string Quiz::print(bool printQuestion, bool printAnswer, bool printSpaceAnswer) {
    string result;

    ifstream bannerFile ("files/banner");
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
        result +=
        "------------------------------------------------------------------------------------------------------------------------"
        "\nSheet no. " + to_string(i) + "\n"
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

tuple < vector<string>, vector< vector<int> > > Quiz::getPrintedSheets(bool printQuestion, bool printAnswer, bool printSpaceAnswer) {
    vector<string> printedResult;
    vector< vector<int> > questionPointer;

    int i = 1;
    for (auto & sheet : sheets) {
        auto lineInfo = sheet.getLines(printQuestion, printAnswer, printSpaceAnswer);
        //for (auto & lf: lineInfo)
        //    lf += 3;
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

void Quiz::renderInput(int sheetIndex, int answerIndex) {
    sheets[sheetIndex].renderInput(answerIndex);
}

vector<vector<string> > Quiz::getPrintSheets(bool printQuestion, bool printAnswer, bool printSpaceAnswer) {
    vector<vector<string> > result;
    for (auto &sheet: sheets)
        result.push_back(sheet.getPrintedQA(printQuestion, printAnswer, printSpaceAnswer));
    return  result;
}

vector<int> Quiz::getNumberOfQuestions() {
    vector<int> result;
    for (auto &sheet: sheets)
        result.push_back(sheet.getNumberofQuestions());
    return result;
}
