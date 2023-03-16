#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include "Game.h"
#include "Board.h"
#include "Position.h"

using namespace std;

//constructor 
// I initiliased the default starting position but we will be changing it later on

Game::Game(Player p1, Player p2) : first(p1), second(p2) {
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
            board[i][j] = Position::UNPLAYABLE;
        }
    }
    board[4][4] = board[3][3] = Position::BLACK;
    board[3][4] = board[4][3] = Position::WHITE;
}




//has to be implmeneted as drawBoard in Board class

void Game::printboard() {
    // system("CLS");

    cout << "    0   1   2   3   4   5   6   7" << endl; // column numbers
    cout << "  +--------------------------------+" << endl; // horizontal line
    for (int y = 0; y < 8; y++) { // A line
        cout << char('0' + y) << " "; // row letter
        for (int x = 0; x < 8; x++) { // An entry
            cout << "| " << board[x][y] << " ";
        }
        cout << "|" << endl;
        cout << "  +--------------------------------+" << endl; // horizontal line
    }
}

// helps count score will later be outputted

void Game::countChar(char arr[8][8],int& countBlack,int& countWhite,int& countEmpty)
{
    // Loop through the array and count the occurrences of each character
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {

            if (arr[i][j] == Position::BLACK) {
                countBlack++;
            }
            else if (arr[i][j] == Position::WHITE) {
                countWhite++;
            }
            else if (arr[i][j] == Position::UNPLAYABLE) {
                countEmpty++;
            }
        }
    }
}


//game mechanics
//might implement exception handling for out of range,weird charachters and occupied position (so far seems uselss)

void Game::play() {
    //Do many turns

        do {
            //Draw the board

            printboard();

            cout << "It is " << currentPlayer->getName() << "'s turn. You will place your sign " << getCurrentPlayerSymbol() << " by choosing a number from 0 to 7 for your i and j index " << endl;

            //Get a i index

            int i, j;

            cout << "Chose i ";
            cin >> i;

            cout << "Chose j ";
            cin >> j;

            cout << endl;

            system("CLS");

            //Confirm the play is on the board
            if ((i < 0 || i > 7) || (j < 0 || j > 7)) {
                cout << "Invalid range, please pick a position between 0 and 7, inclusive, for both i and j." << endl;
                //  system("CLS");
                continue;
            }
            //Confirm the play is empty
            if ((board[i][j]) != Position::UNPLAYABLE) {
                cout << "Position " << "i = " << i << " j = " << j << " is already occupied!" << endl;
                //  system("CLS");
                continue;
            }

            //get sign of play to replace on board if all is ok
            (board[i][j]) = getCurrentPlayerSymbol();

            //will not be used thats not how othello works
            //keeping as reference for now

            /*
            for (int y = 0; y < 8; y++) { // Checking Rows
                won |= (board[0 + y * 8] != SPACE) && (board[0 + y * 8] == board[1 + y * 8]) && (board[1 + y * 8] == board[2 + y * 8]);
            }
            for (int x = 0; x < 8; x++) { // Checking Columns
                won |= (board[x + 0 * 3] != SPACE) && (board[x + 0 * 3] == board[x + 1 * 3]) && (board[x + 1 * 3] == board[x + 2 * 3]);
            }
            won |= (board[4] != SPACE) && (board[0] == board[4]) && (board[4] == board[8]);
            won |= (board[4] != SPACE) && (board[6] == board[4]) && (board[4] == board[2]);
            */

            moreMoves = false;
            for (int j = 0; j < 8; j++) {
                for (int i = 0; i < 8; i++) {
                    moreMoves |= (board[i][j] == Position::UNPLAYABLE);
                }
            }
            //switches turn and displays count
            if (!won) {
                if (currentPlayer == &first) currentPlayer = &second;
                else currentPlayer = &first;

                int countBlack = 0; int countWhite = 0; int countEmpty = 0;
                countChar(board, countBlack, countWhite, countEmpty);
                cout << "Count X : " << countBlack << "  Count O : " << countWhite << "  Count - : " << countEmpty << endl << endl;

                //  system("CLS");
            }

        }

        while (!won && moreMoves);

    //Draw the final board
    printboard();

    //Declare winner, if someone won
    if (won) {
        cout << currentPlayer->getName() << " won!" << endl;
    } // Declare Tie if nobody won
    else if (!moreMoves) cout << "Tie Game!" << endl;

}

// used to get which player is playing and print that char
//it will rreturn either B or W

char Game::getCurrentPlayerSymbol() {
    return (currentPlayer == &first) ? Position::BLACK : Position::WHITE;
}
