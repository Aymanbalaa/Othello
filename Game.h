#include "Player.h"
#pragma once
class Game
{
public:
    Game(Player p1, Player p2);
    void printboard();
    void play();

    void countChar(char arr[8][8], int& countX, int& countO, int& countUnderscore);

private:
    //  static const char X = 'X', O = 'O', SPACE = '_';

    char getCurrentPlayerSymbol();


    //Set up board like this:
    //{.,.,.,
    // .,.,.,
    // .,.,.}

    //00 01 02
    //03 04 05
    //06 07 08
    char board[8][8];


    Player first, second;
    Player* currentPlayer = &first;
    bool won = false, moreMoves = true;
};

