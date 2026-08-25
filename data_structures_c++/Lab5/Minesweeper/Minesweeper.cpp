#include "Minesweeper.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <stdlib.h>

/*************************
* 
* Function: Default Ctor
* 
* Purpose: Set the default
* values. m_board will be
* default board, m_fail 
* and m_victory should be
* false.
* 
*************************/
Minesweeper::Minesweeper() : m_board(Board()), m_fail(false), m_victory(false)									//default ctor
{}

/*************************
*
* Function: Move Ctor
*
* Purpose: Is a move
* constructor
*
*************************/
Minesweeper::Minesweeper(Minesweeper&& copy)noexcept : m_board(copy.m_board), m_fail(copy.m_fail),				//move ctor
														m_victory(copy.m_fail)
{}

/*************************
*
* Function: Copy Ctor
*
* Purpose: Is a copy
* constructor
*
*************************/
Minesweeper::Minesweeper(const Minesweeper& copy) : m_board(copy.m_board), m_fail(copy.m_fail),					//copy ctor
													m_victory(copy.m_fail)					
{}


/*************************
*
* Function: Move Assignment
*
* Purpose: Sets the left hand
* side of an assignment operator
* to the right hand side by changing
* the values of member variables.
*
*************************/
Minesweeper& Minesweeper::operator = (Minesweeper&& rhs)noexcept												//move assignment operator
{
	if (this != &rhs) {
		m_board = rhs.m_board;
		m_fail = rhs.m_fail;
		m_victory = rhs.m_victory;
	}
	return *this;
}

/*************************
*
* Function: Copy Assignment
*
* Purpose: Sets the left hand
* side of an assignment operator
* to the right hand side by changing
* the values of member variables.
*
*************************/
Minesweeper& Minesweeper::operator = (const Minesweeper& rhs)													//copy assignment operator
{
	if (this != &rhs) {
		m_board = rhs.m_board;
		m_fail = rhs.m_fail;
		m_victory = rhs.m_victory;
	}
	return *this;
}

/*************************
*
* Function: Dtor
*
* Purpose: Resets all
* values to default. This 
* means resetting the board, 
* and setting both m_fail and
* m_victory to false.
*
*************************/
Minesweeper::~Minesweeper()																						//dtor
{
	Reset();
}

/*************************
*
* Function: Start
*
* Purpose: Starts the game.
* Sets the difficulty, and 
* manages user input. 
*
*************************/
void Minesweeper::Start()																						//start the game
{
	char minesweeping = 'Y';
	while (minesweeping == 'Y') {
		system("cls");

		cout << "Welcome to Minesweeper!" << endl;

		cout << "Please pick a difficulty:\n" <<
			"1. Easy (10x10 board, 10 mines)\n" <<
			"2. Intermediate (16x16 board, 40 mines)\n" <<
			"3. Hard (16x30 board, 100 mines)" << endl;
		int choice = 0;
		while (choice > 3 || choice < 1)
			cin >> choice;

		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());

		switch (choice) {
		case 1:
			m_board.setBeginner();
			break;
		case 2:
			m_board.setIntermediate();
			break;
		case 3:
			m_board.setHard();
			break;
		}


		char type = ' ', x_c, y_c;
		char buffer[6];
		char copy[6];
		int x, y;
		Display();
		bool loop = true;
		while (loop) {
			cin.getline(buffer, 6);								//format: U x,y			= 5 chars, + 1 for nullptr
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			if (buffer[1] == ',') {
				x_c = *(strtok(buffer, ","));
				y_c = *(strtok(NULL, "\0"));

				x_c = toupper(x_c);
				y_c = toupper(y_c);

				loop = false;

			}
			else
				cout << "Error in formatting. Please enter only the coordinates you wish to reveal." << endl;
		}





		if (x_c > 64)
			x = x_c - 55;
		else
			x = x_c - 48;

		if (y_c > 64)
			y = y_c - 55;
		else
			y = y_c - 48;

		while (x > m_board.m_cols || x < 0) {
			cout << "Please enter a new x-coordinate: ";
			cin >> x_c;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());

			if (x_c > 64)
				x = x_c - 55;
			else
				x = x_c - 48;
		}

		while (y > m_board.m_cols || y < 0) {
			cout << "Please enter a new y-coordinate: ";

			cin >> y_c;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());

			if (y_c > 64)
				y = y_c - 55;
			else
				y = y_c - 48;
		}

		m_board.populateBoard(y, x);

		while (!m_fail && !m_victory) {
			Display();
			loop = true;
			while (loop) {
				cin.getline(buffer, 6);								//format: U x,y			= 5 chars, + 1 for nullptr
				strcpy(copy, buffer);
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				if (buffer[1] == ' ' && buffer[3] == ',') {
					type = *(strtok(buffer, " "));
					x_c = *(strtok(NULL, ","));
					y_c = *(strtok(NULL, "\0"));

					type = toupper(type);
					x_c = toupper(x_c);
					y_c = toupper(y_c);

					switch (type) {

					case 'U':
						loop = false;
						break;
					case 'M':
						loop = false;
						break;
					default:
						cout << "Please enter a valid command.\n" << endl;
					}


				}
				else if (buffer[1] == ',')
				{
					x_c = *(strtok(buffer, ","));
					y_c = *(strtok(NULL, "\0"));

					x_c = toupper(x_c);
					y_c = toupper(y_c);

					loop = false;

				}
				else
					cout << "Error in formatting. Please follow the format guide of U x,y or M x,y or x,y" << endl;
			}

			if (x_c > 64)
				x = x_c - 55;
			else
				x = x_c - 48;

			if (y_c > 64)
				y = y_c - 55;
			else
				y = y_c - 48;





			while (x > m_board.m_cols || x < 0) {
				cout << "Please enter a new x-coordinate: ";
				cin >> x_c;
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());

				if (x_c > 64)
					x = x_c - 55;
				else
					x = x_c - 48;
			}

			while (y > m_board.m_rows || y < 0) {
				cout << "Please enter a new y-coordinate: ";

				cin >> y_c;
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());

				if (y_c > 64)
					y = y_c - 55;
				else
					y = y_c - 48;
			}



			if (copy[1] == ' ' && copy[3] == ',') {
				switch (type) {

				case 'U':
					m_board.unsetFlag(y, x);										//unmarks the position
					break;
				case 'M':
					m_victory = m_board.setFlag(y, x);								//marks or unmarks the position
					break;
				default:															//should NOT do anything otherwise
					break;
				}
			}
			else
			{
				m_fail = m_board.guessBoard(y, x);									//guess the position, and check if a bomb was hit
				m_victory = m_board.getVictory();									//check if all non-bomb squares have been uncovered
			}

		}
		
		if (m_fail) {
			system("cls");
			cout << "You lost. Mine found at: " << x_c << "," << y << endl;

			cout << "\nYour board:\n";
			m_board.DisplayBoard();

			cout << "\nRevealed board:\n"; 
			m_board.revealBoard();

			m_board.DisplayBoard();
			cout << "\n\n";
		}

		if (m_victory) {
			system("cls");
			cout << "You won, congratulations!!" << endl;
			m_board.DisplayBoard();
		}

		Reset();

		cout << "Would you like to play again? Y/N\n" << endl;
		minesweeping = getchar();
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		minesweeping = toupper(minesweeping);
	}
	
}

/*************************
*
* Function: Display
*
* Purpose: Outputs instructions
* on how to play, and displays
* the board. Also clears the 
* console display every time 
* it is called. 
*
*************************/
void Minesweeper::Display()																						//display the board
{
	system("cls");																							//clear the console screen
	cout << "Set a flag by entering 'M', a space, and then the desired coordinate.\n " <<
		"remove a flag using 'U', a space, and then the desired coordinate.\n" <<  
		"Example: U 3,F\t\t M 3,F\n\n" <<
		"Take a guess by entering only the coordinates.\n"  <<
		"Example: 3,F\n\n" << endl;

	m_board.DisplayBoard();

	cout << "\n\n";
}

/*************************
*
* Function: Reset
*
* Purpose: Set the default
* values for m_fail and 
* m_victory. Reset the board.
*
*************************/
void Minesweeper::Reset()																						//reset the game
{
	m_board.resetBoard();
	m_fail = false;
	m_victory = false;
}
