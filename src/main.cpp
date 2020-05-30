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
        } else if (string(args[1]) == "STUDENT"){
            string username;
            cout << "Enter your username:" << endl;
            cin >> username;
            App theGame;
            theGame.setUsername(username);
            theGame.run(true);
        } else if (string(args[1]) == "TEACHER"){
            string code;
            if (!App::getPassword().empty()) {
                cout << "Enter TEACHER's password:" << endl;
                cin >> code;
            }
            if (code != App::getPassword()){
                cout << "Bad password!" << endl;
                return 1;
            }
            App theGame;
            theGame.run();
        }
        else {
            cout << "no matching argument!" << endl;
            cout << App::getInfo();
            return 1;
        }
    }
    else if (argv > 2){
        if (string(args[1]) == "--import"){
            string code;
            if (!App::getPassword().empty()) {
                cout << "Enter TEACHER's password:" << endl;
                cin >> code;
            }
            if (code != App::getPassword()){
                cout << "Bad password!" << endl;
                return 1;
            }
            App::import(argv,args);
        }
        else {
            cout << "no matching argument!" << endl;
            return 1;
        }
    }

    return 0;
}