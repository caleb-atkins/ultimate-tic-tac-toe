/**********************************************************************
cell.cpp - object for one single cell within a regular tic-tac-toe grid
**********************************************************************/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

#include "cell.h"

using namespace std;

// Cell constructor
Cell::Cell()
{
  // set default cell status to empty
  this -> cellStatus = 'e';
}

// Cell destructor
Cell::~Cell(){}

/*
 * @desc set Cell object to either be empty or contain an X/O value
 *
 * @param char new CellStatus - value to be placed inside of given cell
*/
void Cell::setCellStatus(char newCellStatus)
{
  if (newCellStatus == 'e'){this -> cellStatus = 'e';}
  else if (newCellStatus == 'X'){this -> cellStatus = 'X';}
  else if (newCellStatus == 'O'){this -> cellStatus = 'O';}
  else {throw "Invalid cell status submitted.";}
}

/*
 * @desc return current value in given cell
 *
 * @return current value held inside given cell
*/
char Cell::getCellStatus()
{
  return this -> cellStatus;
}
