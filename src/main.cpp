#include <iostream>
#include "App.h"

using namespace std;

int main (int argv, char ** args) {
    if (argv <= 1){
        cout << App::getInfo();
    }
    else if (argv == 2){
        if (string(args[1]) == "--help"){
            cout << App::getInfo();
        } else if (string(args[1]) == "--import"){
            // TODO
        } else if (string(args[1]) == "STUDENT"){
            string username;
            cout << "Enter your username:" << endl;
            cin >> username;
            App theGame;
            theGame.setUsername(username);
            theGame.run(true);
        } else if (string(args[1]) == "TEACHER"){
            string code;
            cout << "Enter TEACHER's password:" << endl;
            cin >> code;
            if (code != "password"){
                cout << "Bad password!" << endl;
                return 1;
            }
            App theGame;
            theGame.run();
        }
        else {
            cout << "no matching argument!" << endl;
            return 1;
        }
    }
    else {
        cout << "no matching argument!" << endl;
        return 1;
    }

    return 0;
}