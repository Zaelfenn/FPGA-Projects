#pragma once

#include "Exception.h"
#include "Vertex.h"
template<typename V, typename E>
class Vertex;
#include <queue>
using std::queue;
#include<stack>
using std::stack;
#include "list"
using std::list;
#include "iterator"
using std::iterator;

/*******************************
*
* Class: Graph
*
* Manager functions:
*		Default Ctor
*		Move Ctor
*		Copy Ctor
*		Dtor
*		Move Assignment Operator
*		Copy Assignment Operator
*		
*
* Member functions:
*		InsertVertex
*		DeleteVertex
*		InsertArc
*		DeleteArc
*		DepthFirst
*		BreadthFirst
*		isEmpty
*		getCount
*		getVertices
*		findVertex
*		allProcessed
*		
*		Subscript Operator
*
*********************************/
template <typename V, typename E>
class Graph {
friend class Vertex<V, E>;
public:
	Graph();
	Graph(Graph&& copy)noexcept;
	Graph(const Graph& copy);
	~Graph();

	Graph& operator = (Graph&& rhs)noexcept;
	Graph& operator = (const Graph& rhs);

	void InsertVertex(V data);
	void DeleteVertex(V data);

	void InsertArc(V from, V to, E edge, int weight);
	void DeleteArc(V from, V to);

	void DepthFirst(void(*vist)(V data));
	void BreadthFirst(void(*visit)(V data));
	bool isEmpty();

	int getCount();

	list<Vertex<V, E>>& getVertices();

	Vertex<V, E>& findVertex(V data);

	bool allProcessed();

	Vertex<V, E>& operator [] (int index);
private:
	void ClearFlags();
	int m_count;						//count of all total nodes
	list<Vertex<V, E>> m_nodes;			//all nodes
};

/*****************************
* function: Default Ctor
*
* purpose: initialize a new graph 
* with default values. count of 0
* and empty list of vertex pointers. 
*
******************************/
template <typename V, typename E>
Graph<V, E>::Graph() : m_count(0), m_nodes(list<Vertex<V,E>>())
{}

/*****************************
* function: Move Ctor
*
* purpose: intialize a new graph
* with the same count of vertexes. 
* move old vertex list over, and 
* remove the connection from the
* original graph. 
*
******************************/
template <typename V, typename E>
Graph<V, E>::Graph(Graph&& copy) noexcept: m_count(copy.m_count), m_nodes(copy.m_nodes)
{
	if (!m_nodes.empty()) {
		typename list<Vertex<V, E>>::iterator i;
		typename list<Edge<V, E>>::iterator j;
		for (i = m_nodes.begin(); i != m_nodes.end(); ++i) {
			if (!i->m_edges.empty()) {
				for (j = i->m_edges.begin(); j != i->m_edges.end(); ++j) {
					j->setDestination(findVertex(j->getDestination().m_data));
				}
			}
		}

	}
}

/*****************************
* function: Copy Ctor
*
* purpose: initialize a new graph
* with the same count of vertices.
* copy the list of vertices over, 
* and adjust edge pointers to point
* at the new list. 
*
******************************/
template <typename V, typename E>
Graph<V, E>::Graph(const Graph& copy) : m_count(copy.m_count), m_nodes(copy.m_nodes)
{
	if (!m_nodes.empty()) {
		typename list<Vertex<V, E>>::iterator i;
		typename list<Edge<V, E>>::iterator j;
		for (i = m_nodes.begin(); i != m_nodes.end(); ++i) {
			if (!i->m_edges.empty()) {
				for (j = i->m_edges.begin(); j != i->m_edges.end(); ++j) {
					j->setDestination(findVertex(j->getDestination().m_data));
				}
			}
		}

	}
}

/*****************************
* function: Dtor
*
* purpose: reset data members
* to default values.
*
******************************/
template <typename V, typename E>
Graph<V, E>::~Graph()
{
	m_count = 0;
	while (!m_nodes.empty()) {
		Vertex<V, E> temp = m_nodes.front();
		temp.m_edges.clear();
		m_nodes.pop_front();
	}
}

/*****************************
* function: Move Assignment Operator
*
* purpose: copy data member values
* from rhs. make sure all edges
* are pointing at the appropriate
* vertexes. 
*
******************************/
template <typename V, typename E>
Graph<V, E>& Graph<V, E>::operator = (Graph&& rhs)noexcept
{
	if (this != &rhs) {
		while (!m_nodes.empty()) {
			Vertex<V, E> temp = m_nodes.front();
			temp.m_edges.clear();
			m_nodes.pop_front();
		}
		m_count = rhs.m_count;
		m_nodes = rhs.m_nodes;
		if (!m_nodes.empty()) {
			typename list<Vertex<V, E>>::iterator i;
			typename list<Edge<V, E>>::iterator j;
			for (i = m_nodes.begin(); i != m_nodes.end(); ++i) {
				if (!i->m_edges.empty()) {
					for (j = i->m_edges.begin(); j != i->m_edges.end(); ++j) {
						j->setDestination(findVertex(j->getDestination()));
					}
				}
			}
		
		}
	}

	return *this;
}

/*****************************
* function: Copy Assignment Operator
*
* purpose: copy data member values
* from rhs. change pointers for all
* edges to point to new vertexes.
*
******************************/
template <typename V, typename E>
Graph<V, E>& Graph<V, E>::operator = (const Graph& rhs)
{
	if (this != &rhs) {
		while (!m_nodes.empty()) {
			Vertex<V, E> temp = m_nodes.front();
			temp.m_edges.clear();
			m_nodes.pop_front();
		}
		m_count = rhs.m_count;
		m_nodes = rhs.m_nodes;
		if (!m_nodes.empty()) {
			typename list<Vertex<V, E>>::iterator i;
			typename list<Edge<V, E>>::iterator j;
			for (i = m_nodes.begin(); i != m_nodes.end(); ++i) {
				if (!i->m_edges.empty()) {
					for (j = i->m_edges.begin(); j != i->m_edges.end(); ++j) {
						j->setDestination(findVertex(j->getDestination()));
					}
				}
			}

		}
	}

	return *this;
}

/*****************************
* function: InsertVertex
*
* purpose: create a new vertex 
* and add it to the end of the 
* m_nodes list. 
*
******************************/
template <typename V, typename E>
void Graph<V, E>::InsertVertex(V data)
{
	Vertex<V, E> nv(data, m_count);
	m_nodes.push_back(nv);
	m_count += 1;
}

/*****************************
* function: DeleteVertex
*
* purpose: Delete a vertex and all
* edges which point to that vertex. 
*
******************************/
template<typename V, typename E>
void Graph<V, E>::DeleteVertex(V data)
{	
	typename list<Vertex<V, E>>::iterator i;
	for (i = m_nodes.begin(); i != m_nodes.end(); ++i)
		i->RemoveEdge(findVertex(data));
	
	bool found = false;
	bool sub = false;
	for (i = m_nodes.begin(); !found; ++i) {
		if (i->m_data == data) {
			found = true;
			if (i == m_nodes.end()) {
				--i;
				sub = true;
			}
		}
	}
	if (!sub) {
		--i;
	}
	m_nodes.erase(i);

	m_count -= 1;
}

/*****************************
* function: InsertArc
*
* purpose: create a new edge using
* the passed in values of to, edge, and 
* weight. insert the edge into the vertex
* "from" list. 
*
******************************/
template <typename V, typename E>
void Graph<V, E>::InsertArc(V from, V to, E edge, int weight)
{
	if (m_nodes.empty())
		throw(Exception("Error: cannot create an edge without vertices"));

	findVertex(from).CreateEdge(findVertex(to), edge, weight);
}

/*****************************
* function: Delete Arc
*
* purpose: delete an edge using
* the starting point and ending point.
*
******************************/
template<typename V, typename E>
void Graph<V, E>::DeleteArc(V from, V to)
{
	if (m_nodes.empty())
		throw(Exception("Error: cannot create an edge without vertices"));

	
	findVertex(from).RemoveEdge(findVertex(to));
}

/*****************************
* function: DepthFirst
*
* purpose: pass in a function. 
* Add the first vertex to a stack.
* Pop the stack, then add all connected
* vertices that have not been processed 
* to the stack. Repeat until all
* vertices have been processed.
*
******************************/
template<typename V, typename E>
void Graph<V, E>::DepthFirst(void(*visit)(V data))
{
	if (!m_nodes.empty()) {
		stack<Vertex<V,E>*> s;
		s.push(&m_nodes.front());
		m_nodes.front().m_processed = true;
		Vertex<V, E>* proc;
		while (!s.empty()) {
			proc = s.top();
			s.pop();
			visit(proc->m_data);
			typename list<Edge<V, E>>::iterator i;
			for (i = proc->m_edges.begin(); i != proc->m_edges.end(); ++i) {
				if (!i->getDestination().m_processed) {
					s.push(&i->getDestination());
					i->getDestination().m_processed = true;
				}
			}
		}
		ClearFlags();
	}

}

/*****************************
* function: BreadthFirst
*
* purpose: pass in a function to
* perform on every vertex in the
* graph, starting from a the first 
* vertex in the list.Then go to
* each connecting vertex, until 
* every reachable point has been
* processed.
*
******************************/
template<typename V, typename E>
void Graph<V, E>::BreadthFirst(void(*visit)(V data))
{
	if (!m_nodes.empty()) {
		queue<Vertex<V, E>*> q;
		q.push(&m_nodes.front());
		m_nodes.front().m_processed = true;
		Vertex<V, E>* proc;
		while (!q.empty()) {
			proc = q.front();
			q.pop();
			visit(proc->m_data);
			typename list<Edge<V, E>>::iterator i;
			for (i = proc->m_edges.begin(); i != proc->m_edges.end(); ++i) {
				if (!i->getDestination().m_processed) {
					q.push(&i->getDestination());
					i->getDestination().m_processed = true;
				}
			}
		}
		ClearFlags();
	}
}


/*****************************
* function: isEmpty
*
* purpose: return true if 
* there are no vertices.
*
******************************/
template<typename V, typename E>
bool Graph<V, E>::isEmpty()
{
	return m_count == 0;
}

/*****************************
* function: getCount
*
* purpose: return the total
* amount of vertices in the 
* graph. 
*
******************************/
template<typename V, typename E>
int Graph<V, E>::getCount()
{
	return m_count;
}

/*****************************
* function: ClearFlags
*
* purpose: clear the processed
* flag of every vertex.
*
******************************/
template<typename V, typename E>
void Graph<V, E>::ClearFlags()
{
	if (!m_nodes.empty()) {
		typename list<Vertex<V, E>>::iterator i;
		for (i = m_nodes.begin(); i != m_nodes.end(); ++i) {
			i->m_processed = false;
		}
	}
}

/*****************************
* function: findVertex
*
* purpose: return the address of 
* a vertex with the passed in
* value as a data member. 
*
******************************/
template<typename V, typename E>
Vertex<V, E>& Graph<V, E>::findVertex(V data)
{
	typename list<Vertex<V, E>>::iterator i;
	if (m_nodes.empty()) {
		throw(Exception("Error: cannot find vertex in empty list"));
	}

	bool found = false;
	Vertex<V, E>* retVal = nullptr;
	for (i = m_nodes.begin(); i != m_nodes.end() && !found; ++i) {
		if (i->m_data == data) {
			found = true;
			retVal = &*i;
		}
	}

	if (!found)
		throw(Exception("Error: vertex not found in list"));

	return *retVal;
}

/*****************************
* function: getVertices 
*
* purpose: return a list of
* all vertices by reference.
* 
******************************/
template<typename V, typename E>
list<Vertex<V, E>>& Graph<V, E>::getVertices()
{
	return m_nodes;
}

/*****************************
* function: allProcessed
*
* purpose: return true if all
* vertices have been processed
*
******************************/
template<typename V, typename E>
bool Graph<V, E>::allProcessed()
{
	bool retVal = true;
	if (!m_nodes.empty()) {
		for (typename list<Vertex<V, E>>::iterator i = m_nodes.begin(); true && i != m_nodes.end(); ++i) {
			if (!i->m_processed)
				retVal = false;
		}
	}

	return retVal;
}

/*****************************
* function: subscript operator
*
* purpose: using an integer, 
* return the related vertex by 
* value. Useful for Dijkstras.
*
******************************/
template<typename V, typename E>
Vertex<V, E>& Graph<V, E>::operator [] (int index)
{
	if (index < 0 || index >= m_count)
		throw(Exception("Error: Trying to access out of bounds"));
	typename list<Vertex<V, E>>::iterator i;
	i = m_nodes.begin();
	while (index != 0) {
		++i;
		--index;
	}

	return *i;
}