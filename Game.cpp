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
    

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            board[i][j] = Position::UNPLAYABLE;
        }
    }
    board[4][4] = board[3][3] = Position::WHITE;
    board[3][4] = board[4][3] = Position::BLACK;
}

void Game::play() {
    // Print the board
    printBoard(getCurrentPlayerSymbol());
    // Play the game
    while (!won) {
        // Check if the current player has any valid moves
        if (hasValidMoves(getCurrentPlayerSymbol())) {
            // Get the current player's move
            int x, y;
            std::cout << "Player " << currentPlayer->getName() << ", enter your move (x y): ";
            std::cin >> x >> y;
            // Check if the move is valid
            if (isValidMove(x, y, getCurrentPlayerSymbol())) {
                // Make the move
                board[x][y] = getCurrentPlayerSymbol();
                flip(x, y, getCurrentPlayerSymbol());
                // Check if the game is over
                int countBlack, countWhite, countEmpty;
                countChar(board, countBlack, countWhite, countEmpty);
                if ((countEmpty == 0 )) {
                    won = true;
                }
                else {
                    // Switch players
                    system("cls");
                    currentPlayer = (currentPlayer == &first) ? &second : &first;
                }
            }
            else {
                system("cls");
                std::cout << "Invalid move!\n";
            }
        }
        else {

            int numb = 0;
            do {
                system("cls");
                std::cout << "No valid moves available. Skipping turn.\n";
                // Switch players
                currentPlayer = (currentPlayer == &first) ? &second : &first;
                
                numb++;
            } while (numb < 1);




        }
        // Print the board
        printBoard(getCurrentPlayerSymbol());
    }

    // Print the winner
    int countX, countO, countUnderscore;
    countChar(board, countX, countO, countUnderscore);
    if (countX > countO) {
        std::cout << "Player " << first.getName() << " wins!\n";
        getchar();
    }
    else if (countO > countX) {
        std::cout << "Player " << second.getName() << " wins!\n";
        getchar();
    }
    else {
        std::cout << "It's a tie!\n";
        getchar();
    }


}

//has to be implmeneted as drawBoard in Board class

void Game::printBoard(char currentPlayer) {
    // Calculate valid moves for the current player
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (isValidMove(i, j, currentPlayer)) {
                board[i][j] = Position::EMPTY;
            }
            else if (board[i][j] == Position::EMPTY) {
                board[i][j] = Position::UNPLAYABLE;
            }
        }
    }
    //clear screen using system call
    
    

    // Print the board
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
    int countBlack, countWhite, countEmpty;
    countChar(board, countBlack, countWhite, countEmpty);
    cout << "Count Black = " << countBlack << endl;
    cout << "Count White = " << countWhite << endl;
    cout << "Count Empty = " << countEmpty << endl;

    
}


bool Game::isValidMove(int x, int y, char currentPlayer) {
    // Check if the position is already occupied
    if (board[x][y] != Position::EMPTY && board[x][y] != Position::UNPLAYABLE) return false;

    char opponent = (currentPlayer == Position::BLACK) ? Position::WHITE : Position::BLACK;

    // Check all eight directions from this position
    const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    const int dy[] = { -1, 0, 1,-1 ,1,-1 ,0 ,1 };
    for (int d = 0; d < 8; d++) {
        int i = x + dx[d];
        int j = y + dy[d];

        bool foundOpponent = false;
        while (i >= 0 && i < 8 && j >= 0 && j < 8) {
            if (board[i][j] == opponent) {
                foundOpponent = true;
            }
            else if ((board[i][j] == currentPlayer) && foundOpponent) {
                return true;
            }
            else {
                break;
            }
            i += dx[d];
            j += dy[d];
        }
    }

    return false;
}







void Game::flip(int x, int y, char currentPlayer) {
    char opponent = (currentPlayer == Position::BLACK) ? Position::WHITE : Position::BLACK;

    // Check all eight directions from this position
    const int dx[] = { -1, -1, -1, 0, 0, 1, 1 ,1 };
    const int dy[] = { -1 ,0 ,1 ,-1 ,1 ,-1 ,0 ,1 };
    for (int d = 0; d < 8; d++) {
        int i = x + dx[d];
        int j = y + dy[d];

        bool foundOpponent = false;
        while (i >= 0 && i < 8 && j >= 0 && j < 8) {
            if (board[i][j] == opponent) {
                foundOpponent = true;
            }
            else if ((board[i][j] == currentPlayer && foundOpponent)) {
                // Flip the opponent's pieces in this direction
                int ii = x + dx[d];
                int jj = y + dy[d];
                while (ii != i || jj != j) {
                    board[ii][jj] = currentPlayer;
                    ii += dx[d];
                    jj += dy[d];
                }
                break;
            }
            else {
                break;
            }
            i += dx[d];
            j += dy[d];
        }
    }
}








// helps count score will later be outputted

void Game::countChar(char arr[8][8],int& countBlack,int& countWhite,int& countEmpty)
{


    countBlack = 0;
    countWhite = 0;
    countEmpty = 0;
 
    // Loop through the array and count the occurrences of each character
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {

            if (arr[i][j] == Position::BLACK) {
                countBlack++;
            }
            else if (arr[i][j] == Position::WHITE) {
                countWhite++;
            }
            else if (arr[i][j] == ((Position::EMPTY) )||(Position::UNPLAYABLE))
            {
                countEmpty++;
            }
        }
    }
}


bool Game::hasValidMoves(char currentPlayer) {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (isValidMove(x, y, currentPlayer)) {
                return true;
            }
        }
    }
    return false;
}











// used to get which player is playing and print that char
//it will rreturn either B or W

char Game::getCurrentPlayerSymbol() {
    return (currentPlayer == &first) ? Position::BLACK : Position::WHITE;
}



