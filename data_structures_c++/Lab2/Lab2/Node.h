/*******************************************************************
*
* Date created: April 3rd, 2024
*
* File Author: Zaelfenn Sandow
*
* File name: Exception.h
*
* File purpose: Declares and defines the member functions and data members  
* of the node class. Friends with the TDLL class. 
*
*
*******************************************************************/


#pragma once

#include "List.h"

template<typename T>
class List;

template<typename T>

class Node {
	friend class List<T>;
private:

	Node();									//default constructor
	Node(T data);							//value constructor
	~Node();								//destructor
	Node(const Node& original);				//copy constructor
	Node& operator = (const Node& rhs);		//copy assignment operator

	T		m_data;
	Node<T>* m_next;
	Node<T>* m_prev;
};

template<typename T>
Node<T>::Node() : m_data(T()), m_next(nullptr), m_prev(nullptr)
{}

template<typename T>
Node<T>::Node(T data) : m_data(data), m_next(nullptr), m_prev(nullptr)
{}

template<typename T>
Node<T>::~Node()
{
	m_next = nullptr;
	m_prev = nullptr;
	m_data = T();
}

template<typename T>
Node<T>::Node(const Node<T>& original) : m_data(original.m_data), m_next(original.m_next), m_prev(original.m_prev)
{}

template<typename T>
Node<T>& Node<T>::operator=(const Node& rhs) {
	if (this != *rhs) {
		m_data = rhs.m_data;
		m_next = rhs.m_next;
		m_prev = rhs.m_prev;
	}
}
