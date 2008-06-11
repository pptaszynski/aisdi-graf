#include "graf.h"

/**
 * Graph Destructor. Cleans the Vertex objects.
 *
 */
Graph::~Graph() {
	for(vertex_map::iterator i = vmap.begin(); i != vmap.end(); ++i)
		delete (*i).second;
}


/**
 * getVertex method
 * Gets a Vertex by specified int key. If vertex not in a graph
 * it adds it.
 *
 * @param int
 * @return Vertex*
 */

Graph::getVertex(int v) {
	vertex_map::iterator i = vmap.find(v);

	if (i == vmap.end() ) {
		Vertex *new_vert = new Vertex(v);
		vmap[ v ] = new_vert;
		return new_vert;
	}

	return (*i).second;
}

/**
 * Adds new edge to the graph.
 *
 * @param int
 * @param int
 * @param double
 * 
 */
void Graph::addEdge( int from, int to, double weight) {
	Vertex *w = getVertex(from);
	Vertex *v = getVertex(to);
	v->adj.push_back( Edge(w, weight) );
}

/**
 * Clears the vertex fields computed by path searching algorithm.
 *
 */
void Graph::clearAlg() {
	for(vertex_map::iterator i = vmap.begin(); i != vmap.end(); ++i)
		(*i).second->reset( );
}

/**
 * Recursively prints the found shortest path to from
 *
 */
void Graph::printPath(const Vertex& to) const {
	if (to.prev != NULL) {
		printPath(*from.prev); 
		cout << " to";
	}
	cout << "(" << to.x << "," << to.y << ")";
}

/** 
 *
 */
void Graph::printPath(int to) const {
	vertex_map::const_iterator i = vmap.find(to);
	if (i == vmap.end() )
		throw GraphException( "Destination vertex not found in the graph" );

	const Vertex& w = *(*i).second;
	if (w.dist == INFINITY )
		cout << to;
	else {
		cout << w.dist << " ";
		printPath(w);
	}
	cout << endl;
}

