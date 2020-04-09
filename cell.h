/*****************************************************************
cell.h - cell.cpp header file with class attributes and prototypes
*****************************************************************/

#ifndef _cell_h
#define _cell_h

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

/*
 * Cell class provides functions and status attribute for
 * operating on one cell within a regular tic-tac-toe grid
*/
class Cell
{

  private:

    // character indicating value in a given cell ('e' indicates an empty cell)
    char cellStatus;

  public:

    Cell();
    ~Cell();
    
    void setCellStatus(char newCellStatus);
    char getCellStatus();

};

#endif
