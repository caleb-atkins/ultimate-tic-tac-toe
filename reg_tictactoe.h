/***********************************************************************************
reg_tictactoe.h - reg_tictactoe.cpp header file with class attributes and prototypes
***********************************************************************************/

#ifndef _reg_tictactoe_h
#define _reg_tictactoe_h

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

#include "cell.h"


/*
 * RegTicTacToe provides object attributes and functions
 * on individual regular game board within one cell of the
 * ultimate game board
*/
class RegTicTacToe
{

  private:

    /* character indicating regular board's status:
     * U -> unfinished game board, play still in progress
     * X -> X won the board
     * O -> O won the board
     * T -> the board resulted in a tie
    */
    char boardStatus;

  public:
    // 3 x 3 board of Cell objects
    Cell board[3][3];

    RegTicTacToe();
    ~RegTicTacToe();

    void setBoardStatus(char newBoardStatus);
    char getBoardStatus();

    std::string drawCellValues(Cell line[]);
    void drawBoard();

    void fillO();
    void fillX();

    bool checkMatch(Cell a, Cell b, Cell c);

    void regMove(char newCellStatus, int x, int y);
};

#endif
