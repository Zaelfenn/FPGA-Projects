#pragma once

#include "Graph.h"
template <typename V, typename E>
class Graph;
#include "Edge.h"
template <typename V, typename E>
class Edge;
#include "list"
using std::list;
#include "iterator"
using std::iterator;

/*******************************
*
* Class: Vertex
*
* Manager functions:
*		Default Ctor
*		Value Ctor
*		Move Ctor
*		Copy Ctor
*		Dtor
*		Move Assignment Operator
*		Copy Assignment Operator
*
*
* Member functions:
*		getEdges
*		getIndex
*		getData
*		setProcessed
*		getProcessed
*
*********************************/
template <typename V, typename E>
class Vertex {
friend class Edge<V, E>;
friend class Graph<V, E>;

public:
	Vertex();
	Vertex(V data, int index);
	Vertex(Vertex&& copy);
	Vertex(const Vertex& copy);
	~Vertex();
	Vertex& operator = (Vertex&& rhs);
	Vertex& operator = (const Vertex& rhs);

	list<Edge<V,E>>& getEdges();
	int getIndex();
	V getData();
	void setProcessed();
	bool getProcessed();
private:
	


	void CreateEdge(Vertex& dest, E data, int weight);
	void RemoveEdge(Vertex& dest);
	bool m_processed;								//whether this vertex has been hit by a function or not
	V m_data;										//data that this vertex holds
	int m_index;
	list<Edge<V, E>> m_edges;						//what this vertex connects to
};

/*****************************
* function: Default Ctor
*
* purpose: set data members to
* default values. 
*
******************************/
template <typename V, typename E>
Vertex<V, E>::Vertex() : m_processed(false), m_data(V()), m_edges(list<Edge<V,E>>()), m_index(0)
{}

/*****************************
* function: Value Ctor
*
* purpose: set m_data to passed 
* in value, and keep m_processed
* and m_edges at default values.
*
******************************/
template <typename V, typename E>
Vertex<V, E>::Vertex(V data, int index) : m_processed(false), m_data(data), m_edges(list<Edge<V, E>>()), m_index(index)
{}

/*****************************
* function: Move Ctor
*
* purpose: copy the data members
* from the passed in vertex. 
*
******************************/
template <typename V, typename E>
Vertex<V, E>::Vertex(Vertex&& copy) : m_processed(copy.m_processed), m_data(copy.m_data), m_edges(copy.m_edges), m_index(copy.m_index)
{}

/*****************************
* function: Copy Ctor
*
* purpose: copy the data members
* from the passed in vertex.
*
******************************/
template <typename V, typename E>
Vertex<V, E>::Vertex(const Vertex& copy) : m_processed(copy.m_processed), m_data(copy.m_data), m_edges(copy.m_edges), m_index(copy.m_index)
{}

/*****************************
* function: Dtor
*
* purpose: reset data members
* to default values.
*
******************************/
template <typename V, typename E>
Vertex<V, E>::~Vertex() 
{
	m_processed = false;
	m_data = V();
	m_edges.clear();
	m_index = 0;
}

/*****************************
* function: Move Operator
*
* purpose: copy the data members
* from the passed in vertex.
*
******************************/
template <typename V, typename E>
Vertex<V, E>& Vertex<V, E>::operator = (Vertex&& rhs)
{
	if (this != &rhs) {
		m_edges.clear();
		m_processed = rhs.m_processed;
		m_data = rhs.m_data;
		m_edges = rhs.m_edges;
		m_index = rhs.m_index;
	}
	
	return *this;
}


/*****************************
* function: Copy Operator
*
* purpose: copy the data members
* from the passed in vertex.
*
******************************/
template <typename V, typename E>
Vertex<V, E>& Vertex<V, E>::operator = (const Vertex& rhs)
{
	if (this != &rhs) {
		m_edges.clear();
		m_processed = rhs.m_processed;
		m_data = rhs.m_data;
		m_edges = rhs.m_edges;
		m_index = rhs.m_index;
	}

	return *this;
}


/*****************************
* function: CreateEdge
*
* purpose: Create an edge between
* this vertex and the passed in destination
* using the passed in data and weight. 
* Throw an error if an edge between these
* two already exists.
*
******************************/
template <typename V, typename E>
void Vertex<V, E>::CreateEdge(Vertex& dest, E data, int weight)
{
	if (!m_edges.empty()) {
		typename list<Edge<V, E>>::iterator i;
		bool found = false;
		for (i = m_edges.begin(); i != m_edges.end() && !found; ++i) {
			if (i->m_destination->m_data == dest.m_data) {
				found = true;
			}
		}
		if (found)
			throw(Exception("Error: cannot add more than one edge between two vertices"));
	}
	Edge<V, E> ne(&dest, weight, data);
	m_edges.push_back(ne);
}


/*****************************
* function: RemoveEdge
*
* purpose: remove any edges in
* the list that point to the
* passed in destination.
*
******************************/
template <typename V, typename E>
void Vertex<V, E>::RemoveEdge(Vertex& dest)
{
	typename list<Edge<V, E>>::iterator i;
	bool found = false;
	bool sub = false;
	for (i = m_edges.begin(); i != m_edges.end() && !found; ++i) {
		if (i->m_destination == &dest) {
			found = true;
			if (i == m_edges.end()) {
				--i;
				sub = true;
			}
		}
	}

	if (found) {
		if (!sub) {
			--i;
		}
		m_edges.erase(i);
	}
}

/**********************************
* Function Name: getEdges
* 
* Purpose: return the list of 
* edges by reference.
* 
**********************************/
template <typename V, typename E>
list<Edge<V,E>>& Vertex<V,E>::getEdges()
{
	return m_edges;
}

/**********************************
* Function Name: getIndex
*
* Purpose: return the index member
* variable.
*
**********************************/
template <typename V, typename E>
int Vertex<V, E>::getIndex()
{
	return m_index;
}

/**********************************
* Function Name: getData
*
* Purpose: return the data 
* member variable
*
**********************************/
template <typename V, typename E>
V Vertex<V, E>::getData()
{
	return m_data;
}

/**********************************
* Function Name: setProcessed
*
* Purpose: set the "processed"
* member to true
*
**********************************/
template <typename V, typename E>
void Vertex<V, E>::setProcessed()
{
	m_processed = true;;
}

/**********************************
* Function Name: getProcessed
*
* Purpose: return the state of the
* m_processed member variable
*
**********************************/
template <typename V, typename E>
bool Vertex<V,E>::getProcessed()
{
	return m_processed;
}
