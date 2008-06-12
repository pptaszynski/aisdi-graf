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
 * Method adds a vertex to the graph
 *
 * @param int
 * @param int
 * @param int
 *
 */
void Graph::addVertex(unsigned int k, double x, double y) {
	vertex_map::iterator i = vmap.find(k);

	if (i == vmap.end() ) {
		Vertex *new_vertex = new Vertex(x, k);
		vmap[ k ] = new_vertex;
		return new_vertex;
	}

	return (*i).second;
}

/**
 * getVertex method
 * Gets a Vertex by specified int key. If vertex not in a graph
 * it adds it.
 *
 * @param int
 * @return Vertex*
 */
Vertex* Graph::getVertex(int v) {
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

/**
 * Method to search shortest unweighted path from from to all other vertices
 *
 * @param int
 */
void Graph::unweighted(int from) {
	vertex_map::iterator i = vmap.find(from);
	if (i == vmap.end() ) 
		throw GraphException(from + " isn't vertex in this Graph");

	clearAlg();
	Vertex *first = (*i).second;
	list<Vertex*> q;
	q.push_back(first);
	first->dist = 0;
	while( !q.empty() ) {
		Vertex *v = q.front();
		q.pop_front();

		int vadjs = v->adj.size();
		for (int i = 0; i < vadjs; ++i) {
			Edge e = v->adj[ i ];
			Vertex *w = e.to;
			if (w->dist == INFINITY) {
				w->dist = v->dist + 1;
				w->prev = v;
				q.push_back(w);
			}
		}
	}
}

/**
 * This method finds the weighted shortest-path using Dijkstra's algorithm
 *
 * @param int
 *
 */
void Graph::weighted(int from) {
	priority_queue<Path, vector<Path>, greater<Path> > pq;
	Path vrec;

	vector_map::iterator i = vmap.find(from);
	if (i == vmap.end() )
		throw GraphException(from + " isn't a vertex in this graph");

	clearAlg();
	Vertex *first = (*i).second;
	pq.push(Path(first, 0) ); 
	start->dist = 0;

	int totalVs = vmap.size();
	for (int visitedVs = 0; visitedVs < totalVs; ++vistedVs) {
		do {
			if (pq.empty() ) return;
			vrec = pq.top();
			pq.pop();
		} while (vrec.to->scraatch != 0);

		Vertex *v vrec.dest;
		v->scratch = 1;

		int vadjs = v->adj.size();
		for(int i = 0; i < vadjs; ++i) {
			Edge e = v->adj[ i ];
			Vertex *w = e.dest;
			double costvw = e.cost;
			if (costvw < 0) 
				throw GraphException("Edges can't have negative cost");

			if (w->dist > v->dist+costvw) {
				w->dist = v->dist + costvw;
				w->prev = v;
				pq.push(Path(w, w->dist) );
			}
		}
	}
}


