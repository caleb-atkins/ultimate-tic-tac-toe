/***************************************************************
reg_tictactoe.cpp - object for regular tic-tac-toe playing board
- 9 x 9 board of Cell objects
***************************************************************/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>

#include "cell.h"
#include "reg_tictactoe.h"

using namespace std;

// RegTicTacToe constructor (sets each cell status to empty, sets board status to unfinished)
RegTicTacToe::RegTicTacToe()
{
  for (int x = 0; x < 3; x++)
  {
    for (int y = 0; y < 3; y++)
    {
      this -> board[x][y].setCellStatus('e');
    }
  }

  this -> setBoardStatus('U');

}

// RegTicTacToe destructor
RegTicTacToe::~RegTicTacToe(){}

/*
 * @desc sets the board's current gameplay status
 *
 * @param char newBoardStatus - {'U', 'X', 'O', 'T'}
 * - character indicating if board is unfinished, if X or O won, or if a tie resulted
*/
void RegTicTacToe::setBoardStatus(char newBoardStatus)
{
  if (newBoardStatus == 'U'){this -> boardStatus = newBoardStatus;}
  else if (newBoardStatus == 'X'){this -> boardStatus = newBoardStatus;}
  else if (newBoardStatus == 'O'){this -> boardStatus = newBoardStatus;}
  else if (newBoardStatus == 'T'){this -> boardStatus = newBoardStatus;}
  else {throw "Invalid board status";}
}

/*
 * @desc gets the given board's current gameplay status
 *
 * @return current board status
*/
char RegTicTacToe::getBoardStatus()
{
  return this -> boardStatus;
}

/*
 * @desc draws a single line of cell values for a given regular board (ex.  X | X | X)
 *
 * @param Cell line[] - array of three Cell objects that make up a line in the board
 *
 * @return std::string valueLine - string of cell values for line of cells in board (ex. "  X | X | X ")
*/
std::string RegTicTacToe::drawCellValues(Cell line[])
{

    std::string valueLine = " ";

    for (int i = 0; i < 3; i++)
    {
      // if empty, insert space
      if (line[i].getCellStatus() == 'e')
      {
        valueLine.push_back(' ');
      }

      // or insert X | O
      else
      {
        valueLine.push_back(line[i].getCellStatus());
      }


      if (i < 2)
      {
        valueLine += " | ";
      }

      else
      {
        valueLine += " ";
      }

    }
    return valueLine;
}

/*
 * @desc print current regular tic tac toe board
 * Note: unused by ult_tictactoe.cpp, kept for maintenance
*/
void RegTicTacToe::drawBoard()
{
  for (int x = 0; x < 3; x++)
  {
      cout << "   |   |   " << endl;
      cout << drawCellValues(this -> board[x]) << endl;;

      if (x <= 1){cout << "___|___|___" << endl;}
      else {cout << "   |   |   " << endl;}
  }
}

/*
 * @desc fill current game board with O values, indicating O won the board
*/
void RegTicTacToe::fillO()
{
  for (int x = 0; x < 3; x++)
  {
    for (int y = 0; y < 3; y++)
    {
      this -> board[x][y].setCellStatus('O');
    }
  }
}

/*
 * @desc fill current game board with X values, indicating X won the board
*/
void RegTicTacToe::fillX()
{
  for (int x = 0; x < 3; x++)
  {
    for (int y = 0; y < 3; y++)
    {
      this -> board[x][y].setCellStatus('X');
    }
  }
}

/*
 * @desc checks to see if three values given match, indicating a tic-tac-toe
 *
 * @param Cell a - first Cell object to check
 * @param Cell b - second Cell object to check
 * @param Cell c - third Cell object to check
 *
 * @return true if they match, false if they do not
*/
bool RegTicTacToe::checkMatch(Cell a, Cell b, Cell c)
{
  if (a.getCellStatus() != 'e')
  {
    if ((a.getCellStatus() == b.getCellStatus()) && (b.getCellStatus() == c.getCellStatus()))
    {
      return true;
    }
  }

  return false;
}


/*
 * @desc if the cell is empty, input given cell status value and check if board was won/tied
 *
 * @param char newCellStatus - new cell status to fill in (either X or O)
 * @param int x - row value of board to be filled
 * @param int y - column value of board to be filled

*/
void RegTicTacToe::regMove(char newCellStatus, int x, int y){

  if (this -> board[x][y].getCellStatus() == 'e')
  {
    if (newCellStatus == 'X')
    {
      this -> board[x][y].setCellStatus('X');
    }

    else if (newCellStatus == 'O')
    {
      this -> board[x][y].setCellStatus('O');
    }

    else
    {
      throw "Unidentifiable turn";
    }
  }

  else
  {
    throw "Invalid move (cell already occupied)";
  }

  // Game logic! - check for win or tie

  // Check vertical
  for (int column = 0; column < 3; column++)
  {
    if (this -> checkMatch(this -> board[0][column], this -> board[1][column], this -> board[2][column]))
    {
      char newBoardStatus = this -> board[0][column].getCellStatus() == 'X' ? 'X' : 'O';
      this -> setBoardStatus(newBoardStatus);

      if (this -> getBoardStatus() == 'X')
      {
        this -> fillX();
      }

      else if (this -> getBoardStatus() == 'O')
      {
        this -> fillO();
      }

      else
      {
        throw "Invalid board status.";
      }
    }
  }

  //Check horizontal
  for (int row = 0; row < 3; row++)
  {
    if (this -> checkMatch(this -> board[row][0], this -> board[row][1], this -> board[row][2]))
    {
      char newBoardStatus = this -> board[row][0].getCellStatus() == 'X' ? 'X' : 'O';
      this -> setBoardStatus(newBoardStatus);

      if (this -> getBoardStatus() == 'X')
      {
        this -> fillX();
      }

      else if (this -> getBoardStatus() == 'O')
      {
        this -> fillO();
      }

      else
      {
        throw "Invalid board status.";
      }
    }
  }

  //Check diagonals

  if (this -> checkMatch(this -> board[0][0], this -> board[1][1], this  -> board[2][2]))
  {
    char newBoardStatus = this -> board[0][0].getCellStatus() == 'X' ? 'X' : 'O';
    this -> setBoardStatus(newBoardStatus);

    if (this -> getBoardStatus() == 'X')
    {
      this -> fillX();
    }

    else if (this -> getBoardStatus() == 'O')
    {
      this -> fillO();
    }

    else
    {
      throw "Invalid board status.";
    }
  }

  if (this -> checkMatch(this -> board[0][2], this -> board[1][1], this  -> board[2][0]))
  {
    char newBoardStatus = this -> board[1][1].getCellStatus() == 'X' ? 'X' : 'O';
    this -> setBoardStatus(newBoardStatus);

    if (this -> getBoardStatus() == 'X')
    {
      this -> fillX();
    }

    else if (this -> getBoardStatus() == 'O')
    {
      this -> fillO();
    }

    else
    {
      throw "Invalid board status.";
    }
  }

  //Check if draw
  if (this -> getBoardStatus() == 'U')
  {
    // boolean for if any cells are empty, if not and nobody won then tie
    bool anyEmpty = false;

    for (int x = 0; x < 3; x++)
    {
      for (int y = 0; y < 3; y++)
      {
        if (this -> board[x][y].getCellStatus() == 'e')
        {
          anyEmpty = true;
        }
      }
    }

    if (anyEmpty == false)
    {
      this -> setBoardStatus('T');
    }
  }

}
