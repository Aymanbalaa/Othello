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
			int countX, countO, countUnderscore;
			countChar(board, countX, countO, countUnderscore);
            if ((countUnderscore == 0)) {
				won = true;
			}
            else {
				// Switch players
				currentPlayer = (currentPlayer == &first) ? &second : &first;
			}
		}
        else {
			std::cout << "Invalid move!\n";
		}
		// Print the board


        printBoard(getCurrentPlayerSymbol());
	}

	// Print the winner
	int countX, countO, countUnderscore;
	countChar(board, countX, countO, countUnderscore);
    if (countX > countO) {
		std::cout << "Player " << first.getName() << " wins!\n";
	}
    else if (countO > countX) {
		std::cout << "Player " << second.getName() << " wins!\n";
	}
    else {
		std::cout << "It's a tie!\n";
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
    system("cls");
    

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

/*

void Game::play() {
6  6 6    do {
        // Draw the board
        printboard();
        cout << "It is " << currentPlayer->getName() << "'s turn. You will place your sign " << getCurrentPlayerSymbol() << " by choosing a number from 0 to 7 for your i and j index " << endl;

        // Get an i index and j index from the player
        int i, j;
        cout << "Choose i: ";
        cin >> i;
        cout << "Choose j: ";
        cin >> j;
        cout << endl;
        system("CLS");

        // Confirm the play is on the board
        if ((i < 0 || i > 7) || (j < 0 || j > 7)) {
            cout << "Invalid range, please pick a position between 0 and 7, inclusive, for both i and j." << endl;
            continue;
        }
        // Confirm the play is empty
        if ((board[i][j]) != Position::UNPLAYABLE) {
            cout << "Position " << "i = " << i << " j = " << j << " is already occupied!" << endl;
            continue;
        }

        // Place the current player's symbol on the board
        (board[i][j]) = getCurrentPlayerSymbol();


       //find the pieces that are unplyable because they do not flip any pieces in othello game and output them
        for (int j = 0; j < 8; j++) {
            for (int i = 0; i < 8; i++) {
                if (board[i][j] == Position::UNPLAYABLE) {
					cout << "Position " << "i = " << i << " j = " << j << " is empty!" << endl;
				}
			}
		}
        






        // Check if any pieces need to be flipped
       bool flipped = false;
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                if (di == 0 && dj == 0) {
                    continue;  // Skip this iteration, as it corresponds to the current position
                }
                int ni = i + di;  // Position to check in the i direction
                int nj = j + dj;  // Position to check in the j direction
                bool foundOpponent = false;  // Tracks whether an opponent's symbol was found in this direction
                while (ni >= 0 && ni < 8 && nj >= 0 && nj < 8) {
                    if (board[ni][nj] == Position::UNPLAYABLE) {
                        break;  // Reached the edge of the board or an empty position, so stop checking in this direction
                    }
                    if (board[ni][nj] == getCurrentPlayerSymbol()) {
                        if (foundOpponent) {
                            // Flip the pieces between the current position and the last position where an opponent's symbol was found
                            int ci = i;
                            int cj = j;
                            while (ci != ni || cj != nj) {
                                (board[ci][cj]) = getCurrentPlayerSymbol();
                                ci -= di;
                                cj -= dj;
                            }
                            flipped = true;
                        }
                        break;  // Reached a position with the current player's symbol, so stop checking in this direction
                    }
                    foundOpponent = true;  // Found an opponent's symbol in this direction
                    ni += di;
                    nj += dj;
                }
            }
        }

        // If no pieces were flipped, it is not a valid move
        if (!flipped) {
            cout << "Invalid move. No pieces were flipped." << endl;
            (board[i][j]) = Position::UNPLAYABLE;  // Remove the current player's symbol from the board
            continue;
        }

        

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
            
     } while (!won && moreMoves);

    //Draw the final board
    printboard();

    //Declare winner, if someone won
    if (won) {
        cout << currentPlayer->getName() << " won!" << endl;
    } // Declare Tie if nobody won
    else if (!moreMoves) cout << "Tie Game!" << endl;


}
*/

// used to get which player is playing and print that char
//it will rreturn either B or W

char Game::getCurrentPlayerSymbol() {
    return (currentPlayer == &first) ? Position::BLACK : Position::WHITE;
}



