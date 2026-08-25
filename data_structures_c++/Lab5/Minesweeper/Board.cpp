#include "Board.h"
#include <Windows.h>
#include <iostream>
using std::cout;
using std::endl;

//sourced from https://cplusplus.com/reference/cstdlib/rand/
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


/**********************
*
* Function: Default Ctor
*
* Purpose: Set the default
* values of member variables,
* which is a default 2D array,
* and all others to 0. m_revealed
* should be -1, as a reveal check
* should not immediately be able
* to be true.
*
************************/
Board::Board() : m_array(Array2D<Cell>()), m_cols(0), m_rows(0), m_diff(0), m_flags(0), m_guess(0), m_revealed(-1)
{}

/**********************
*
* Function: Value Ctor : Array
*
* Purpose: using the provided array,
* determine the column count,
* row count, difficulty, and 
* mine count. 
*
************************/
Board::Board(Array2D<Cell> arr) : m_array(arr), m_cols(arr.getColumns()), m_rows(arr.getRow()), m_diff(0), m_flags(0), m_guess(0), m_revealed(-1)
{
	switch (arr.getColumns())								//using the columns provided, the difficulty can be determined
	{
	case 10:									//column count for beginner difficulty
		m_diff = BEGINNER;
		m_flags = 10;
		m_revealed = m_rows * m_cols - m_flags;
		break;
	case 16:									//column count for intermediate difficulty
		m_diff = INTERMEDIATE;
		m_flags = 40;
		m_revealed = m_rows * m_cols - m_flags;
		break;
	case 30:									//column count for hard difficulty
		m_diff = HARD;
		m_flags = 100;
		m_revealed = m_rows * m_cols - m_flags;
		break;
	default:									//something went wrong
		m_diff = 4;
		m_flags = 0;
	
	}

}


/**********************
*
* Function: Value Ctor : integers
*
* Purpose: using the provided row
* and column values,determine difficulty,
* and mine count, and create an array
* of specified length/width. 
*
************************/
Board::Board(int rows, int cols) : m_array(Array2D<Cell>(rows, cols)), m_cols(cols), m_rows(rows), m_diff(0), m_flags(0), m_guess(0), m_revealed(-1)
{
	switch(cols)								//using the columns provided, the difficulty can be determined
	{
	case 10:									//column count for beginner difficulty
		m_diff = BEGINNER;
		m_flags = 10;
		m_revealed = m_rows * m_cols - m_flags;
		break;
	case 16:									//column count for intermediate difficulty
		m_diff = INTERMEDIATE;
		m_flags = 40;
		m_revealed = m_rows * m_cols - m_flags;
		break;
	case 30:									//column count for hard difficulty
		m_diff = HARD;
		m_flags = 100;
		m_revealed = m_rows * m_cols - m_flags;
		break;
	default:									//something went wrong
		m_diff = 4;
		m_flags = 0;

	}

}

/**********************
*
* Function: Move Ctor 
*
* Purpose: using the provided 
* board, copy over the array, 
* column count, row count,
* difficulty, and mine count
*
************************/
Board::Board(Board&& copy) noexcept : m_array(copy.m_array), m_cols(copy.m_cols),
							m_rows(copy.m_rows), m_diff(copy.m_diff),
							m_flags(copy.m_flags), m_guess(copy.m_guess),
							m_revealed(copy.m_revealed)
{}

/**********************
*
* Function: Copy Ctor
*
* Purpose: using the provided
* board, copy over the array,
* column count, row count,
* difficulty, and mine count
*
************************/
Board::Board(const Board& copy) : m_array(copy.m_array), m_cols(copy.m_cols),
								m_rows(copy.m_rows), m_diff(copy.m_diff),
								m_flags(copy.m_flags), m_guess(copy.m_guess),
								m_revealed(copy.m_revealed)
{}

/**********************
*
* Function: Move Assignment Operator
*
* Purpose: using the provided
* board, copy over the array,
* column count, row count,
* difficulty, and mine count
*
************************/
Board& Board::operator = (Board&& rhs) noexcept
{
	if (this != &rhs) {
		m_array = rhs.m_array;
		m_cols = rhs.m_cols;
		m_rows = rhs.m_rows;
		m_diff = rhs.m_diff;
		m_flags = rhs.m_flags;
		m_guess = rhs.m_guess;
		m_revealed = rhs.m_revealed;
	}

	return *this;
}

/**********************
*
* Function: Destructor
*
* Purpose: reset members
* back to initial values
*
************************/
Board::~Board()
{
	m_array.setRows(0);
	m_cols = 0;
	m_rows = 0;
	m_diff = 0;
	m_flags = 0;
	m_guess = 0;
	m_revealed = 0;
}

/**********************
*
* Function: Copy Assignment Operator
*
* Purpose: using the provided
* board, copy over the array,
* column count, row count,
* difficulty, and mine count
*
************************/
Board& Board::operator = (const Board& rhs) 
{
	if (this != &rhs) {
		m_array = rhs.m_array;
		m_cols = rhs.m_cols;
		m_rows = rhs.m_rows;
		m_diff = rhs.m_diff;
		m_flags = rhs.m_flags;
		m_guess = rhs.m_guess;
		m_revealed = rhs.m_revealed;
	}

	return *this;
}

/********************************
*
* Function: resetBoard
*
* Purpose: Reset the board to 
* default values
*
********************************/
void Board::resetBoard()						//resets board to default values (using m_rows and m_cols)
{
	m_array.setRows(0);							//delete the existing array

	m_array.setRows(m_rows);
	m_array.setColumns(m_cols);
	m_guess = 0;
	m_revealed = m_rows * m_cols - m_flags;
}

/********************************
*
* Function: setBeginner
*
* Purpose: Set the board to beginner
* difficulty. There should be 10 flags
* for 10 mines, and the board should be
* 10 rows by 10 columns. 
*
********************************/
void Board::setBeginner()						//set a beginner board (10x10, 10 mines)
{
	m_diff = BEGINNER;
	m_flags = 10;
	m_rows = 10;
	m_cols = 10;
	resetBoard();

}

/********************************
*
* Function: setIntermediate
*
* Purpose: Set the board to intermediate
* difficulty. There should be 40 flags
* for 40 mines, and the board should be
* 16 rows by 16 columns.
*
********************************/
void Board::setIntermediate()					//set an intermediate board (16x16, 40 mines)
{
	m_diff = INTERMEDIATE;
	m_flags = 40;
	m_rows = 16;
	m_cols = 16;
	resetBoard();
}

/********************************
*
* Function: setHard
*
* Purpose: Set the board to hard
* difficulty. There should be 100 flags
* for 100 mines, and the board should be
* 16 rows by 30 columns.
*
********************************/
void Board::setHard()							//create a hard mode board (16x30, 100 mines)
{
	m_diff = HARD;
	m_flags = 100;
	m_rows = 16;
	m_cols = 30;
	resetBoard();

}

/********************************
*
* Function: populateBoard
*
* Purpose: Set up the board. Add 
* bombs based on difficulty, and sporadically
* around the board. Once this has been
* done, reveal the board. The starting
* point can never be a bomb. 
*
********************************/
void Board::populateBoard(int row, int col)		//populate the board with mines and numbers
{

	/* initialize random seed: */
	srand(time(NULL));
	int rows, cols, placed = 0;
	while (placed < m_flags) {
		rows = rand() % m_rows;
		cols = rand() % m_cols;

		if (!(m_array[rows][cols].m_bomb || (rows == row && cols == col))) {
			m_array[rows][cols].m_bomb = true;
	
			if (cols + 1 < m_cols)
				m_array[rows][cols + 1].m_val += 1;							//increment right

			if (rows + 1 < m_rows && cols + 1 < m_cols)
				m_array[rows + 1][cols + 1].m_val += 1;						//increment down + right

			if(rows + 1 < m_rows)
				m_array[rows + 1][cols].m_val += 1;							//increment down

			if (rows + 1 < m_rows && cols - 1 > 0)
				m_array[rows + 1][cols - 1].m_val += 1;						//increment down + left
		
			if (cols - 1 >= 0)
				m_array[rows][cols - 1].m_val += 1;							//increment left

			if (rows - 1 >= 0 && cols - 1 >= 0)
				m_array[rows - 1][cols - 1].m_val += 1;						//increment up + left

			if (rows - 1 >= 0)
				m_array[rows - 1][cols].m_val += 1;							//increment up

			if (rows - 1 >= 0 && cols + 1 < m_cols)
				m_array[rows - 1][cols + 1].m_val += 1;						//increment up + right

			placed++;
		}
	}

	floodFill(row, col);
}

/********************************
*
* Function: getFlags
*
* Purpose: Return the amount of flags 
* left to place
* 
********************************/
int Board::getFlags()
{
	return m_flags;
}

/********************************
*
* Function: setFlag
*
* Purpose: Set a flag on a hidden cell.
* If the cell is revealed, or if the
* cell already has a flag, then do 
* nothing.
*
********************************/
bool Board::setFlag(int row, int col)
{
	bool retVal = false;
	
	if (m_array[row][col].m_state == HIDDEN) {				//check to see if a cell is hidden (don't flag revealed cells)
		if (m_flags > 0) {									//check to see if there are flags left to place
			m_array[row][col].m_state = FLAGGED;
			m_flags -= 1;									//flag this cell and subtract one from the flags member variable
			if (m_array[row][col].m_bomb) {
				m_guess += 1;								//if this put a flag on the bomb, add one to the total correct guesses
			}
		}
	}
	switch (m_diff)
	{
	case BEGINNER:
		if (m_guess == 10)
			retVal = true;										//all 10 bombs have been found in easy mode
		break;
	case INTERMEDIATE:
		if (m_guess == 40)										//all 40 bombs have been found in intermediate mode
			retVal = true;
		break;
	case HARD:
		if (m_guess == 100)										//all 100 bombs have been found in hard mode
			retVal = true;
		break;
	}
	
	return retVal;
}

/********************************
*
* Function: unsetFlag
*
* Purpose: Take away the status of
* a flagged cell. If a flag is removed,
* add one back to the available flags. 
*
********************************/
void Board::unsetFlag(int row, int col) {
	if (m_array[row][col].m_state == FLAGGED) {				//check to see if a cell has been flagged
		m_array[row][col].m_state = HIDDEN;
		m_flags += 1;										//remove the flag and add one to m_flag
		if (m_array[row][col].m_bomb) {
			m_guess -= 1;									//if this removed a flag off a bomb, subtract one from the total guessed
		}
	}
}
/********************************
*
* Function: guessBoard
*
* Purpose: Used for guessing if a cell
* in the board is a bomb or not. 
* Fills out the board if a bomb is not
* hit, and reveals the full board if 
* a bomb is hit. 
*
********************************/
bool Board::guessBoard(int row, int col)		//return if the input given was a bomb or not, calls floodFill or revealBoard
{
	if (m_array[row][col].m_state == HIDDEN)		//skip checking a revealed or flagged cell
	{
		floodFill(row, col);
	}
	return m_array[row][col].m_bomb;
}

/********************************
*
* Function: floodFill
*
* Purpose: Fill out the board until 
* number values are encountered. 
* This function recursively reveals
* every empty cell up to and including
* cells with a numberic value. This 
* should not reveal any bombs. 
*
*
********************************/
void Board::floodFill(int row, int col)
{
	
	if (!m_array[row][col].m_bomb) {
		m_revealed -= 1;
		if (m_array[row][col].m_state != FLAGGED)			//only reveal a non-flagged cell
			m_array[row][col].m_state = REVEALED;

		if (m_array[row][col].m_val == 0) {					//check to see if there are bombs around this cell

			if (row - 1 >= 0 && m_array[row - 1][col].m_state != REVEALED)								//check above
				floodFill(row - 1, col);
			if (row - 1 >= 0 && col + 1 < m_cols && m_array[row - 1][col + 1].m_state != REVEALED)		//check above and right
				floodFill(row - 1, col + 1);
			if (col + 1 < m_cols && m_array[row][col + 1].m_state != REVEALED)							//check right
				floodFill(row, col + 1);
			if (row + 1 < m_rows && col + 1 < m_cols && m_array[row + 1][col + 1].m_state != REVEALED)	//check below and right
				floodFill(row + 1, col + 1);
			if (row + 1 < m_rows && m_array[row + 1][col].m_state != REVEALED)							//check below
				floodFill(row + 1, col);
			if (row + 1 < m_rows && col - 1 >= 0 && m_array[row + 1][col - 1].m_state != REVEALED)		//check below and left
				floodFill(row + 1, col - 1);
			if (col - 1 >= 0 && m_array[row][col - 1].m_state != REVEALED)								//check left
				floodFill(row, col - 1);
			if (row - 1 >= 0 && col - 1 >= 0 && m_array[row - 1][col - 1].m_state != REVEALED)			//check above and left
				floodFill(row - 1, col - 1);
		}
	}
}

/********************************
* S
* Function: revealBoard
* 
* Purpose: reveal every cell on
* the board.
* 
* 
********************************/
void Board::revealBoard()
{
	for (int i = 0; i < m_rows; ++i) {
		for (int j = 0; j < m_cols; ++j) {
			m_array[i][j].m_state = REVEALED;
		}
	}
}

/********************************
*
* Function: getCell
*
* Purpose: return a const cell type.
* This should allow the state of
* the cell to be determined. 
*
*
********************************/
const Cell Board::getCell(int row, int col)
{
	return m_array[row][col];
}

/**********************
*
* Function: getVictory
*
* Purpose: return a true
* if all squares that can
* be revealed, are revealed.
*
************************/
bool Board::getVictory() {
	return m_revealed == 0;
}


void Board::DisplayBoard()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (m_diff) {
		case BEGINNER:
			cout << "  0123456789" << endl;
			break;
		case INTERMEDIATE:
			cout << "  0123456789ABCDEF" << endl;
			break;
		case HARD:
			cout << "  0123456789ABCDEFGHIJKLMNOPQRST" << endl;
			break;
	}
	
	for (int i = 0; i < m_rows; ++i) {
		char o;
		if (i < 10) {
			o = i + 48;
			cout << o << " ";
		}
		else {
			o = i + 55;
			cout << o << " ";
		}

		for (int j = 0; j < m_cols; ++j) {
			cout << m_array[i][j];
			SetConsoleTextAttribute(hConsole, 15);
		}
		cout << endl;
	}

}