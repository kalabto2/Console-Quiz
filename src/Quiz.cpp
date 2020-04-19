//
// Created by tom on 19.04.20.
//

#include "Quiz.h"

void Quiz::setName(string name) {
    this->name = name;
}

Quiz::Quiz() : id(5) {}

void Quiz::addSheet(Sheet sheet) {
    sheets.emplace_back(sheet);
}
