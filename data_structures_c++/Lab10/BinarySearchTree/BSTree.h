/***************************************************
*
* File name: BSTree.h
*
* Author: Zaelfenn Sandow
*
* Date created: May 3rd, 2024
*
* File purpose: This file declares and defines the
* Binary Search Tree class, using a templated Node class
* to do so. 
*
*
****************************************************/

#pragma once

#include "BSNode.h"
#include "Queue.h"

template<typename T>
class BSNode;

/******************************************
* Class Binary Search Tree
* 
* Manager Functions:
*				Default Ctor	
*				Value Ctor
*				Move Ctor
*				Copy Ctor
*				Move Assignment Operator
*				Copy Assignment Operator
*				Destructor
* 
* Public Methods:
*				Insert
*				Delete
*				Purge
*				Height
*				InOrder
*				PostOrder
*				PreOrder
* 
*********************************************/
template<typename T>
class BSTree {
	friend class BSNode<T>;
public:

	//MANAGER FUNCTIONS

	BSTree();	
	BSTree(T root);
	BSTree(BSTree&& copy)noexcept;
	BSTree(const BSTree& copy);
	BSTree& operator = (BSTree&& rhs)noexcept;
	BSTree& operator = (const BSTree& rhs);
	~BSTree();



	//PUBLIC INTERFACE FOR FUNCTIONS THAT REQUIRE A NODE CLASS

	void Insert(T data);
	void Delete(T data);
	void Purge();
	int Height();
	void InOrder(void(*function)(T data));
	void PostOrder(void(*function)(T data));
	void PreOrder(void(*function)(T data));
	void BreadthFirst(void(*function)(T data));

	BSNode<T>* getRoot();				//test function to return m_root
	T getRootData();				//test function to return m_root->m_data
private:
	//FUNCTIONS THAT REQUIRE USE OF PRIVATE NODE CLASS

	void Insert(BSNode<T>* root, T data);
	void Delete(BSNode<T>* root);
	int Height(BSNode<T>* root);
	void InOrder(BSNode<T>* root, void(*function)(T data));
	void PostOrder(BSNode<T>* root, void(*function)(T data));
	void PreOrder(BSNode<T>* root, void(*function)(T data));
	void BreadthFirst(BSNode<T>* root, void(*function)(T data));

	void CopyAll(BSNode<T>* rhs);

	//ROOT OF THE TREE
	BSNode<T>* m_root;


};


/*************************************
*
*
* Function: default ctor
*
*
* Purpose: create an empty tree
*
*
*************************************/
template<typename T>
BSTree<T>::BSTree() : m_root(nullptr)
{}

/*************************************
*
*
* Function: value ctor
*
*
* Purpose: create a tree that has a 
* root node of the passed in value. 
*
*
*************************************/
template<typename T>
BSTree<T>::BSTree(T root) : m_root(nullptr)
{
	m_root = new BSNode<T>(root);
}

/*************************************
*
*
* Function: move ctor
*
*
* Purpose: set the lhs to the same values
* as rhs. move pointer of rhs to point at 
* nothing, so that the tree is moved and 
* not deleted. 
*
*
*************************************/
template<typename T>
BSTree<T>::BSTree(BSTree&& copy)noexcept : m_root(copy.m_root)
{
	copy.m_root = nullptr;
}

/*************************************
*
*
* Function: copy ctor
*
*
* Purpose: copy all of the values of 
* the passed in tree to the newly created
* tree. 
*
*
*************************************/
template<typename T>
BSTree<T>::BSTree(const BSTree& copy) : m_root(nullptr)
{
	CopyAll(copy.m_root);
}

/*************************************
*
*
* Function: move assignment operator
*
*
* Purpose: move the right hand side values
* to the left hand side. Right hand side should
* stop pointing at root. 
*
*
*************************************/
template<typename T>
BSTree<T>& BSTree<T>::operator = (BSTree&& rhs)noexcept
{
	if (this != &rhs) {
		if (m_root != nullptr) {
			Purge();
		}
		m_root = rhs.m_root;
		rhs.m_root = nullptr;
	}
	return *this;
}

/*************************************
*
*
* Function: copy assignment operator
*
*
* Purpose: copy all of the nodes from 
* the right hand side over to the left
* hand side. 
*
*
*************************************/
template<typename T>
BSTree<T>& BSTree<T>::operator = (const BSTree& rhs)
{
	if (this != &rhs) {
		if (m_root != nullptr) {
			Purge();
	}
		CopyAll(rhs.m_root);
	}

	return *this;
}

/*************************************
*
*
* Function: dtor
*
*
* Purpose: Delete every node in the tree. 
* reset member variables to default values. 
*
*
*************************************/
template<typename T>
BSTree<T>::~BSTree()
{
	if (m_root != nullptr)
		Purge();
}

/*************************************
*
*
* Function: Insert
*
*
* Purpose: pass in data to insert into 
* the list in order. Will create a root 
* node if one does not yet exist. 
*
*
*************************************/
template<typename T>
void BSTree<T>::Insert(T data)
{
	Insert(m_root, data);
}

/*************************************
*
*
* Function: Delete
*
*
* Purpose: find and delete the passed in 
* data. Will throw exceptions if the data
* isn't found, or if the tree is empty.
*
*
*************************************/
template<typename T>
void BSTree<T>::Delete(T data)
{
	if (m_root == nullptr)
		throw(Exception("Error: CANNOT DELETE FROM EMPTY LIST"));
	BSNode<T>* travel = m_root;
	while (travel != nullptr && travel->m_data != data) {
		if (travel->m_data > data) {
			travel = travel->m_left;
		}
		else if (travel->m_data < data) {
			travel = travel->m_right;
		}
	}
	if (travel == nullptr) {
		throw(Exception("Error: DATA NOT FOUND"));
	}
	else {
		Delete(travel);
	}
}

/*************************************
*
*
* Function: Purge
*
*
* Purpose: delete all existing nodes
* and set root node to nullpointer.
*
*
*************************************/
template<typename T>
void BSTree<T>::Purge()
{
	if (m_root != nullptr)
		m_root->Purge();
	else
		throw(Exception("Error: Cannot purge an empty tree"));
	m_root = nullptr;
}

/*************************************
*
*
* Function: Height
*
*
* Purpose: return the height of the tree.
*
*
*************************************/
template<typename T>
int BSTree<T>::Height()
{
	return Height(m_root);
}

/*************************************
*
*
* Function: InOrder
*
*
* Purpose: Execute a passed in function
* on every node in the tree, from the 
* node lowest in value to the node
* highest in value. Will throw an 
* exception if the tree is empty. 
*
*
*************************************/
template<typename T>
void BSTree<T>::InOrder(void(*function)(T data))
{
	if (m_root != nullptr)
		InOrder(m_root, function);
	else
		throw(Exception("Error: CANNOT TRAVERSE EMPTY TREE"));
}

/*************************************
*
*
* Function: PreOrder
*
*
* Purpose: Excecute a passed in function
* on every node, from root to left to right.
* Will throw an exception on the case of an 
* empty tree. 
*
*
*************************************/
template<typename T>
void BSTree<T>::PreOrder(void(*function)(T data))
{
	if (m_root != nullptr)
		PreOrder(m_root, function);
	else
		throw(Exception("Error: CANNOT TRAVERSE EMPTY TREE"));
}

/*************************************
*
*
* Function: PostOrder
*
*
* Purpose: Execute a passed in function 
* on every node, from m_left to m_right
* to root. Will throw exception in the 
* case of an empty tree. 
*
*
*************************************/
template<typename T>
void BSTree<T>::PostOrder(void(*function)(T data))
{
	if (m_root != nullptr)
		PostOrder(m_root, function);
	else
		throw(Exception("Error: CANNOT TRAVERSE EMPTY TREE"));
}


/*************************************
*
*
* Function: Insert
*
*
* Purpose: Using m_root, data passed
* in by a client will be used to grow
* the tree. The data is to be inserted
* in order from lowest on the left to 
* greates on the right. 
*
*
*************************************/
template<typename T>
void BSTree<T>::Insert(BSNode<T>* root, T data)
{
	if (m_root == nullptr) {
		BSNode<T>* nn = new BSNode<T>(data);
		m_root = nn;
	}
	else {
		if (root->m_data > data) {							//go left
			if (root->m_left != nullptr) {
				Insert(root->m_left, data);
			}
			else {
				BSNode<T>* nn = new BSNode<T>(data);
				root->m_left = nn;
			}
		}
		else {												//go right
			if (root->m_right != nullptr) {
				Insert(root->m_right, data);
			}
			else {
				BSNode<T>* nn = new BSNode<T>(data);
				root->m_right = nn;
			}
		}
	}
}

/*************************************
*
*
* Function: Delete
*
*
* Purpose: Using a passed in node, 
* reorganize the tree as needed 
* to delete the node. 
*
*
*************************************/
template<typename T>
void BSTree<T>::Delete(BSNode<T>* root)
{

		if (root->m_left != nullptr) {			//check if there is a left subtree for the root
			BSNode<T>* travel = root->m_left;
			BSNode<T>* trail = nullptr;
			while (travel->m_right != nullptr) {		//traverse the left subtree
				trail = travel;
				travel = travel->m_right;
			}
			if (trail == nullptr) {						//if there is nothing to the right
				root->m_left = travel->m_left;
				root->m_data = travel->m_data;
				delete travel;
			}
			else {										//otherwise, replace lowest level of data with current 
				trail->m_right = travel->m_left;
				root->m_data = travel->m_data;
				delete travel;
			}
		}
		else if (root->m_right != nullptr) {		//if no left tree, check for right subtree 
			BSNode<T>* travel = root->m_right;
			BSNode<T>* trail = nullptr;
			while (travel->m_left != nullptr) {			//traverse the directory of root
				trail = travel;
				travel = travel->m_left;
			}
			if (trail == nullptr) {
				root->m_right = travel->m_right;
				root->m_data = travel->m_data;
				delete travel;
			}
			else {
				trail->m_left = travel->m_right;
				root->m_data = travel->m_data;
				delete travel;
			}
		}
		else {										//if it is a leaf, just delete it
			delete root;
			root = nullptr;
		}
}

/*************************************
*
*
* Function: Height
*
*
* Purpose: Using m_root, calculate the
* height of the tree. 
*
*
*************************************/
template<typename T>
int BSTree<T>::Height(BSNode<T>* root)					//calculate height of the tree
{
	int retVal = 0;
	if (m_root != nullptr) {
		if (root->m_left != nullptr) {
			int temp = Height(root->m_left) + 1;
			if (retVal < temp) {
				retVal = temp;
			}
		}

		if (root->m_right != nullptr) {
			int temp = Height(root->m_right) + 1;
			if (retVal <= temp) {
				retVal = temp;
			}
		}
	}
	else
		throw(Exception("Error: CANNOT GIVE HEIGHT OF EMPTY TREE"));
	return retVal;
}

/*************************************
*
*
* Function: InOrder
*
*
* Purpose: Perform a passed in function
* on every node in the tree, recursively
* calling this function so that the order
* of the nodes is m_left, root, m_right. 
*
*
*************************************/
template<typename T>
void BSTree<T>::InOrder(BSNode<T>* root, void(*function)(T data))			//m_left then root then m_right
{
	if (root->m_left != nullptr) {
		InOrder(root->m_left, function);
	}

	function(root->m_data);

	if (root->m_right != nullptr) {
		InOrder(root->m_right, function);
	}

}

/*************************************
*
*
* Function: PostOrder
*
*
* Purpose: Recursively call this function
* to perform the passed in function on
* every node, from left to right to root.
*
*
*************************************/
template<typename T>
void BSTree<T>::PostOrder(BSNode<T>* root, void(*function)(T data)) //m_left then m_right then root
{
	if (root->m_left != nullptr) {
		PostOrder(root->m_left, function);
	}
	if (root->m_right != nullptr) {
		PostOrder(root->m_right, function);
	}

	function(root->m_data);
}

/*************************************
*
*
* Function: PreOrder
*
*
* Purpose: Recursively call this function 
* to perform the passed in function on
* every node, in the order of root to left
* to right. 
*
*
*************************************/
template<typename T>
void BSTree<T>::PreOrder(BSNode<T>* root, void(*function)(T data))	//root then m_left then m_right
{
	function(root->m_data);

	if (root->m_left != nullptr) {
		PreOrder(root->m_left, function);
	}

	if (root->m_right != nullptr) {
		PreOrder(root->m_right, function);
	}
}

/*************************************
*
*
* Function: getRoot
*
*
* Purpose: used as a test function to 
* ensure that a list is created.
*
*
*************************************/
template<typename T>
BSNode<T>* BSTree<T>::getRoot() {
	return m_root;
}

/*************************************
*
*
* Function: getRootData
*
*
* Purpose: used as a test function to ensure
* that a list is created with the proper data
* in root. 
*
*
*************************************/
template<typename T>
T BSTree<T>::getRootData() {
	return m_root->m_data;
}

/*************************************
*
*
* Function: CopyAll
*
*
* Purpose: Used to recursively insert every
* node from one tree to another. 
*
*
*************************************/
template<typename T>
void BSTree<T>::CopyAll(BSNode<T>* rhs) {
	if (rhs != nullptr) {
		Insert(rhs->m_data);

		if (rhs->m_left != nullptr) {
			CopyAll(rhs->m_left);
		}

		if (rhs->m_right != nullptr) {
			CopyAll(rhs->m_right);
		}
	}
}

/*************************************
*
*
* Function: BreadthFirst
*
*
* Purpose: Perform the passed in function
* on every node in the tree, from top to
* bottom and left to right. Will throw
* an exception when used on an empty list. 
*
*
*************************************/
template<typename T>
void BSTree<T>::BreadthFirst(void(*function)(T data))
{
	if (m_root != nullptr)
		BreadthFirst(m_root, function);
	else
		throw(Exception("Error: CANNOT TRAVERSE EMPTY LIST"));
}

/*************************************
*
*
* Function: BreadthFirst
*
*
* Purpose: Perform the passed in function
* on every node in the tree. The order of 
* this should be from top to bottom, left to 
* right. This will be implemented using a list,
* and enqueuing the children of any dequeued node. 
*
*
*************************************/
template<typename Q>
void BSTree<Q>::BreadthFirst(BSNode<Q>* root, void(*function)(Q data))
{
	Queue<BSNode<Q>*> q;
	q.Enqueue(m_root);
	while (!q.isEmpty()) {
		BSNode<Q>* cd = q.Dequeue();
		if (cd->m_left != nullptr) {
			q.Enqueue(cd->m_left);
		}
		if (cd->m_right != nullptr) {
			q.Enqueue(cd->m_right);
		}

		function(cd->m_data);
	}
}
