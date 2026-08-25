/************************************
*
* Author: Zaelfenn Sandow
*
* Date created: April 26th, 2024
*
* Purpose: Define a templated circular Queue class
* based on an array class.
*
*
**************************************/


#pragma once

#include "myArray.h"
/*************************************
* 
* Class: Queue
* 
* 
* Manager Functions:
*			default ctor
*			value ctor
*			move ctor
*			copy ctor
*			move assignment op
*			copy assignment op
*			dtor
* 
* Member functions:
*			Enqueue
*			Dequeue
*			Peek
*			getSize
*			isEmpty
*			isFull
* 
* 
* 
****************************************/
template<typename T>
class Queue {

public:

	Queue();									//default ctor
	Queue(int size);							//value ctor
	Queue(Queue&& copy)noexcept;				//move ctor
	Queue(const Queue& copy);					//copy ctor
	~Queue();									//dtor
	Queue& operator = (Queue&& rhs)noexcept;	//move assignment operator
	Queue& operator = (const Queue& rhs);		//copy assignment operator

	void Enqueue(T data);						//add to the end of the queue

	T Dequeue();								//remove from the beginning of the queue

	T Peek();									//return the first item of the queue
	T Peek()const;

	int getSize();								//return the number of elements in the queue
	int getSize()const;

	bool isEmpty();								//check if the queue is empty
	bool isEmpty()const;

	bool isFull();								//check if the queue is full
	bool isFull()const;

private:
	Array<T> m_queue;
	int m_size;
	int m_head;
	int m_tail;
};

/****************************
*
* Function: default ctor
*
* Purpose: establish default
* member variable values. this 
* includes a default sized array,
* a size of 0, and m_head and
* m_tail being -1.
*
*****************************/
template <typename T>
Queue<T>::Queue() : m_queue(Array<T>()), m_size(0), m_head(-1), m_tail(-1)			//default ctor
{}

/****************************
*
* Function: value ctor
*
* Purpose: establish values of
* member variables. this sets the 
* size of the array to the passed
* in number.
*
*****************************/
template <typename T>
Queue<T>::Queue(int size) : m_queue(Array<T>(size)), m_size(size), m_head(-1), m_tail(-1)			//default ctor
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
Queue<T>::Queue(Queue&& copy)noexcept : m_queue(copy.m_queue), m_size(copy.m_size), m_head(copy.m_head), m_tail(copy.m_tail)		//move ctor
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
Queue<T>::Queue(const Queue& copy) : m_queue(copy.m_queue), m_size(copy.m_size), m_head(copy.m_head), m_tail(copy.m_tail)			//copy ctor
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
	m_queue.SetLength(0);
	m_size = 0;
	m_head = -1;
	m_tail = -1;
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
		m_size = rhs.m_size;
		m_tail = rhs.m_tail;
		m_head = rhs.m_head;
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
		m_size = rhs.m_size;
		m_tail = rhs.m_tail;
		m_head = rhs.m_head;
	}

	return *this;
}

/****************************
*
* Function: Enqueue
*
* Purpose: Add a passed in element
* to the queue. Check if the tail
* should loop. Throw an exception 
* if the queue is full.
*
*****************************/
template <typename T>
void Queue<T>::Enqueue(T data)							//add to the end of the queue
{
	if (isFull() || m_size == 0) {
		throw(Exception("Overflow Error: Attempting to add to a full queue"));
	}

	++m_tail;
	
	if (m_tail == m_size) {					//check if m_tail should loop back to the beginning
		m_tail = 0;
	}

	if (m_head < 0) {						//check if m_head has been initialized yet
		m_head = 0;
	}

	m_queue[m_tail] = data;

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
	if (isEmpty()) {
		throw(Exception("Underflow error: Unable to dequeue from an empty queue"));
	}

	T retVal = m_queue[m_head];
	m_queue[m_head] = T();
	++m_head;
	if (m_head == m_tail + 1) {				//check if every item has been dequeued
		m_head = -1;
		m_tail = -1;
	}
	else if (m_head == m_size) {			//check if m_head has hit the end of the queue
		m_head = 0;
	}

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
	
	if (isEmpty()) {
		throw(Exception("Underflow error: Unable to peek at empty queue"));
	}
	
	return m_queue[m_head];
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
	if (isEmpty()) {
		throw(Exception("Underflow error: Unable to peek at empty queue"));
	}
	return m_queue[m_head];
}

/****************************
*
* Function: getSize
*
* Purpose: return the number of
* spaces available in the queue
*
*****************************/
template <typename T>
int Queue<T>::getSize()							//return the total number of spaces available in the queue
{
	return m_size;
}

/****************************
*
* Function: getSize (const)
*
* Purpose: return the number of
* spaces available in the queue.
*
*****************************/
template <typename T>
int Queue<T>::getSize()const
{
	return m_size;
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
	return m_tail == -1;								//enqueue increments m_tail. therefore if m_tail is less than 0, the queue is empty. 
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
	return m_tail == -1;
}

/****************************
*
* Function: isFull
*
* Purpose: return true if the
* queue is full
*
*****************************/
template <typename T>
bool Queue<T>::isFull()								//check if the queue is full
{
	return (m_head <= 0 && m_tail == m_size - 1) || ((m_head - m_tail) == 1);			//queue is only full if m_head is at 0 or -1 and m_tail is equal to the size,
																									//or if m_tail has looped back around to meet m_head
}

/****************************
*
* Function: isFull (const)
*
* Purpose: return true if
* the queue is full
*
*****************************/
template <typename T>
bool Queue<T>::isFull()const
{
	return ((m_head == 0 || m_head == -1) && m_tail == m_size - 1) || ((m_head - m_tail) == 1);	
}