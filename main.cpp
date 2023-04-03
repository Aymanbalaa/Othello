#include "Game.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
int main() {
    //DISPLAYS OTHELLO LOGO

    string line;
    ifstream myfile("Menu.txt");

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            cout << line << '\n';
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file";
    }
    // MENU OPTIONS
    bool validInput = false;
    while (!validInput) {
        cout << "Choose an option (1-2-3): ";
        cout << endl << "1 - New Game " << endl << "2 - Load Game" << endl << "3 - Quit" << endl << endl;
        int decision;
        cin >> decision;

        switch (decision) {

        // NEW GAME
        case 1: {
            system("CLS");
            string s1;
            string s2;

            cout << "What is the name of Player 1?" << endl << "";
            cin >> s1;
            Player p1(s1);

            cout << "What is the name of Player 2?" << endl << "";
            cin >> s2;
            Player p2(s2);

            cout << "Okay " << s1 << " and " << s2 << endl;

            cout << "What starting position would you like?" << endl;
            cout << "1 - Default" << endl;
            cout << "2 - 5 are different offset non-standard" << endl;

            int starting;
            cin >> starting;

            Game Game1(p1, p2, starting);

            cout << "Ready to start? (y/n)";

            char yn;
            while (true) {
                cin >> yn;

                if (yn == 'y') {
                    break;
                }
                else {
                    cout << "Okay then, type y when you are";
                }
            }

            system("CLS");
            Game1.play();
            getchar();
            validInput = true;
            break;
        }
        
        //LOAD GAME
        case 2: {
            system("CLS");
            Player p1("First");
            Player p2("Second");
            Game game2(p1, p2);
            game2.Load();
            game2.play();
            validInput = true;
            break;
        }

        //EXIT
        case 3: {
            return 0;
        }
        default: {
            system("CLS");
            cout << "The number you entered does not correspond to one of the options!" << endl;
            cout << endl;
            break;
        }
        } // switch statement end
    } // while loop end

    return 0;
}







    
