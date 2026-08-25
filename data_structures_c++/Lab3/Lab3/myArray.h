/*******************************************************************
*
* Date created: April 2nd, 2024
* 
* File Author: Zaelfenn Sandow
* 
* File name: myArray.h
*
* File purpose: Declares the class of myArray, which should be a
* templated class that functions similarly to a default array,
* but with more operations available. This class is templated.
* 
* 
*******************************************************************/
#pragma once

#include "Exception.h"

template <typename T>

class Array {

	public:	
		Array();											//default constructor
		Array(int length, int start_index = 0);				//value constructor 
		Array(const Array<T>& copy);						//copy constructor
		Array(Array<T>&& copy);								//move constructor
		
		Array& operator = (const Array<T>& rhs);			//copy assignment operator
		Array& operator = (Array<T>&& rhs);					//move assignment operator

		~Array();											//destructor

		T& operator [] (int index);							//subscript operator

		int GetStartIndex();								//getter for m_start_index
		int GetLength();									//getter for m_length

		void SetStartIndex(int i);							//setter for setStartIndex
		void SetLength(int length);								//setter for m_length

	private:
		T* m_array;											//array of T values
		int m_start_index;									//where the first element is
		int m_length;										//length of the array
};
template <typename T>
Array<T>::Array() : m_array(nullptr), m_start_index(0), m_length(0)														//default constructor
{}

template <typename T>
Array<T>::Array(int length, int start_index) : m_array(nullptr), m_start_index(start_index), m_length(length)			//value constructor 
{
	if (length > 0)						//positive length of at least one
		m_array = new T[length];
	else if (length < 0)				//negative length not valid
	{
		throw(Exception("Length cannot be negative"));
	}
	else							//length of zero, or no length at all
	{
		m_array = nullptr;
	}
		
}

template <typename T>
Array<T>::Array(const Array<T>& copy) : m_array(nullptr), m_start_index(copy.m_start_index), m_length(copy.m_length)	//copy constructor
{
	if (copy.m_array != nullptr) {
		delete[] m_array;
		m_length = copy.m_length;
		m_array = new T[m_length];
		for (int i = 0; i < m_length; ++i)
		{
			m_array[i] = copy.m_array[i];
		}
		m_start_index = copy.m_start_index;
	}
}

template <typename T>
Array<T>::Array(Array<T>&& copy) : m_array(nullptr), m_start_index(copy.m_start_index), m_length(copy.m_length)			//move constructor
{
	if (copy.m_array != nullptr) {
		m_array = copy.m_array;
		copy.m_array = nullptr;
	}
}

template <typename T>
Array<T>& Array<T>::operator = (const Array<T>& rhs)			//copy assignment operator
{
	if (this != &rhs)
	{
	
		delete[] m_array;
		m_length = rhs.m_length;
		m_array = new T[m_length];
		if (rhs.m_array != nullptr)
		{
			for (int i = 0; i < m_length; ++i)
			{
				m_array[i] = rhs.m_array[i];
			}
		}
		m_start_index = rhs.m_start_index;
	}
	return *this;
}

template <typename T>
Array<T>& Array<T>::operator = (Array<T>&& rhs)					//move assignment operator
{
	if (this != rhs)
	{
		delete[] m_array;
		m_array = rhs.m_array;
		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;

		rhs.m_array = nullptr;
		rhs.m_length = 0;
		rhs.m_start_index = 0;
	}
	return *this;
}

template <typename T>
Array<T>::~Array()											//destructor
{
	delete[] m_array;
	m_array = nullptr;
	m_length = 0;
	m_start_index = 0;
}

template <typename T>
T& Array<T>::operator [] (int index)							//subscript operator
{
	if (index - m_start_index < 0)			//out of bounds in the negative range
	{
		throw(Exception("Out of bounds- index too small"));
	}
	else if (index - m_start_index > m_length)			//out of bounds in the positive range
	{
		throw(Exception("Out of bounds- index too large"));
	}
	return m_array[index - m_start_index];			//return the value from desired location
}

template <typename T>
int Array<T>::GetStartIndex() 								//getter for m_start_index
{
	return m_start_index;
}

template <typename T>
int Array<T>::GetLength()									//getter for m_length
{
	return m_length;
}

template <typename T>
void Array<T>::SetStartIndex(int i)							//setter for setStartIndex
{
	m_start_index = i;
}

template <typename T>
void Array<T>::SetLength(int length)								//setter for m_length
{
	if (length > 1)
	{
		if (m_array != nullptr)
		{
			T* temp = new T[length];
			for (int i = 0; i < length && i < m_length; ++i)
			{
				temp[i] = m_array[i];
			}
			delete[] m_array;
			m_array = temp;
		}
		else
		{
			m_array = new T[length];
		}
	}
	else if (length == 1)					//if a length of one is given, copy over the first element from the previous array (if applicable) and delete the rest
	{
		if (m_array != nullptr)
		{
			T temp = m_array[0];
			delete[] m_array;
			m_array = new T;
			*m_array = temp;
		}
		else
		{
			m_array = new T;
		}
	}
	else if (length == 0)					//if a length of zero is given, delete all existing elements and set to nullptr
	{
		delete[] m_array;
		m_array = nullptr;
	}
	else								//if a negative number is entered, throw an exception		
	{
		throw(Exception("Negative Length INVALID"));

	}
	m_length = length;
}