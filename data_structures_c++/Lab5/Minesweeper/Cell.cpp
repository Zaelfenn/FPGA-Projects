#include "Cell.h"
#include <Windows.h>

/**********************
* 
* Function: Default Ctor
* 
* Purpose: Set the default
* values of member variables,
* including value to 0, bomb
* to false, and state to hidden.
* 
************************/
Cell::Cell() : m_val(0), m_bomb(false), m_state(HIDDEN)
{}

/**********************
*
* Function: Value Ctor
*
* Purpose: Set the member
* variables to the passed
* in values.
*
************************/
Cell::Cell(int val, bool bomb, int state) : m_val(val), m_bomb(bomb), m_state(state)
{}


/**********************
*
* Function: Move Ctor
*
* Purpose: copy the values
* over from one cell to 
* another
*
************************/
Cell::Cell(Cell&& copy) noexcept : m_val(copy.m_val), m_bomb(copy.m_bomb), m_state(copy.m_state)
{}

/**********************
*
* Function: Copy Ctor
*
* Purpose: copy the values
* over from one cell to
* another
*
************************/
Cell::Cell(const Cell& copy) : m_val(copy.m_val), m_bomb(copy.m_bomb), m_state(copy.m_state)
{}

/**********************
*
* Function: Destructor
*
* Purpose: Set member 
* variables back to 
* default values
*
************************/
Cell::~Cell()
{
	m_val = 0;
	m_bomb = false;
	m_state = HIDDEN;
}

/**********************
*
* Function: Move assignment
*
* Purpose: copy the values
* over from one cell to
* another
*
************************/
Cell& Cell::operator=(Cell&& rhs)noexcept
{
	m_val = rhs.m_val;
	m_bomb = rhs.m_bomb;
	m_state = rhs.m_state;

	return *this;
}

/**********************
*
* Function: Copy assignment
*
* Purpose: copy the values
* over from one cell to
* another
*
************************/
Cell& Cell::operator=(const Cell& rhs)
{
	m_val = rhs.m_val;
	m_bomb = rhs.m_bomb;
	m_state = rhs.m_state;

	return *this;
}

/**********************
*
* Function: overloaded stream operator
*
* Purpose: output a Cell 
* with a specific color and
* shape depending on the 
* state and value of the cell.
*
************************/
ostream& operator << (ostream& out, const Cell& rhs)
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (rhs.m_state) {
	case HIDDEN:
		SetConsoleTextAttribute(hConsole, 8);
		out << "#";
		break;
	case REVEALED:
		if (rhs.m_bomb) {
			SetConsoleTextAttribute(hConsole, 4);
			out << "X";
		}
		else {
			char temp = 177;
			switch (rhs.m_val) {
				case 0:
					SetConsoleTextAttribute(hConsole, 8);
					out << temp;
					break;
				case 1:
					SetConsoleTextAttribute(hConsole, 10);
					out << rhs.m_val;
					break;
				case 2:
					SetConsoleTextAttribute(hConsole, 11);
					out << rhs.m_val;
					break;
				case 3:
					SetConsoleTextAttribute(hConsole, 5);
					out << rhs.m_val;
					break;
				case 4:
					SetConsoleTextAttribute(hConsole, 13);
					out << rhs.m_val;
					break;
				case 5:
					SetConsoleTextAttribute(hConsole, 2);
					out << rhs.m_val;
					break;
				case 6:
					SetConsoleTextAttribute(hConsole, 9);
					out << rhs.m_val;
					break;
				case 7:
					SetConsoleTextAttribute(hConsole, 6);
					out << rhs.m_val;
					break;
				case 8:
					SetConsoleTextAttribute(hConsole, 12);
					out << rhs.m_val;
					break;
			}
			
		}
		break;
	case FLAGGED:
		SetConsoleTextAttribute(hConsole, 14);
		out << "F";
		break;
	default:
		out << "?";
	}
	return out;
}