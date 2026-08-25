/*******************************************************************
*
* Date created: April 3rd, 2024
*
* File Author: Zaelfenn Sandow
*
* File name: TDLL.h
*
* File purpose: Declares and defines the methods and data members of 
* a templated doubly linked list. Friends with the node class. 
*
*
*******************************************************************/

#pragma once
#include <iostream>
using std::cout;
using std::endl;
#include "Node.h"
#include "Exception.h"
template <typename T>

class List {
public:
	List();								//default constructor
	List(T head);						//value constructor
	List(const List<T>& original);		//copy constructor
	List(List&& original)noexcept;		//move constructor
	
	~List();							//default constructor

	List& operator = (List<T>&& rhs)noexcept;		//move assignment operator
	List& operator = (const List<T>& rhs);			//copy assignment operator

	bool isEmpty();									//is the list empty?

	const T& First();								//returns data of first element as a const reference 
	const T& Last();								//returns data of last element as a const reference

	void Prepend(T data);							//prepend the list with data
	void Append(T data);							//append the list with data

	void Purge();									//delete all items in the list

	void Extract(T node);							//delete a single item in the list

	void InsertAfter(T new_item, T old_item);		//append a node in the list
	void InsertBefore(T new_item, T old_item);		//prepend a node in the list	

	Node<T>* getHead();								//return m_head
	Node<T>* getTail();								//return m_tail

	void PrintForwards();							//print list from head to tail
	void PrintBackwards();							//print list from tail to head

private:
	Node<T>* m_head;
	Node<T>* m_tail;

};

template <typename T>
List<T>::List() : m_head(nullptr), m_tail(nullptr)					//default constructor
{}

template <typename T>
List<T>::List(T head) : m_head(nullptr), m_tail(nullptr)					//value constructor
{
	m_head = new Node<T>(head);				//create a new node
	m_tail = m_head;						//one item list means that head and tail are the same
}

template <typename T>
List<T>::List(const List<T>& original) : m_head(nullptr), m_tail(nullptr)	//copy constructor
{
	if (original.m_head != nullptr) {				//if there is data to be copied
		m_head = new Node<T>(*original.m_head);		//copy m_head 
		m_tail = m_head;							//set m_tail
		if (m_head->m_next != nullptr) {			//if there is more than one node in the list

			Node<T>* trail = new Node<T>(*(m_head->m_next));		//copy the next node
			trail->m_prev = m_head;								//set the previous to be m_head
			m_head->m_next = trail;								//set head next to be new node
			
			while (trail->m_next != nullptr) {							//while there is data to be copied
				Node<T>* travel = new Node<T>(*(trail->m_next));				//create a new node 
				travel->m_prev = trail;										//set that node's previous to be the previous tail
				trail->m_next = travel;										//set the previous tail to point at the new node
				trail = travel;												//set the new tail
			}

			m_tail = trail;										//set the tail pointer to the end of the list
		}

	}
}

template <typename T>
List<T>::List(List&& original)noexcept : m_head(original.m_head), m_tail(original.m_tail)		//move constructor
{
	original.m_head = nullptr;			//steal the data
	original.m_tail = nullptr;			//cut the ties
}

template <typename T>
List<T>::~List()							//destructor
{
	Purge();
}

template <typename T>
List<T>& List<T>::operator = (List<T>&& rhs)noexcept		//move assignment operator
{

	if (this != &rhs) {
		Purge();
		m_head = rhs.m_head;
		m_tail = rhs.m_tail;		//steal the data

		rhs.m_head = nullptr;
		rhs.m_tail = nullptr;		//cut the ties
	}
	return *this;
}
template <typename T>
List<T>& List<T>::operator = (const List<T>& rhs)			//copy assignment operator
{
	if (this != &rhs) {
		Purge();			//clear the items

		if (rhs.m_head != nullptr) {				//if there is data to be copied
			m_head = new Node<T>(*rhs.m_head);		//copy m_head 
			m_tail = m_head;							//set m_tail
			if (m_head->m_next != nullptr) {			//if there is more than one node in the list

				Node<T>* trail = new Node<T>(*m_head->m_next);		//copy the next node
				trail->m_prev = m_head;								//set the previous to be m_head
				m_head->m_next = trail;								//set head next to be new node

				while (trail->m_next != nullptr) {							//while there is data to be copied
					Node<T>* travel = new Node<T>(*trail->m_next);				//create a new node 
					travel->m_prev = trail;										//set that node's previous to be the previous tail
					trail->m_next = travel;										//set the previous tail to point at the new node
					trail = travel;												//set the new tail
				}

				m_tail = trail;										//set the tail pointer to the end of the list
			}

		}
	}
	return *this;
}

template <typename T>
bool List<T>::isEmpty()									//is the list empty?
{
	return (m_head == nullptr);
}

template <typename T>
const T& List<T>::First()								//returns data of first element as a const reference 
{
	if (m_head == nullptr) {
		throw(Exception("List empty"));
	}
	return m_head->m_data;
}

template <typename T>
const T& List<T>::Last()								//returns data of last element as a const reference
{
	if (m_head == nullptr) {
		throw(Exception("List empty"));
	}
	return m_tail->m_data;
}
template <typename T>
void List<T>::Prepend(T data)							//prepend the list with data
{
	if (m_head == nullptr) {					//if prepending an empty list
		m_head = new Node<T>(data);
		m_tail = m_head;						//create a new node and set both m_head and m_tail 
	}
	else {										//if the list has data
		Node<T>* temp = new Node<T>(data);
		m_head->m_prev = temp;					//create a new node and set the previous head to point back at it
		temp->m_next = m_head;					//new node points at previous head
		m_head = temp;							//set the new node to be the first node in the list
	}
}

template <typename T>
void List<T>::Append(T data)							//append the list with data
{
	if (m_tail == nullptr) {				//if appending an empty list
		m_tail = new Node<T>(data);
		m_head = m_tail;					//create a new node, and set it to be both tail and head
	}
	else {
		Node<T>* temp = new Node<T>(data);		//if appending a non empty list
		m_tail->m_next = temp;					//create a new node, set it to point at the previous tail and the previous
		temp->m_prev = m_tail;					//tail to point at it
		m_tail = temp;							//set it to be the new tail
	}
}

template <typename T>
void List<T>::Purge()									//delete all items in the list
{
	while (m_head != nullptr) {				
		Node<T>* temp = m_head->m_next;
		delete m_head;						//traverse the list and delete all data
		m_head = temp;
	}
	m_tail = nullptr;									//set m_tail to nullptr
}

template <typename T>
void List<T>::Extract(T node)							//delete a single item in the list
{
	if (isEmpty()) {
		throw(Exception("List Empty!"));
	}
	else {
		if (m_head->m_data == node && m_head->m_next != nullptr) {			//more than one item in the list, head is to be deleted
			Node<T>* temp = m_head;
			m_head = m_head->m_next;
			m_head->m_prev = nullptr;
			delete temp;
		}
		else if (m_head->m_data == node) {					//only one item in the list, it contains the data to be deleted
			delete m_head;
			m_tail = nullptr;
			m_head = nullptr;
		}
		else if (m_tail->m_data == node) {					//more than one item in the list, tail contains data to be deleted
			Node<T>* temp = m_tail->m_prev;
			delete m_tail;
			m_tail = temp;
			m_tail->m_next = nullptr;
		}
		else {
			Node<T>* temp = m_head;
			while (temp->m_next != nullptr && temp->m_data != node) {				//while temp pointer is not at the end of the list, search through the list
				temp = temp->m_next;
			}

			if (temp->m_data == node) {			//if the data is found, it will be in the middle of the list
				Node<T>* trail = temp->m_prev;
				Node<T>* travel = temp->m_next;
				travel->m_prev = trail;
				trail->m_next = travel;						

				delete temp;
			}

			else {
				throw(Exception("Data not found"));
			}
		}
	}
}

template <typename T>
void List<T>::InsertAfter(T new_item, T old_item)		//append a node in the list
{
	if (isEmpty()) {
		throw(Exception("List is empty"));
	}

	else {
		if (m_head->m_data == old_item) {			//if the first node is to be appended
			Node<T>* nn = new Node<T>(new_item);
			if (m_head->m_next == nullptr) {		//if there is only one item in the list
				m_head->m_next = nn;
				nn->m_prev = m_head;				//append the list
				m_tail = nn;						//set the new node to m_tail
			}

			else {
				nn->m_prev = m_head;					//otherwise, set the new node to point back at m_head
				nn->m_next = m_head->m_next;			//set the new node to point at the node after m_head
				m_head->m_next = nn;					//set head to point at the new node
				nn->m_next->m_prev = nn;				//set the node after new node to point back at new node
			}
		}
		else if (m_tail->m_data == old_item) {
			Append(new_item);
		}
		else {
			Node<T>* travel = m_tail;						//start at the end of the list
			Node<T>* trail = m_tail;	
			while (travel->m_data != old_item && travel->m_next != nullptr) {
				trail = travel;
				travel = travel->m_prev;
			}

			if (travel->m_data == old_item) {		//if the data to be appended is found
				Node<T>* nn = new Node<T>(new_item);
				trail->m_prev = nn;
				nn->m_next = trail;
				nn->m_prev = travel;
				travel->m_next = nn;				
			}

			else {									//otherwise, exception
				throw(Exception("Data to prepend not found"));
			}
		}
	}
}


template <typename T>
void List<T>::InsertBefore(T new_item, T old_item)		//prepend a node in the list	
{
	if (isEmpty()) {
		throw(Exception("List is empty"));
	}

	else {
		if (m_head->m_data == old_item) {			//if the first node is to be prepended, prepend the whole list
			Prepend(new_item);
		}
		else if (m_tail->m_data == old_item) {		//if the last node is to be prepended
			if (m_tail->m_prev == nullptr) {			//if there is only one node in the list, prepend the whole list
				Prepend(new_item);
			}
			else {
				Node<T>* nn = new Node<T>(new_item);		//otherwise, prepend the tail node
				Node<T>* trail = m_tail->m_prev;
				trail->m_next = nn;
				nn->m_prev = trail;
				m_tail->m_prev = nn;
				nn->m_next = m_tail;
			}
		}
		else {								//if the node to be prepended is in the middle of the list
			Node<T>* travel = m_head;
			Node<T>* trail = m_head;
			while (travel->m_data != old_item && travel->m_next != nullptr) {
				trail = travel;
				travel = travel->m_next;
			}								//find the node (or hit the end of the list

			if (travel->m_data == old_item) {
				Node<T>* nn = new Node<T>(new_item);
				travel->m_prev = nn;			//prepend the found node
				trail->m_next = nn;
				nn->m_next = travel;
				nn->m_prev = trail;
			}

			else {
				throw(Exception("Data to prepend not found"));
			}
		}
	}
}


template <typename T>
Node<T>* List<T>::getHead()								//return m_head
{
	return m_head;
}

template <typename T>
Node<T>* List<T>::getTail()								//return m_tail
{
	
	return m_tail;
}

template <typename T>
void List<T>::PrintForwards()							//print list from head to tail
{
	Node<T>* trail = m_head;							//start at the beginnning of list
	while (trail != nullptr) {
		cout << trail->m_data << endl;					//print m_data
		trail = trail->m_next;							//go to the next node
	}
}

template <typename T>
void List<T>::PrintBackwards()							//print list from tail to head
{
	Node<T>* trail = m_tail;							//start at the end of the list
	while (trail != nullptr) {
		cout << trail->m_data << endl;					//print m_data
		trail = trail->m_prev;							//go to the next node
	}
}