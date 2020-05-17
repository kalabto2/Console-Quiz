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
