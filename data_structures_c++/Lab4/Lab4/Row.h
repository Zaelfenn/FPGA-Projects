#pragma once


#include "myArray2D.h"

template <typename T>
class Array2D;

template <typename T>
class Row {
	friend class Array2D<T>;
public:
	Row(Array2D<T> & arr, int row);									//value ctor
	const T& operator [](int column) const;							//const compliant subscript operator
	T& operator [](int column);										//subscript operator
	~Row();															//destructor

	int m_row;														//row count
private:
	Array2D<T>& m_arr;												//reference to the array that this row is a part of
};

template <typename T>
Row<T>::Row(Array2D<T> & arr, int row) : m_arr(arr), m_row(row)					//value ctor
{}

template <typename T>
const T& Row<T>::operator[](int column) const									//const compliant subscript operator
{

	if (column > m_arr.m_col || column < 0) {									//out of bounds exception
		throw(Exception("Attempting to go out of bounds: column"));
	}
	return m_arr.m_arr[m_row][column];							//return the element in the row of the member array's member array, offset to the right position via column
}

template <typename T>
T& Row<T>::operator[](int column)												//subscript operator
{

	if (column > m_arr.m_col || column < 0) {									//out of bounds exception
		throw(Exception("Attempting to go out of bounds: column"));
	}
	return m_arr.m_arr[m_row][column];							//return the element in the row of the member array's member array, offset to the right position via column			
}

template <typename T>
Row<T>::~Row()																	//destructor
{}																	//nothing to get rid of