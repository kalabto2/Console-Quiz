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
    /** variables holds size of screen */
    int screenWidth, screenHeight;
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
};

#endif //QUIZ_APP_H
