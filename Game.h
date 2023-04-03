#include "Player.h"
#pragma once
class Game
{
public:
    Game(Player p1, Player p2);
    Game(Player p1, Player p2,int starting);
    void printboard();
    void play();
    void countChar(char arr[8][8], int& countX, int& countO, int& countUnderscore);


    bool hasValidMoves(char currentPlayer);
    bool isValidMove(int x, int y, char currentPlayer);
    void printBoard(char currentPlayer);
    void flip(int x, int y, char currentPlayer);

    void Load();  


private:
    //  static const char X = 'X', O = 'O', SPACE = '_';
    char getCurrentPlayerSymbol();
    void save();
    char board[8][8];
    bool won = false, moreMoves = true;

    Player first, second;
    Player* currentPlayer = &first;

    
};

