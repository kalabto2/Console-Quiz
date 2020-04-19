# App

Semestral work on PA2

## Description
 After starting App, **main menu** shows. Menu contains following:
 * Start Quiz
    * Student / Teacher choose quiz to complete
 * Create Quiz
    * Teacher creates questions, answers and put them into sheet, quiz
 * Evaluate Quiz
    * Teacher choose test and evaluates it
 * Import Export
    * Can export sheets, quizzes to text file, ...
 * Settings
 * Help
    * Info about app
 * Exit
 
All data about quiz (question, answers ...) will be stored in added files

## Classes
* Question - represents 1 question on quiz sheet. Uses polymorphism
  * Text Question - long text question
  * Single choice Question - one correct answer
  * // TODO
* Answer - represents 1 type of answers
    * Text Question - student answers to text field
    * // TODO ...
* Sheet - represents 1 quiz sheet.
* Quiz - Represents 1 quiz containing questions & corresponding types of answers
* FilledQuiz - represents answers of student, to 
* QuizFactory - helping class for creating Quizzes
* MainMenu - menu after starting app
* App - App class ...