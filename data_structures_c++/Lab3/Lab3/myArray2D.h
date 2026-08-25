#pragma once

#include "Exception.h"
#include "myArray.h"
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
	Array<T> m_arr;											//array
};

template <typename T>
Array2D<T>::Array2D() : m_row(0), m_col(0), m_arr(Array<T>())												//default ctor
{}

template <typename T>
Array2D<T>::Array2D(int row, int col) : m_row(row), m_col(col), m_arr(Array<T>(row * col))												//value constructor
{}

template <typename T>
Array2D<T>::Array2D(const Array2D& copy) : m_row(copy.m_row), m_col(copy.m_col), m_arr(copy.m_arr)		//copy constructor
{}

template <typename T>
Array2D<T>& Array2D<T>::operator = (const Array2D& rhs)													//copy assignment operator
{
	m_row = rhs.m_row;
	m_col = rhs.m_col;
	m_arr = rhs.m_arr;												//copy all the data over, because nothing gets deleted don't need to self reference check

	return *this;													//return the new object
}

template <typename T>
Array2D<T>::~Array2D()																						//destructor
{
	m_row = 0;										
	m_col = 0;									//set row/column to default value (0)
	m_arr.SetLength(0);							//delete the array
}

template <typename T>
const int Array2D<T>::getRow() const																				//rows getter
{
	return m_row;									//return row count
}

template <typename T>
const int Array2D<T>::getColumns() const																			//columns getter
{
	return m_col;									//return column count
}

template <typename T>
int Array2D<T>::getRow()																			//rows getter
{
	return m_row;									//return row count
}	

template <typename T>
int Array2D<T>::getColumns() 																		//columns getter
{
	return m_col;									//return column count
}

template <typename T>
void Array2D<T>::setRows(int rows)																			//rows setter
{
	if (rows < 0) {																	//out of bounds exception
		throw(Exception("Trying to set rows too low"));
	}
	else {																			//Adjust row count as needed
		m_row = rows;												//change to new row amount
		m_arr.SetLength(m_row * m_col);								//because the array is set up to be row major, when adjusting rows the length can be adjusted proportionate to
																	//the new row length
	}
}

template <typename T>
void Array2D<T>::setColumns(int cols)																	//columns setter
{
	Array<T> arr(m_row * cols);
	if (cols < 0) {																						//out of bounds exception
		throw(Exception("Trying to set columns too low"));
	}
	else if (m_col > cols){																				//if downsizing, copy old array elements into a new array,
																										//cutting out data that "doesn't fit"	
		for (int i = 0; i < m_row; ++i) {
			for (int j = 0; j < cols; ++j) {
				arr[i * cols + j] = m_arr[i * m_col + j];					//because the array is set up to be row major, the columns need to be adjusted cell-by-cell.
			}
		}
	}
	else {																								//if upsizing, copy old array elements into a new array,
																										//leaving empty spaces where data "doesn't exist"
		for (int i = 0; i < m_row; ++i) {
			for (int j = 0; j < m_col; ++j) {
				arr[i * cols + j] = m_arr[i * m_col + j];					//because the array is set up to be row major, the columns need to be adjusted cell-by-cell
			}
		}
	}
	m_arr = arr;
	m_col = cols;											//adjust m_col and m_arr to reflect the new data
}


template <typename T>
Row<T> Array2D<T>::operator [] (int row)																	//subscript operator
{
	if (m_row < row || row < 0) {														//out of bounds exception
		throw(Exception("Attempting to go out of bounds: row"));
	}

	Row<T> retVal(*this, row);															//create a row object to return

	return retVal;																		//return the row object
}

template <typename T>
const T& Array2D<T>::Select(int d_r, int d_c) const																//subscript function, const compliant
{
	return *this[d_r][d_c];														//select is basically just subscript operator, but in function form. therefore,
																				//use subscript instead of rewriting the same thing. 
}

template <typename T>
T& Array2D<T>::Select(int d_r, int d_c)																			//subscript function
{
	return *this[d_r][d_c];
}