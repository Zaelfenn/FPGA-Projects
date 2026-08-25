/***************************************************
* 
* File name: BSNode.h
* 
* Author: Zaelfenn Sandow
* 
* Date created: May 3rd, 2024
* 
* File purpose: This file declares and defines the 
* node class which is used for the binary search tree.
* 
* 
****************************************************/

#pragma once

#include "Exception.h"
#include "BSTree.h"

template<typename T>
class BSTree;


template<typename T>
class BSNode {
	friend class BSTree<T>;
private:

	BSNode();
	BSNode(T data);
	BSNode(const BSNode& copy);
	BSNode& operator = (const BSNode& rhs);
	
	~BSNode();

	void Purge();

	BSNode* m_left;
	BSNode* m_right;
	T m_data;
};

/*************************************
* 
* 
* Function: default ctor
* 
* 
* Purpose: set default values for 
* data, right, and left.
* 
* 
*************************************/
template<typename T>
BSNode<T>::BSNode() : m_data(T()), m_right(nullptr), m_left(nullptr)
{}

/*************************************
*
*
* Function: value ctor
*
*
* Purpose: set value of data to passed
* in value, and set right and left to 
* nullpointer.
*
*
*************************************/
template<typename T>
BSNode<T>::BSNode(T data) : m_data(data), m_right(nullptr), m_left(nullptr)
{}

/*************************************
*
*
* Function: copy ctor
*
*
* Purpose: set the value of this node
* to the same as the passed in node. 
*
*
*************************************/
template<typename T>
BSNode<T>::BSNode(const BSNode& copy) : m_data(copy.m_data), m_right(copy.m_right), m_left(copy.m_right)
{}

/*************************************
*
*
* Function: copy assignment operator
*
*
* Purpose: set the values of the lhs
* to rhs. 
*
*
*************************************/
template<typename T>
BSNode<T>& BSNode<T>::operator = (const BSNode& rhs)
{
	if (this != rhs) {
		m_data = rhs.m_data;
		m_left = rhs.m_left;
		m_right = rhs.m_right;
	}
	return *this;	
}

/*************************************
*
*
* Function: dtor
*
*
* Purpose: reset values to default. 
*
*
*************************************/
template<typename T>
BSNode<T>::~BSNode()
{
	m_left = nullptr;
	m_right = nullptr;
	m_data = T();
}

/*************************************
*
*
* Function: Purge
*
*
* Purpose: delete this node, and any 
* nodes connected to it. 
*
*
*************************************/
template<typename T>
void BSNode<T>::Purge()
{
	if (m_left != nullptr) {
		m_left->Purge();
	}
	if (m_right != nullptr) {
		m_right->Purge();
	}
	delete this;
}

