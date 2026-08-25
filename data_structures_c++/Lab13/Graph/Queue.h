/************************************
* 
* Author: Zaelfenn Sandow
* 
* Date created: April 25th, 2024
* 
* Purpose: Define a templated Queue class
* based on a linked list class.
* 
* 
**************************************/


#pragma once

#include "List.h"

template <typename T>
class Queue {

public:

	Queue();									//default ctor
	Queue(Queue&& copy)noexcept;						//move ctor
	Queue(const Queue& copy);					//copy ctor
	~Queue();									//dtor
	Queue& operator = (Queue&& rhs)noexcept;			//move assignment operator
	Queue& operator = (const Queue& rhs);		//copy assignment operator

	void Enqueue(T data);						//add to the end of the queue

	T Dequeue();								//remove from the beginning of the queue

	T Peek();									//return the first item of the queue
	T Peek()const;

	int getNumElements();						//return the number of elements in the queue
	int getNumElements()const;

	bool isEmpty();								//check if the queue is empty
	bool isEmpty()const;

private:
	List<T> m_queue;							//holds the elements
	int m_num_elements;							//track the number of elements
};

/****************************
* 
* Function: default ctor
* 
* Purpose: establish default
* member variable values. this 
* includes the number of elements 
* being 0 and the list being empty. 
* 
*****************************/
template <typename T>
Queue<T>::Queue() : m_queue(List<T>()), m_num_elements(0)			//default ctor
{}

/****************************
*
* Function: move ctor
*
* Purpose: Create a new class
* object with the same member
* variable values as the passed
* in object.
*
*****************************/
template <typename T>
Queue<T>::Queue(Queue&& copy)noexcept : m_queue(copy.m_queue), m_num_elements(copy.m_num_elements)		//move ctor
{}

/****************************
*
* Function: Copy Ctor
*
* Purpose: Create a new class
* object with the same member
* variable values as the passed
* in object.
*
*****************************/
template <typename T>
Queue<T>::Queue(const Queue& copy) : m_queue(copy.m_queue), m_num_elements(copy.m_num_elements)		//copy ctor
{}

/****************************
*
* Function: Destructor
*
* Purpose: return the member 
* variables back to base value. 
*
*****************************/
template <typename T>
Queue<T>::~Queue()									//dtor
{
	m_queue.Purge();
	m_num_elements = 0;
}

/****************************
*
* Function: Move Assignment op
*
* Purpose: assign the values of
* member variables from RHS to LHS.
* return the updated values. 
*
*****************************/
template <typename T>
Queue<T>& Queue<T>::operator = (Queue&& rhs)noexcept			//move assignment operator
{
	if (this != &rhs) {
		m_queue = rhs.m_queue;
		m_num_elements = rhs.m_num_elements;
	}

	return *this;
}

/****************************
*
* Function: Copy Assignment Op
*
* Purpose: assign the member values
* of RHS to LHS. return the adjusted
* values. 
*
*****************************/
template <typename T>
Queue<T>& Queue<T>::operator = (const Queue& rhs)		//copy assignment operator
{
	if (this != &rhs) {
		m_queue = rhs.m_queue;
		m_num_elements = rhs.m_num_elements;
	}

	return *this;
}

/****************************
*
* Function: Enqueue
*
* Purpose: Add a passed in element
* to the queue. Increment the total
* number of items in queue by one
*
*****************************/
template <typename T>
void Queue<T>::Enqueue(T data)							//add to the end of the queue
{
	m_num_elements += 1;
	m_queue.Append(data);
}

/****************************
*
* Function: Dequeue
*
* Purpose: Remove and return 
* the first element in queue. If
* there are no elements in queue,
* throw an exception.
*
*****************************/
template <typename T>
T Queue<T>::Dequeue()								//remove from the beginning of the queue
{
	if (m_num_elements == 0) {
		throw(Exception("Underflow error: Unable to dequeue from an empty queue"));
	}
	m_num_elements -= 1;
	T retVal = m_queue.First();
	m_queue.Extract(m_queue.First());
	return retVal;
}

/****************************
*
* Function: Peek
*
* Purpose: Return the first element
* in the queue. If there are no
* elements queued, throw an 
* exception. 
*
*****************************/
template <typename T>
T Queue<T>::Peek()									//return the first item of the queue
{
	if (m_num_elements == 0) {
		throw(Exception("Underflow error: Unable to peek at empty queue"));
	}
	return m_queue.First();
}

/****************************
*
* Function: Peek (const)
*
* Purpose: Return the first item
* in the queue. If there is nothing,
* throw an exception.
*
*****************************/
template <typename T>
T Queue<T>::Peek()const
{
	if (m_num_elements == 0) {
		throw(Exception("Underflow error: Unable to peek at empty queue"));
	}
	return m_queue.First();
}

/****************************
*
* Function: getNumElements
*
* Purpose: return the number of
* elements in queue.
*
*****************************/
template <typename T>
int Queue<T>::getNumElements()						//return the number of elements in the queue
{
	return m_num_elements;
}

/****************************
*
* Function: getNumElements (const)
*
* Purpose: return the total 
* number of elements in queue.
*
*****************************/
template <typename T>
int Queue<T>::getNumElements()const
{
	return m_num_elements;
}

/****************************
*
* Function: isEmpty
*
* Purpose: return true if there
* are no elements in the list.
*
*****************************/
template <typename T>
bool Queue<T>::isEmpty()								//check if the queue is empty
{
	return m_num_elements == 0;
}

/****************************
*
* Function: isEmpty (const)
*
* Purpose: return true if 
* there are no elements in the 
* list.
*
*****************************/
template <typename T>
bool Queue<T>::isEmpty()const
{
	return m_num_elements == 0;
}