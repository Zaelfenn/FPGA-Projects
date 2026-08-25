/********************************************************
*
* Date created: April 17th, 2024
*
*
* Author: Zaelfenn Sandow
*
* Purpose: This file declares the class of Minesweeper. Using
* a board, the game of minesweeper should be entirely localized
* to this class. 
*
*********************************************************/

#pragma once

#include "Board.h"
class Board;

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
*
* member functions:
*		Start
*		Display
*
*
*
***********************************/
class Minesweeper {
	friend class Board;
public:
	Minesweeper();											//default ctor
	Minesweeper(Minesweeper&& copy)noexcept;				//move ctor
	Minesweeper(const Minesweeper& copy);					//copy ctor
	Minesweeper& operator = (Minesweeper&& rhs)noexcept;	//move assignment operator
	Minesweeper& operator = (const Minesweeper& rhs);		//copy assignment operator

	~Minesweeper();											//dtor

	void Start();											//start the game
	void Display();											//display the board

	
	void Reset();											//reset the game


private:

	Board m_board;
	bool m_victory;
	bool m_fail;
};