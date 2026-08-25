#pragma once
#include "Exception.h"
#include "Row.h"


template <typename T>
class Row;

template <typename T>
class Array2D {
	friend class Row<T>;
public:
	Array2D();												//default ctor
	Array2D(int row, int col);								//value ctor
	Array2D(const Array2D& copy);							//copy ctor
	Array2D& operator = (const Array2D& rhs);				//copy assignment operator
	~Array2D();												//destructor

	int getRow();											//getter for rows
	int getColumns();										//getter for columns

	const int getRow() const;								//const compliant getter
	const int getColumns() const;							//const compliant getter

	void setRows(int rows);									//setter for rows
	void setColumns(int cols);								//setter for columns

	Row<T> operator [] (int row);							//subscript operator

	const T& Select(int d_r, int d_c) const;				//const compliant select function
	T& Select(int d_r, int d_c);							//select function (subscript function)

private:
	int m_row;												//row count
	int m_col;												//column count
	T** m_arr;												//array
};
template <typename T>
Array2D<T>::Array2D() : m_row(0), m_col(0), m_arr(nullptr)												//default ctor
{}

template <typename T>
Array2D<T>::Array2D(int row, int col) : m_row(row), m_col(col), m_arr(nullptr)									//value ctor
{
	if (m_row > 0 && m_col > 0) {																	//if there is a positive value to copy 
		m_arr = new T * [m_row];																	//allocate the proper amount of row pointers
		for (int i = 0; i < m_row; ++i) {
			m_arr[i] = new T[m_col];																//allocate the space for each collumn
		}
	}
	else {
		throw(Exception("Attempting to create illegal array"));
	}
}

template <typename T>
Array2D<T>::Array2D(const Array2D& copy) : m_row(copy.m_row), m_col(copy.m_col), m_arr(nullptr)							//copy ctor
{
	if (m_row > 0 && m_col > 0) {								//if there are both rows and collumns to copy
		m_arr = new T* [m_row];									//create a pointer to a pointer with the proper amount of rows
	
		for (int i = 0; i < m_row; ++i) {
			m_arr[i] = new T[m_col];							//allocate the space for each column
			for (int j = 0; j < m_col; ++j) {
				m_arr[i][j] = copy.m_arr[i][j];					//fill the new array with the same data as the old 
			}
		}
	}
	
}

template <typename T>
Array2D<T>& Array2D<T>::operator = (const Array2D& rhs)			//copy assignment operator
{
	if (this != &rhs) {												//self reference check

		if (m_row > 0 && m_col > 0) {								//if there are both rows and collumns to copy

			m_arr = new T*[m_row];							//create a pointer to a pointer with properly allocated space for the total amount of rows

			for (int i = 0; i < m_row; ++i) {				//initialize each row to the proper amount of space
				m_arr[i] = new T[m_col];
				for (int j = 0; j < m_col; ++j) {
					m_arr[i][j] = rhs.m_arr[i][j];					//fill the new array with the same data as the old 
				}
			}

			m_row = rhs.m_row;
			m_col = rhs.m_col;
		}
	}
	return *this;
}

template <typename T>
Array2D<T>::~Array2D()												//destructor
{
	if (m_row > 0 && m_col > 0) {						//if there is data, delete it
		for (int i = 0; i < m_row; ++i) {
			delete[] m_arr[i];
			m_arr[i] = nullptr;							//set each row to be nullptr
		}
	}
	delete[] m_arr;
	m_arr = nullptr;									//set m_arr to point at nothing
	m_row = 0;
	m_col = 0;											//guarantee default values
}

template <typename T>
int Array2D<T>::getRow()											//getter for rows
{
	return m_row;
}

template <typename T>
int Array2D<T>::getColumns()										//getter for columns
{
	return m_col;
}

template <typename T>
const int Array2D<T>::getRow() const								//const compliant getter
{
	return m_row;
}

template <typename T>
const int Array2D<T>::getColumns() const						//const compliant getter
{
	return m_col;
}

template <typename T>
void Array2D<T>::setRows(int rows)									//setter for rows
{
	if (rows < 0) {													//cannot set a negative length
		throw(Exception("Attempting to set an illegal length"));
	}

	else if (rows < m_row){											//deleting existing rows
		for (int i = rows; i < m_row; ++i) {
			delete[] m_arr[i];									//delete all "excess" rows
		}
	}

	else if (rows > m_row){											//adding new rows
		T** temp_arr = new T * [rows];
		for (int i = 0; i < m_row; ++i) {
			temp_arr[i] = m_arr[i];								//move existing rows over
			m_arr[i] = nullptr;
		}
		for (int i = m_row; i < rows; ++i) {
			temp_arr[i] = new T[m_col];
		}
		delete[] m_arr;											//deallocate old pointers
		m_arr = temp_arr;										//reassign to new array
	}

	else if (rows == 0) {											//deleting all rows
		for (int i = 0; i < m_row; ++i) {
			delete[] m_arr[i];										//delete all row values
			m_arr[i] = nullptr;
		}
		delete[] m_arr;
		m_arr = nullptr;
		m_col = rows;												//change column value to 0
	}

	else 															//nothing happens
	{}

	m_row = rows;
}

template <typename T>
void Array2D<T>::setColumns(int cols)								//setter for columns
{
	if (cols < 0) {											//cant set to a negative value
		throw(Exception("Attempting to set an illegal length"));
	}

	else if (cols > m_col) {								//adding columns
		for (int i = 0; i < m_row; ++i) {					//change each row
			T* temp_ptr = new T[cols];						//change the size of the column
			for (int j = 0; j < m_col; ++j) {
				temp_ptr[j] = m_arr[i][j];					//copy over old data
			}
			delete[] m_arr[i];								//deallocate old data
			m_arr[i] = temp_ptr;							//move the pointer into the array
		}
	}

	else if (cols < m_col) {								//deleting columns

		for (int i = 0; i < m_row; ++i){					//change each row
			T* temp_ptr = new T[cols];						//change the size of the column
			for (int j = 0; j < cols; ++j) {
				temp_ptr[j] = m_arr[i][j];					//copy over old data
			}
			delete[] m_arr[i];								//deallocate old data
			m_arr[i] = temp_ptr;							//move the pointer into the array
		}
	}

	else if (cols == 0) {									//delete m_arr
		for (int i = 0; i < m_row; ++i) {
			delete[] m_arr[i];										//delete all row values
			m_arr[i] = nullptr;
		}
		m_arr = nullptr;
		m_row = cols;												//change row value
	}

 	else													//do nothing
	{}

	m_col = cols;
}

template <typename T>
Row<T> Array2D<T>::operator [] (int row)							//subscript operator
{
	if (row < 0 || row > m_row) {
		throw(Exception("Attempting to access out of bounds"));
	}

	Row<T> retVal(*this, row);
	return retVal;
}

template <typename T>
const T& Array2D<T>::Select(int d_r, int d_c) const				//const compliant select function
{
	return *this[d_r][d_c];
}

template <typename T>
T& Array2D<T>::Select(int d_r, int d_c)							//select function (subscript function)
{
	return *this[d_r][d_c];
}