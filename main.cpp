#include "Game.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
int main() {

        string line;
        ifstream myfile("Menu.txt");
        cout << setw(25);
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                cout << setw(25);
                cout << line << '\n';
            }
            myfile.close();
        }

        else cout << "Unable to open file";

        // menu options

        menu :
        cout << "Chose one option from the following list by entering it's number (1-2-3)";
        cout << endl << "1 - New Game " << endl << "2 - Load Game" << endl << "3 - Quit" <<endl<<endl;

        int decision;
        cin >> decision;

        switch (decision)
        {


        //starts a new game
        case 1 :  
        { system("CLS");
        string s1;
        string s2;
        //Get players name

        cout << "What is the name of player 1 ?" << endl << "";

        cin >> s1;
        Player p1(s1);

        cout << "What is the name of player 2 ?" << endl << "";
        cin >> s2;
        Player p2(s2);
        cout << "Okay " << s1 << " and " << s2;
        cout << " ready to start ? (y/n)";

        char yn;
        while (true) {
            cin >> yn;

            if (yn == 'y') {
                break;
            }
            else {
                cout << "okay then , type y when you are";
            }
        }

        system("CLS");

        Game game1(p1, p2);
        game1.play();
        getchar();
        break;
        }

        //loads old game
        case 2 :
        {
            system("CLS");
            cout << "get rekt bozo baad ma 3melt shi hon";
        }

        //stops program
        case 3 : 
        { return 0;
        }
        //no correspondance
        default :
        {   system("CLS");
            cout << "The Number you entered does not correspond to one of the options !";
            cout << endl;
            goto menu;
        }
        } // swicth statement end

        


        
    

}









    
