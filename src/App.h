//
// Created by tom on 11.04.20.
//

#ifndef QUIZ_APP_H
#define QUIZ_APP_H

#include <string>

using namespace std;

/** Class represents application starting with ncurses initialization */
class App {
protected:
    /** variables holds number of columns of screen */
    int screenWidth;
    /** variables holds number of rows of screen */
    int screenHeight;
    /** variable holds username of student or teacher */
    string username;

public:
    /** Initiates ncurses, sets properties of ncurses */
    App ();

    /** Ends ncurses */
    ~App();

    /** Starts application, loads main menu and makes action.
     * @param studentMode - when true, app launched in limited 'STUDENT' mode. When false, app launched as 'TEACHER' */
    void run (bool studentMode = false);

    /** Gets help info about app.
     * @return info as string */
    static string getInfo ();

    /** Sets variable username */
    void setUsername(const string &username);

    /** Copies passed file names into App's file structure. If file is not compatible, function does nothing.
     * @param[in] argv represents number of arguments of program (including its name and parameter '--import')
     * @param[in] args represents fileNames to be imported */
    static void import(int argv, char ** args);

    /** Renders window for setting password, handles input and save password to file */
    void setPassword ();

    /** Loads password from file. If file not opened, password set to 'password'
     * @return password*/
    static string getPassword ();
};

#endif //QUIZ_APP_H
