/***************************************************************
Caleb Atkins

Ultimate Tic-Tac-Toe terminal game

ult_tictactoe.cpp - class for entire ultimate tic-tac-toe board object
- 9 x 9 board of RegTicTacToe objects
***************************************************************/


#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>

#include "cell.h"
#include "reg_tictactoe.h"
#include "ult_tictactoe.h"

using namespace std;

// UltTicTacToe constructor
UltTicTacToe::UltTicTacToe()
{
  std::string before = "beforeStart";
  this -> setGameStatus(before);
  this -> setActiveBoardRow(-1);
  this -> setActiveBoardColumn(-1);
}

// UltTicTactoe destructor
UltTicTacToe::~UltTicTacToe(){}

/*
 * sets game status variable to control game flow
 *
 * @param std::string &newGameStatus) - string reference holding overall game status
*/
void UltTicTacToe::setGameStatus(std::string &newGameStatus)
{
  if (newGameStatus == "beforeStart")
  {
    this -> gameStatus = newGameStatus;
  }

  else if (newGameStatus == "running")
  {
    this -> gameStatus = newGameStatus;
  }

  else if (newGameStatus == "finished")
  {
    this -> gameStatus = newGameStatus;
  }

  else if (newGameStatus == "quit")
  {
    this -> gameStatus = newGameStatus;
  }

  else
  {
    throw "Invalid game status.";
  }
}

/*
 * get overall game status
 *
 * @return string gameStatus - current game status
*/
std::string UltTicTacToe::getGameStatus()
{
  return this -> gameStatus;
}

/*
 * set which row on overall game board is active for next move after turn is over
 *
 * @param int newActiveRow - {0, 1, 2} active row after applying restriction
*/
void UltTicTacToe::setActiveBoardRow(int newActiveRow)
{
  this -> activeRow = newActiveRow;
}

/*
 * get which row on overall game board is active for current move
 *
 * @return int activeRow
*/
int UltTicTacToe::getActiveBoardRow()
{
  return this -> activeRow;
}

/*
 * set which column on overall game board is active for next move after turn is over
 *
 * @param int newActiveColumn - {0, 1, 2} active column after applying restriction
*/
void UltTicTacToe::setActiveBoardColumn(int newActiveColumn)
{
  this -> activeColumn = newActiveColumn;
}

/*
 * get which row on overall game board is active for current move
 *
 * @return int activeColumn
*/
int UltTicTacToe::getActiveBoardColumn()
{
  return this -> activeColumn;
}

/*
 * set current player to make a move
 *
 * @param char newPlayer - which player (X or O) will move next
*/
void UltTicTacToe::setCurrentPlayer(char newPlayer)
{
  if (newPlayer == 'X')
  {
    this -> currPlayer = 'X';
  }

  else if (newPlayer == 'O')
  {
    this -> currPlayer = 'O';
  }
  else
  {
    throw "Invalid player selection.";
  }
}

/*
 * get current player about to make a move
 *
 * @return char currPlayer - which player (X or O) will move next
*/
char UltTicTacToe::getCurrentPlayer()
{
  return this -> currPlayer;
}

/*
 * swap which player will make move next
*/
void UltTicTacToe::swapPlayer()
{
  if (this -> currPlayer == 'X')
  {
    this -> setCurrentPlayer('O');
  }

  else if (this -> currPlayer == 'O')
  {
    this -> setCurrentPlayer('X');
  }

  else
  {
    throw "Invalid player selection.";
  }
}

/*
 * set current player to make a move
 *
 * @param UltTicTacToe game - UltTicTacToe object
 * @param char currPlayer - current player
 * @param - which row, for all rows, to move on [a-i]
 * @param - which column, for all, to move on [1-9]
*/
void UltTicTacToe::ultMove(char currPlayer, char boardRow, char boardColumn)
{

  // validate input is a spot on the board
  char hSlots[9] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
  char vSlots[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

  int hIndex = -1;
  int vIndex = -1;

  for (int i = 0; i < 9; i++)
  {
    if (hSlots[i] == boardRow)
    {
      hIndex = i;
    }

    if (vSlots[i] == boardColumn)
    {
      vIndex = i;
    }
  }

  // make move on regular gameboard within active row and column
  this -> gameBoard[hIndex/3][vIndex/3].regMove(currPlayer, hIndex % 3, vIndex % 3);

  // print board
  this -> displayBoard();

  // see if someone won the game
  this -> checkWin(currPlayer);

  // swap whose turn it is
  this -> swapPlayer();

  // restrict board activity to row and column correlating with last move
  this -> restrictActiveBoard(hIndex % 3, vIndex % 3);

}

/*
 * print current game board
 *
 * @param UltTicTacToe masterBoard - given game board
*/
void UltTicTacToe::displayBoard()
{
  std::string xxx;

  cout << "     1   2   3      4   5   6      7   8   9  " << endl;
  cout << "   ___________________________________________" << endl;
  cout << "  |             ||             ||             " << endl;
  cout << "  |    |   |    ||    |   |    ||    |   |    " << endl;

  xxx += "a | ";
  xxx.append(this -> gameBoard[0][0].drawCellValues(gameBoard[0][0].board[0]));
  xxx += " || ";
  xxx.append(this -> gameBoard[0][1].drawCellValues(gameBoard[0][1].board[0]));
  xxx += " || ";
  xxx.append(this -> gameBoard[0][2].drawCellValues(gameBoard[0][2].board[0]));
  xxx += "\n";
  cout << xxx;

  cout << "  | ___|___|___ || ___|___|___ || ___|___|___ " << endl;
  cout << "  |    |   |    ||    |   |    ||    |   |    " << endl;

  xxx = "";
  xxx += "b | ";
  xxx.append(this -> gameBoard[0][0].drawCellValues(gameBoard[0][0].board[1]));
  xxx += " || ";
  xxx.append(this -> gameBoard[0][1].drawCellValues(gameBoard[0][1].board[1]));
  xxx += " || ";
  xxx.append(this -> gameBoard[0][2].drawCellValues(gameBoard[0][2].board[1]));
  xxx += "\n";
  cout << xxx;

  cout << "  | ___|___|___ || ___|___|___ || ___|___|___ " << endl;
  cout << "  |    |   |    ||    |   |    ||    |   |    " << endl;

  xxx = "";
  xxx += "c | ";
  xxx.append(this -> gameBoard[0][0].drawCellValues(gameBoard[0][0].board[2]));
  xxx += " || ";
  xxx.append(this -> gameBoard[0][1].drawCellValues(gameBoard[0][1].board[2]));
  xxx += " || ";
  xxx.append(this -> gameBoard[0][2].drawCellValues(gameBoard[0][2].board[2]));
  xxx += "\n";
  cout << xxx;

  cout << "  |    |   |    ||    |   |    ||    |   |    " << endl;
  cout << "  |             ||             ||             " << endl;
  cout << "  | ==========================================" << endl;
  cout << "  |             ||             ||             " << endl;
  cout << "  |    |   |    ||    |   |    ||    |   |    " << endl;

  xxx = "";
  xxx += "d | ";
  xxx.append(this -> gameBoard[1][0].drawCellValues(gameBoard[1][0].board[0]));
  xxx += " || ";
  xxx.append(this -> gameBoard[1][1].drawCellValues(gameBoard[1][1].board[0]));
  xxx += " || ";
  xxx.append(this -> gameBoard[1][2].drawCellValues(gameBoard[1][2].board[0]));
  xxx += "\n";
  cout << xxx;

  cout << "  | ___|___|___ || ___|___|___ || ___|___|___ " << endl;
  cout << "  |    |   |    ||    |   |    ||    |   |    " << endl;

  xxx = "";
  xxx += "e | ";
  xxx.append(this -> gameBoard[1][0].drawCellValues(gameBoard[1][0].board[1]));
  xxx += " || ";
  xxx.append(this -> gameBoard[1][1].drawCellValues(gameBoard[1][1].board[1]));
  xxx += " || ";
  xxx.append(this -> gameBoard[1][2].drawCellValues(gameBoard[1][2].board[1]));
  xxx += "\n";
  cout << xxx;

  cout << "  | ___|___|___ || ___|___|___ || ___|___|___ " << endl;
  cout << "  |    |   |    ||    |   |    ||    |   |    " << endl;

  xxx = "";
  xxx += "f | ";
  xxx.append(this -> gameBoard[1][0].drawCellValues(gameBoard[1][0].board[2]));
  xxx += " || ";
  xxx.append(this -> gameBoard[1][1].drawCellValues(gameBoard[1][1].board[2]));
  xxx += " || ";
  xxx.append(this -> gameBoard[1][2].drawCellValues(gameBoard[1][2].board[2]));
  xxx += "\n";
  cout << xxx;


  cout << "  |    |   |    ||    |   |    ||    |   |    " << endl;
  cout << "  |             ||             ||             " << endl;
  cout << "  | ==========================================" << endl;
  cout << "  |             ||             ||             " << endl;
  cout << "  |    |   |    ||    |   |    ||    |   |    " << endl;

  xxx = "";
  xxx += "g | ";
  xxx.append(this -> gameBoard[2][0].drawCellValues(gameBoard[2][0].board[0]));
  xxx += " || ";
  xxx.append(this -> gameBoard[2][1].drawCellValues(gameBoard[2][1].board[0]));
  xxx += " || ";
  xxx.append(this -> gameBoard[2][2].drawCellValues(gameBoard[2][2].board[0]));
  xxx += "\n";
  cout << xxx;

  cout << "  | ___|___|___ || ___|___|___ || ___|___|___ " << endl;
  cout << "  |    |   |    ||    |   |    ||    |   |    " << endl;

  xxx = "";
  xxx += "h | ";
  xxx.append(this -> gameBoard[2][0].drawCellValues(gameBoard[2][0].board[1]));
  xxx += " || ";
  xxx.append(this -> gameBoard[2][1].drawCellValues(gameBoard[2][1].board[1]));
  xxx += " || ";
  xxx.append(this -> gameBoard[2][2].drawCellValues(gameBoard[2][2].board[1]));
  xxx += "\n";
  cout << xxx;

  cout << "  | ___|___|___ || ___|___|___ || ___|___|___ " << endl;
  cout << "  |    |   |    ||    |   |    ||    |   |    " << endl;

  xxx = "";
  xxx += "i | ";
  xxx.append(this -> gameBoard[2][0].drawCellValues(gameBoard[2][0].board[2]));
  xxx += " || ";
  xxx.append(this -> gameBoard[2][1].drawCellValues(gameBoard[2][1].board[2]));
  xxx += " || ";
  xxx.append(this -> gameBoard[2][2].drawCellValues(gameBoard[2][2].board[2]));
  xxx += "\n";
  cout << xxx;

  cout << "  |    |   |    ||    |   |    ||    |   |    " << endl;
  cout << "  |             ||             ||             " << endl;
  cout << "\n";
}


/*
 * check if the player who just moved won
 *
 * @param char currentPlayer - current player
*/
void UltTicTacToe::checkWin(char currentPlayer)
{

  //vertical
  for (int y = 0; y < 3; y++)
  {
    if ((this -> gameBoard[0][y].getBoardStatus() != 'U') && this -> gameBoard[0][y].getBoardStatus() != 'T')
    {
      if ((this -> gameBoard[0][y].getBoardStatus() == this -> gameBoard[1][y].getBoardStatus())
      && (this -> gameBoard[1][y].getBoardStatus() == this -> gameBoard[2][y].getBoardStatus()))
      {
        win(currentPlayer);
      }
    }
  }


  //horizontal
  for (int x = 0; x < 3; x++)
  {
    if ((this -> gameBoard[x][0].getBoardStatus() != 'U') && (this -> gameBoard[x][0].getBoardStatus() != 'T'))
    {
      if ((this -> gameBoard[x][0].getBoardStatus() == this -> gameBoard[x][1].getBoardStatus())
      && (this -> gameBoard[x][1].getBoardStatus() == this -> gameBoard[x][2].getBoardStatus()))
      {
        win(currentPlayer);
      }
    }
  }


  //diagonals
  if ((this -> gameBoard[1][1].getBoardStatus() != 'U') && (this -> gameBoard[1][1].getBoardStatus() != 'T'))
  {
    if ((this -> gameBoard[0][0].getBoardStatus() == this -> gameBoard[1][1].getBoardStatus())
    && (this -> gameBoard[1][1].getBoardStatus() == this -> gameBoard[2][2].getBoardStatus()))
    {
      win(currentPlayer);
    }
  }

  if ((this -> gameBoard[1][1].getBoardStatus() != 'U') && (this -> gameBoard[1][1].getBoardStatus() != 'T'))
  {
    if ((this -> gameBoard[0][2].getBoardStatus() == this -> gameBoard[1][1].getBoardStatus())
    && (this -> gameBoard[1][1].getBoardStatus() == this -> gameBoard[2][0].getBoardStatus()))
    {
      win(currentPlayer);
    }
  }
}

/*
 * restrict gameplay to target row and column based on last move
 *
 * @param int row - {0, 1, 2} row to restrict gameplay to
 * @param int column - {0, 1, 2} column to restrict gameplay to
*/
void UltTicTacToe::restrictActiveBoard(int row, int column)
{

  // if the target board is already filled, then next player can move anywhere
  if ((this -> gameBoard[row][column].getBoardStatus() == 'T')
  || (this -> gameBoard[row][column].getBoardStatus() == 'X')
  || (this -> gameBoard[row][column].getBoardStatus() == 'O'))
  {
    this -> freeActiveBoard();
  }

  else
  {
    this -> setActiveBoardRow(row);
    this -> setActiveBoardColumn(column);
  }

}

/*
 * allow next move to be anywhere on the board
*/
void UltTicTacToe::freeActiveBoard()
{
  this -> setActiveBoardRow(-1);
  this -> setActiveBoardColumn(-1);
}

/*
 * check to see if move input from player is valid position for play
 *
 * @param char boardRow - a-i row value
 * @param char boardColumn - 1-9 column value
 *
 * @return true if valid move, false if not
*/
bool UltTicTacToe::isValidMove(char boardRow, char boardColumn)
{

  // make sure input is indeed a-i and 1-9, then grab their value indices
  char hSlots[9] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
  char vSlots[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

  bool isBoardSlot = false;
  bool isRowSlot, isColumnSlot;
  int rowIndex, columnIndex;


  for (int i = 0; i < 9; i++)
  {
    if (boardRow == hSlots[i])
    {
      isRowSlot = true;
      rowIndex = i;
    }
  }

  for (int j = 0; j < 9; j++)
  {
    if (boardColumn == vSlots[j])
    {
      isColumnSlot = true;
      columnIndex = j;
    }
  }


  if (!isRowSlot || !isColumnSlot)
  {
    return false;
  }

  // check if input move is within restricted gameplay bounds
  char validRows[3], validColumns[3];
  bool allRowsOpen = false;
  bool allColumnsOpen = false;

  if (this -> getActiveBoardRow() == -1)
  {
    allRowsOpen = true;
  }

  else if (this -> getActiveBoardRow() == 0)
  {
    validRows[0] = 'a';
    validRows[1] = 'b';
    validRows[2] = 'c';
  }
  else if (this -> getActiveBoardRow() == 1)
  {
    validRows[0] = 'd';
    validRows[1] = 'e';
    validRows[2] = 'f';
  }
  else if (this -> getActiveBoardRow() == 2)
  {
    validRows[0] = 'g';
    validRows[1] = 'h';
    validRows[2] = 'i';
  }

  if (this -> getActiveBoardRow() == -1)
  {
    allColumnsOpen = true;
  }

  else if (this -> getActiveBoardColumn() == 0)
  {
    validColumns[0] = '1';
    validColumns[1] = '2';
    validColumns[2] = '3';
  }
  else if (this -> getActiveBoardColumn() == 1)
  {
    validColumns[0] = '4';
    validColumns[1] = '5';
    validColumns[2] = '6';
  }
  else if (this -> getActiveBoardColumn() == 2)
  {
    validColumns[0] = '7';
    validColumns[1] = '8';
    validColumns[2] = '9';
  }

  bool validRow = false;
  bool validColumn = false;

  for (int i = 0; i < 3; i++)
  {
    if (boardRow == validRows[i])
    {
      validRow = true;
    }
  }

  for (int i = 0; i < 3; i++)
  {
    if (boardColumn == validColumns[i])
    {
      validColumn = true;

    }
  }



  if (!allRowsOpen && !allColumnsOpen)
  {
    if (!validRow || !validColumn)
    {
      return false;
    }
  }

  // make sure the cell is empty
  if(this -> gameBoard[rowIndex/3][columnIndex/3].board[rowIndex%3][columnIndex%3].getCellStatus() != 'e')
  {
    return false;
  }

  return true;

}

/*
 * present win message to player
 *
 * @param char currentPlayer - current player
*/
void UltTicTacToe::win(char currentPlayer)
{
  cout << "Congrats " << currentPlayer << ", you won!\n" << endl;
  std::string finished = "finished";
  this -> setGameStatus(finished);
}

/*
 * Menu:
 * Print rules.txt
 * Gamplay
 * - initialize board -> get move, validate, make move, repeat
 * Exit
*/

int main()
{
  int option = -1;
  cout << "Welcome; to Ultimate Tic Tac Toe! Please enter an option's number: " << endl;
  cout << "1 - Play" << endl;
  cout << "2 - Rules" << endl;
  cout << "3 - Exit" << endl;
  cin >> option;
  cout << "\n";

  while (option != 3)
  {
    UltTicTacToe game;

    if (option == 2)
    {
    std::cout << std::ifstream("rules.txt").rdbuf() << endl;
    }

    if (option == 1)
    {

      cout << "Have fun!\n\n";

      std::string running = "running";
      game.setGameStatus(running);
      game.setCurrentPlayer('X');
      game.displayBoard();


      while(game.getGameStatus() == "running")
      {
        string moveLoc = "xx";
        cout << game.getCurrentPlayer() << "\'s move:   ";
        cin >> moveLoc;
        cout << "\n";

        while(!game.isValidMove(moveLoc[0], moveLoc[1]))
        {
          game.displayBoard();
          cout << "Invalid move! Please enter a valid move:  " ;
          cin >> moveLoc;
          cout << "\n";
        }

        game.ultMove(game.getCurrentPlayer(), moveLoc[0], moveLoc[1]);

      }

    }

    cout << "What would you like to do now? Please enter an option's number: " << endl;
    cout << "1 - Play" << endl;
    cout << "2 - Rules" << endl;
    cout << "3 - Exit" << endl;
    cin >> option;
  }

  cout << "Thanks for playing!" << endl;

  return 0;
}
