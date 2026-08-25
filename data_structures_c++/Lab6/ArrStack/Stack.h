#pragma once
#include "myArray.h"

template<typename T>
class Stack {
public:
	Stack();												//default ctor
	Stack(int size);										//value ctor
	Stack(Stack&& copy)noexcept;							//move ctor
	Stack(const Stack& copy);								//copy ctor
	Stack& operator = (Stack&& rhs)noexcept;				//move assignment op
	Stack& operator = (const Stack& rhs);					//copy assignment op

	~Stack();												//destructor

	void Push(T data);										//push data onto the stack

	T Pop();												//pop data off the stack

	T Peek();												//return item at the top of the stack
	T Peek() const;											//return item at the top of a const stack

	int getNumElements();									//getter for top
	int getNumElements() const;								//getter for top

	int getSize();											//getter for size
	int getSize() const;									//getter for size

	void setSize(int size);									//setter for size

	bool isEmpty();											//check if the stack is empty
	bool isEmpty() const;									//check if the stack is empty

	bool isFull();											//check if the stack is full
	bool isFull() const;									//check if the stack is full
private:
	Array<T> m_stack;
	int m_size;
	int m_top;
};

/****************************
* 
* Function: Default Ctor
* 
* Purpose: Set default values,
* which are a default array of 
* no size, m_size set to 0, and
* m_top set to -1 
* 
*****************************/
template<typename T>
Stack<T>::Stack() : m_stack(Array<T>()), m_size(0), m_top(-1)												//default ctor
{}

/****************************
*
* Function: Value Ctor
*
* Purpose: Set member variables
* according to the passed in integer,
* which sets the array and size
* to a specific int and leaves
* m_top at -1
*
*****************************/
template<typename T>
Stack<T>::Stack(int size) : m_stack(Array<T>(size)), m_size(size), m_top(-1)										//value ctor
{}

/****************************
*
* Function: Move Ctor
*
* Purpose: Copy the values of
* one stack to another
*
*****************************/
template<typename T>
Stack<T>::Stack(Stack&& copy) noexcept : m_stack(copy.m_stack), m_size(copy.m_size), m_top(copy.m_top)									//move ctor
{}

/****************************
*
* Function: Copy Ctor
*
* Purpose: Copy the values of
* one stack to another
*
*****************************/
template<typename T>
Stack<T>::Stack(const Stack& copy) : m_stack(copy.m_stack), m_size(copy.m_size), m_top(copy.m_top)							//copy ctor
{}

/****************************
*
* Function: Move Assignment Operator
*
* Purpose: Copy the values of
* one stack to another
*
*****************************/
template<typename T>
Stack<T>& Stack<T>::operator = (Stack&& rhs) noexcept						//move assignment op
{
	if (this != &rhs) {
		m_stack = rhs.m_stack;
		m_size = rhs.m_size;
		m_top = rhs.m_top;
	}
	return *this;
}

/****************************
*
* Function: Copy Assignment Operator
*
* Purpose: Copy the values of
* one stack to another
*
*****************************/
template<typename T>
Stack<T>& Stack<T>::operator = (const Stack& rhs)					//copy assignment op
{
	if (this != &rhs) {
		m_stack = rhs.m_stack;
		m_size = rhs.m_size;
		m_top = rhs.m_top;
	}
	return *this;
}

/****************************
*
* Function: Destructor
*
* Purpose: Set the stack back
* to default values
*
*****************************/
template<typename T>
Stack<T>::~Stack()
{
	m_size = 0;
	m_top = -1;
	m_stack.SetLength(m_size);
}

/****************************
*
* Function: Push
*
* Purpose: Add data to the top 
* of the stack. Will throw an 
* exception if the stack has 
* no space left.
*
*****************************/
template<typename T>
void Stack<T>::Push(T data)										//push data onto the stack
{
	if (!isFull()) {
		++m_top;
		m_stack[m_top] = data;
	}
	else
		throw(Exception("Overflow error: Attempting to push onto a full stack"));
}

/****************************
*
* Function: Pop
*
* Purpose: Remove data from the
* top of the stack. Return the 
* data that is popped off 
* of the stack. Throw an exception
* if the stack is empty. 
*
*****************************/
template<typename T>
T Stack<T>::Pop()												//pop data off the stack
{
	T retVal = m_stack[m_top];
	if (!isEmpty()) {
		m_stack[m_top] = T();
		--m_top;
	}
	else
		throw(Exception("Underflow error: Attempting to pop off an empty stack"));
	
	return retVal;
}

/****************************
*
* Function: Peek
*
* Purpose: Return the data
* from  the top of the stack.
* Throw an exception if the 
* stack is empty.
*
*****************************/
template<typename T>
T Stack<T>::Peek()												//return item at the top of the stack
{
	if (isEmpty()) {
		throw(Exception("Underflow Error: Attempting to access an empty stack"));
	}

	return m_stack[m_top];
}

/****************************
*
* Function: Peek (const)
*
* Purpose: Return the data
* from  the top of the stack.
* Throw an exception if the
* stack is empty.
*
*****************************/
template<typename T>
T Stack<T>::Peek() const											//return item at the top of a const stack
{
	if (isEmpty()) {
		throw(Exception("Underflow Error: Attempting to access an empty stack"));
	}

	return m_stack[m_top];
}

/****************************
*
* Function: getNumElements
*
* Purpose: Return the total number
* of elements currently in the stack.
*
*****************************/
template<typename T>
int Stack<T>::getNumElements()									//getter for top
{
	return m_top + 1;
}

/****************************
*
* Function: getNumElements (const)
*
* Purpose: Return the total number
* of elements currently in the stack.
*
*****************************/
template<typename T>
int Stack<T>::getNumElements() const								//getter for top
{
	return m_top + 1;
}

/****************************
*
* Function: getSize
*
* Purpose: Return the total space
* available in the stack.
*
*****************************/
template<typename T>
int Stack<T>::getSize()											//getter for size
{
	return m_size;
}

/****************************
*
* Function: getSize (const)
*
* Purpose: Return the total space
* available in the stack.
*
*****************************/
template<typename T>
int Stack<T>::getSize() const									//getter for size
{
	return m_size;
}

/****************************
*
* Function: setSize
*
* Purpose: Set the total size
* available in the stack. If 
* m_top would point to out of 
* bounds, instead set it to point
* at the top of the new stack. 
*
*****************************/
template<typename T>
void Stack<T>::setSize(int size)									//setter for size
{
	if (size >= 0) {
		m_size = size;
		m_stack.SetLength(m_size);
		if (m_top >= m_size)
			m_top = m_size - 1;
	}
	else
		throw(Exception("Error: Cannot Set Negative Length"));
}

/****************************
*
* Function: isEmpty
*
* Purpose: Return a bool which is 
* true if the stack is empty.
*
*****************************/
template<typename T>
bool Stack<T>::isEmpty()											//check if the stack is empty
{
	return m_top == -1;
}

/****************************
*
* Function: isEmpty (const)
*
* Purpose: Return a bool which is
* true if the stack is empty.
*
*****************************/
template<typename T>
bool Stack<T>::isEmpty() const									//check if the stack is empty
{
	return m_top == -1;
}

/****************************
*
* Function: isFull
*
* Purpose: Return a bool which is
* true if the stack is full.
*
*****************************/
template<typename T>
bool Stack<T>::isFull()											//check if the stack is full
{
	return m_top == m_size - 1;
}

/****************************
*
* Function: isFull (const)
*
* Purpose: Return a bool which is
* true if the stack is full.
*
*****************************/
template<typename T>
bool Stack<T>::isFull() const									//check if the stack is full
{
	return m_top == m_size - 1;
}