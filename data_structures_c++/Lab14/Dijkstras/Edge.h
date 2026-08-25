#pragma once


#include "Vertex.h"
template <typename V, typename E>
class Vertex;

/*******************************
*
* Class: Edge
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
*		getData
*		getWeight
*		getDestination
*		setDestination
*
*********************************/
template<typename V, typename E>
class Edge {
friend class Vertex<V,E>;
public:
	//MANAGER FUNCTIONS

	Edge();
	Edge(Vertex<V, E>* dest, int weight, E data);
	Edge(Edge&& copy);
	Edge(const Edge& copy);
	~Edge();

	Edge& operator = (Edge&& rhs);
	Edge& operator = (const Edge& rhs);

	E getData();
	int getWeight();
	Vertex<V,E>& getDestination();
	void setDestination(Vertex<V, E>& dest);
private:

	

	//DATA MEMBERS

	Vertex<V, E>* m_destination;
	int m_weight;
	E m_data;
};

/*****************************
* function: Default Ctor
*
* purpose: set the value
* of the edge to base values,
* a weight of 0 and default data.
*
******************************/
template<typename V, typename E>
Edge<V, E>::Edge() : m_destination(nullptr), m_weight(0), m_data(E())
{}

/*****************************
* function: Value Ctor
*
* purpose: set the value
* of the edge member variables
* to the passed in values
*
******************************/
template<typename V, typename E>
Edge<V, E>::Edge(Vertex<V,E>* dest, int weight, E data) : m_destination(dest), m_weight(weight), m_data(data)
{}

/*****************************
* function: Move Ctor
*
* purpose: copy the destination,
* weight, and data from a passed 
* in edge. Cut the destination from
* the passed in edge. 
*
******************************/
template<typename V, typename E>
Edge<V, E>::Edge(Edge&& copy) : m_destination(copy.m_destination), m_weight(copy.m_weight), m_data(copy.m_weight)
{
	copy.m_destination = nullptr;
}

/*****************************
* function: Copy Ctor
*
* purpose: copy the destination,
* weight, and data from a passed
* in edge. 
*
******************************/
template<typename V, typename E>
Edge<V, E>::Edge(const Edge& copy) : m_destination(copy.m_destination), m_weight(copy.m_weight), m_data(copy.m_data)
{}

/*****************************
* function: Dtor
*
* purpose: reset data members
* to default values. 
*
******************************/
template<typename V, typename E>
Edge<V, E>::~Edge()
{
	m_destination = nullptr;
	m_weight = 0;
	m_data = E();
}

/*****************************
* function: Move Operator
*
* purpose: copy the destination,
* weight, and data from a passed
* in edge. Cut the destination from
* the passed in edge.
*
******************************/
template<typename V, typename E>
Edge<V,E>& Edge<V, E>::operator = (Edge&& rhs)
{
	if (this != &rhs) {
		m_destination = rhs.m_destination;
		m_weight = rhs.m_weight;
		m_data = rhs.m_data;
		rhs.m_destination = nullptr;
	}
	return *this;
}

/*****************************
* function: Move Operator
*
* purpose: copy the destination,
* weight, and data from a passed
* in edge. 
*
******************************/
template<typename V, typename E>
Edge<V, E>& Edge<V, E>::operator = (const Edge& rhs)
{
	if (this != &rhs) {
		m_destination = rhs.m_destination;
		m_weight = rhs.m_weight;
		m_data = rhs.m_data;
	}
	return *this;
}

/*****************************
* function: getData
*
* purpose: return the path
* of the edge
*
******************************/
template<typename V, typename E>
E Edge<V, E>::getData()
{
	return m_data;
}

/*****************************
* function: getWeight
*
* purpose: return the weight
* of the edge
*
******************************/
template<typename V, typename E>
int Edge<V, E>::getWeight()
{
	return m_weight;
}

/*****************************
* function: getDestinatino
*
* purpose: return the vertex 
* that is being pointed to.
*
******************************/
template<typename V, typename E>
Vertex<V,E>& Edge<V, E>::getDestination()
{
	return *m_destination;
}

/*****************************
* function: setDestination
*
* purpose: set the pointer for 
* the destination to the address
* of a passed in vertex.
*
******************************/
template<typename V, typename E>
void Edge<V, E>::setDestination(Vertex<V, E>& dest)
{
	m_destination = &dest;
}
