/********************************************************
*
* Date created: April 17th, 2024
*
*
* Author: Zaelfenn Sandow
*
* Purpose: This file acts as the declaration of the cell class,
* which is a friend of the board class. The reason that these classes
* are friends is because it does not make sense to have a board 
* without cells, or a cell without a board. A cell should not
* be created outside of the context of a board. A cell will
* display a certain way, based on the state, whether it is a bomb,
* and what the number contained inside is. 
*
*********************************************************/

#pragma once
#ifndef ostream
#include <ostream>
using std::ostream;
#endif

class Board;
/**********************************
* 
* Class: Cell
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
*		getState
* 
* 
***********************************/
class Cell {
	friend class Board;
public:
	friend ostream& operator << (ostream& out, const Cell& rhs);
//private:
	Cell();										//default constructor
	Cell(int val, bool bomb, int state);		//value constructor
	Cell(Cell&& copy)noexcept;							//move constructor
	Cell(const Cell& copy);						//copy constructor
	Cell& operator = (Cell&& rhs)noexcept;				//move assignment operator
	Cell& operator = (const Cell& rhs);			//copy assignment operator
	~Cell();									//dtor

	int m_val;						//value contained (how many bombs are around)
	bool m_bomb;					//whether or not this cell contains a bomb
	int m_state;					//whether the cell is revealed, hidden, or flagged
};

enum{HIDDEN, REVEALED, FLAGGED};