//
// Created by tom on 18.04.20.
//

#include "Question.h"

#include <utility>



Question::Question(int id) : id(id) {}

/* ----------------------------------------------------- */

TextQuestion::TextQuestion(int id, string question) : Question(id), question(std::move(question)) {}

/* ----------------------------------------------------- */

SingleChoiceQuestion::SingleChoiceQuestion(int id, string question) : Question(id), question(std::move(question)) {}