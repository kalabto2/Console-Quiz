//
// Created by tom on 18.04.20.
//

#ifndef QUIZ_QUIZ_H
#define QUIZ_QUIZ_H

#include <vector>
#include "Sheet.h"

using namespace std;

class Quiz {
public:
    void addSheet (Sheet);
    void setName (string name);
    void save ();
    Quiz ();
    Quiz (const string& filePath);
    static vector<string> preview (const string& id);
protected:
    vector<Sheet> sheets;
    string id;
    string name;

    const string QUIZ_FILE_PATH = "files/quizzes/";
};

#endif //QUIZ_QUIZ_H
