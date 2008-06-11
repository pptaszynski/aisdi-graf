#include <limits.h>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <functional>
#include <list>

/**
 *	A Class representing a vertex of a graph
 *
 */

class Vertex 
{
public:
	unsigned int x;		// Vertex x coordinate
	unsigned int y;		// Vertex y cooridnate	
	vector<Edge> adj;	// Vector of adjacent vert.
	double	dist;		// to compute dist in finding shortest path alg.
	Vertex	*prev;		// Previous Vertex on the path - to help print it
	int		scratch;	// Var. for alg.
	
	/**
	 *	Public constructor.
	 *
	 *	@param	int
	 *	@para	int
	 *
	 */
	Vertex ( int xco, int yco ) : x(xco), y(yco) {
		reset();
	}
private:
	/**
	 *	Method to reset fields for the algorithm
	 *
	 */
	void reset() {
		dist = INFINITY;
		prev = NULL;
		scratch = 0;
	}
}

/**
 *	Class representing an edge in graph
 *
 */

class Edge
{
public:
	// First vertex is the one that has this edge in adj Vector
	Vertex	*to;	// Destination vertex of an edge.
	double	cost;

	/**
	 *	Public constructor
	 *
	 *	@param Vertex*
	 *	@param double
	 */
	Edge( Vertex *d = 0, double c = 0.0 ) : to(d), cost(c) { }

}

/**
 * Graph class
 *
 * @constructor	no parameteres
 * @method void addEdge(int v, int w, double costvw)
 * @method void printPath(int w)
 * @method void unweighted(int s)
 * @method void weighted(int s)
 *
 */
class Graph
{
public:
	Graph() {}
	~Graph();

	void addEdge (int from, int to, double cost);
	void printPath (int to) const;
	void unweighted (int from);
	void weighted (int to);

private:
	Vertex* getVertex (int v);
	void printPath (const Vertex &to) const;
	void clearAlg();

	typedef map<int, Vertex*, less<int> > vertex_map;
	
	// Disable operator=
	inline const Graph& operator= (const Graph& other) {
		return *this;
	}

	vertex_map vmap;

}

