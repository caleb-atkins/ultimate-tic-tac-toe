/***********************************************************************************
ult_tictactoe.h - ult_tictactoe.cpp header file with class attributes and prototypes
***********************************************************************************/

#ifndef _ult_tictactoe_h
#define _ult_tictactoe_h

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>

#include "cell.h"
#include "reg_tictactoe.h"


/*
 * UltTicTacToe functions as main gameboard for Ultimate Tic-Tac-Toe
 * that is comprised of a 9x9 grid of RegUltTicTacToe objects
*/
class UltTicTacToe
{

  private:
    // string inidicating current overall game status
    std::string gameStatus;

    // identifies the active row/column the next player must play within
    int activeRow;
    int activeColumn;

    // current player making a move, X or O
    char currPlayer;

  public:
    RegTicTacToe gameBoard[3][3];

    UltTicTacToe();
    ~UltTicTacToe();

    void setGameStatus(std::string &newGameStatus);
    std::string getGameStatus();

    void setActiveBoardRow(int newActiveRow);
    int getActiveBoardRow();

    void setCurrentPlayer(char newPlayer);
    char getCurrentPlayer();
    void swapPlayer();

    void setActiveBoardColumn(int newActiveColumn);
    int getActiveBoardColumn();

    void ultMove(char currPlayer, char boardRow, char boardColumn);

    void displayBoard();

    void checkWin(char currentPlayer);

    void restrictActiveBoard(int hValue, int Vvalue);

    void freeActiveBoard();
    bool isValidMove(char boardRow, char boardColumn);


    void win(char currentPlayer);
};

#endif
