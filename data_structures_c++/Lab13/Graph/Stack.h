#pragma once


#include "List.h"

/*******************************
* 
* Class: Stack
* 
* Manager functions:
*		Default Ctor
*		Move Ctor
*		Copy Ctor
*		Move Assignment Operator
*		Copy Assignment Operator
*		Dtor
* 
* Member functions:
*		Push
*		Pop
*		Peek
*		getNumElements
*		isEmpty
* 
*********************************/
template<typename T>
class Stack {

public:
	Stack();
	Stack(Stack&& copy);
	Stack(const Stack& copy);

	Stack& operator = (Stack&& rhs);
	Stack& operator = (const Stack& rhs);
	~Stack();


	void Push(T data);
	T Pop();

	T Peek();
	T Peek() const;

	int getNumElements();
	int getNumElements()const;

	bool isEmpty();
	bool isEmpty()const;

private:
	List<T> m_stack;						//linked list used to create stack
	int m_size;								//number of elements
};

/*****************************
* function: Default Ctor
*
* purpose: set the value
* of the stack to base values,
* an empty list and a size of 0
* 
******************************/
template<typename T>
Stack<T>::Stack() : m_stack(List<T>()), m_size(0)
{}

/*****************************
* function: move ctor
*
* purpose: set the member variables
* of the new stack to match that 
* of the passed in stack
*
******************************/
template<typename T>
Stack<T>::Stack(Stack&& copy) : m_stack(copy.m_stack), m_size(copy.m_size)
{}

/*****************************
* function: Copy Ctor
*
* purpose: set the member variables
* of the new stack to match that 
* of the passed in stack
*
******************************/
template<typename T>
Stack<T>::Stack(const Stack& copy) : m_stack(copy.m_stack), m_size(copy.m_size)
{}

/*****************************
* function: Move assignment Operator
*
* purpose: set the member values
* of LHS to match those of RHS
*
******************************/
template<typename T>
Stack<T>& Stack<T>::operator = (Stack&& rhs)
{
	if (this != &rhs) {
		m_stack = rhs.m_stack;
		m_size = rhs.m_size;
	}
	return *this;
}

/*****************************
* function: Copy assignment Operator
*
* purpose: set the member values
* of LHS to match those of RHS
*
******************************/
template<typename T>
Stack<T>& Stack<T>::operator = (const Stack& rhs)
{
	if (this != &rhs) {
		m_stack = rhs.m_stack;
		m_size = rhs.m_size;
	}
	return *this;
}

/*****************************
* function: Dtor
*
* purpose: reset the value 
* of the stack to base values
*
******************************/
template<typename T>
Stack<T>::~Stack()
{
	m_stack.Purge();
	m_size = 0;
}

/*****************************
* function: Push
*
* purpose: Add an item to 
* the top of the stack
*
******************************/
template<typename T>
void Stack<T>::Push(T data)
{
	m_stack.Append(data);
	m_size += 1;
}

/*****************************
* function: Pop
*
* purpose: return the top item
* on the stack, and remove it 
* from the stack. 
*
******************************/
template<typename T>
T Stack<T>::Pop()
{
	T retVal = Peek();
	m_stack.Extract(retVal);
	m_size -= 1;
	return retVal;
}

/*****************************
* function: Peek
*
* purpose: return the top item
* on the stack.
*
******************************/
template<typename T>
T Stack<T>::Peek()
{
	if (m_size == 0) {
		throw(Exception("Underflow Error: Attempting to peek at an empty list"));
	}

	return m_stack.Last();
}

/*****************************
* function: Peek (const)
*
* purpose: return the top item
* on the stack.
*
******************************/
template<typename T>
T Stack<T>::Peek() const
{
	if (m_size == 0) {
		throw(Exception("Underflow Error: Attempting to peek at an empty list"));
	}
	
	return m_stack.Last();
}

/*****************************
* function: getNumElements
*
* purpose: return the size of
* the stack.
*
******************************/
template<typename T>
int Stack<T>::getNumElements()
{
	return m_size;
}

/*****************************
* function: getNumElements (const) 
*
* purpose: return the size of
* the stack.
* 
******************************/
template<typename T>
int Stack<T>::getNumElements()const 
{
	return m_size;
}

/*****************
* function: isEmpty
* 
* purpose: return a
* bool as to whether 
* or not the list is
* empty.
******************/
template<typename T>
bool Stack<T>::isEmpty()
{
	return m_size == 0;
}

/*****************
* function: isEmpty (const)
*
* purpose: return a
* bool as to whether
* or not the list is
* empty.
******************/
template<typename T>
bool Stack<T>::isEmpty()const
{
	return m_size == 0;
}