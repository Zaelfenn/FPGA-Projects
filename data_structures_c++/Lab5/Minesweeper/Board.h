/********************************************************
*
* Date created: April 17th, 2024
*
*
* Author: Zaelfenn Sandow
*
* Purpose: This file acts as the declaration of the board class,
* which is a friend of the cell class. The reason that these classes
* are friends is because it does not make sense to have a board
* without cells, or a cell without a board. A cell should not
* be created outside of the context of a board. The board should 
* be a two dimensional array of cells, and the cells should be default
* value until an input is given. The board should then populate
* with "random" bombs.
*
*********************************************************/

#pragma once

#include "Cell.h"
#include "myArray2D.h"

class Minesweeper;
class Cell;
/**********************************
*
* Class: Board
*
* Manager functions:
*		default ctor
*		value ctor
*		copy ctor
*		move ctor
*		copy assignment operator
*		move assignment operator
*		dtor
*
* member functions:
*		resetBoard
*		setBeginner
*		setIntermediate
*		setHard
*		populateBoard
*		guessBoard
*		getFlags
*		setFlag
*		getCell
* 
*
*
***********************************/
class Board {
	friend class Cell;
	friend class Minesweeper;
private:
	Board();									//default constructor
	Board(Array2D<Cell> arr);					//value constructor given an array of cells
	Board(int rows, int cols);					//value constructor given a set of rows and columns 
	Board(Board&& copy)noexcept;				//move constructor
	Board(const Board& copy);					//copy constructor
	Board& operator = (Board&& rhs)noexcept;	//move assignment operator
	Board& operator = (const Board& rhs);		//copy assignment operator

	~Board();									//dtor

	void resetBoard();							//resets board to default values (using m_rows and m_cols)

	void setBeginner();							//set a beginner board (10x10, 10 mines)
	void setIntermediate();						//set an intermediate board (16x16, 40 mines)
	void setHard();								//create a hard mode board (16x30, 100 mines)

	void populateBoard(int row, int col);		//populate the board with mines and numbers
		
	bool guessBoard(int row, int col);			//return if the input given was a bomb or not, calls floodFill or revealBoard

	int getFlags();								//return the number of remaining mines
	bool setFlag(int row, int col);				//set a flag on this row/column 
	void unsetFlag(int row, int col);			//take a flag off a flagged cell

	const Cell getCell(int row, int col);		//return a cell at a specific point

	bool getVictory();							//return a true on revealed == 0


	void DisplayBoard();						//display the board
	void floodFill(int row, int col);			//reveal the board recursively
	void revealBoard();							//reveal the board all at once
	

	Array2D<Cell> m_array;						//"board"
	int m_rows;									//board rows
	int m_cols;									//board columns
	int m_diff;									//difficulty settings
	int m_flags;								//count of flags to place on mines
	int m_guess;								//correct amount of flag placements
	int m_revealed;								//amount of revealed squares
};

enum{BEGINNER, INTERMEDIATE, HARD};