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
    Quiz ();
protected:
    vector<Sheet> sheets;
    int id;
    string name;
};

#endif //QUIZ_QUIZ_H
