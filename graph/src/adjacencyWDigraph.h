// adjacency matrix representation of a weighted directed graph

#ifndef adjacencyWDigraph_
#define adjacencyWDigraph_

#include <iostream>
#include <sstream>
#include <iterator>
#include "graph.h"
#include "weightedEdge.h"
#include "vertexIterator.h"
#include "make2dArrayNoCatch.h"
#include "delete2dArray.h"
#include "myExceptions.h"
#include "arrayQueue.h"
#include "arrayStack.h"
#include "linkedWDigraph.h"

using namespace std;

template<class T>
class linkedWDigraph;

template<class T>
class adjacencyWDigraph: public graph<T>
{
protected:
	int n;           // number of vertices
	int e;           // number of edges
	T **a;           // adjacency array
	T noEdge;        // denotes absent edge

public:
	adjacencyWDigraph(int numberOfVertices = 0, T theNoEdge = 0)
	{	// Constructor.
		// validate number of vertices

		if (numberOfVertices < 0)
			throw illegalParameterValue("number of vertices must be >= 0");
		n = numberOfVertices;
		e = 0;
		noEdge = theNoEdge;
		make2dArray(a, n + 1, n + 1);
		for (int i = 1; i <= n; i++)
			// initialize adjacency matrix
			fill(a[i], a[i] + n + 1, noEdge);
	}

	~adjacencyWDigraph()
	{
		delete2dArray(a, n + 1);
	}

	int numberOfVertices() const
	{
		return n;
	}

	int numberOfEdges() const
	{
		return e;
	}

	bool directed() const
	{
		return true;
	}

	bool weighted() const
	{
		return true;
	}

	bool existsEdge(int i, int j) const
	{   // Return true iff (i,j) is an edge of the graph.
		if (i < 1 || j < 1 || i > n || j > n || a[i][j] == noEdge)
			return false;
		else
			return true;
	}

	void insertEdge(edge<T> *theEdge)
	{	// Insert edge theEdge into the digraph; if the edge is already
		// there, update its weight to theEdge.weight().
		int v1 = theEdge->vertex1();
		int v2 = theEdge->vertex2();
		if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
		{
			ostringstream s;
			s << "(" << v1 << "," << v2 << ") is not a permissible edge";
			throw illegalParameterValue(s.str());
		}

		if (a[v1][v2] == noEdge)  // new edge
			e++;
		a[v1][v2] = theEdge->weight();
	}

	void eraseEdge(int i, int j)
	{  // Delete the edge (i,j).
		if (i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge)
		{
			a[i][j] = noEdge;
			e--;
		}
	}

	void checkVertex(int theVertex) const
	{  // Verify that i is a valid vertex.
		if (theVertex < 1 || theVertex > n)
		{
			ostringstream s;
			s << "no vertex " << theVertex;
			throw illegalParameterValue(s.str());
		}
	}

	int degree(int theVertex) const
	{
		throw undefinedMethod("degree() undefined");
	}

	int outDegree(int theVertex) const
	{  // Return out-degree of vertex theVertex.
		checkVertex(theVertex);

		// count out edges from vertex theVertex
		int sum = 0;
		for (int j = 1; j <= n; j++)
			if (a[theVertex][j] != noEdge)
				sum++;

		return sum;
	}

	int inDegree(int theVertex) const
	{  // Return in-degree of vertex theVertex.
		checkVertex(theVertex);

		// count in edges at vertex theVertex
		int sum = 0;
		for (int j = 1; j <= n; j++)
			if (a[j][theVertex] != noEdge)
				sum++;

		return sum;
	}

	class myIterator: public vertexIterator<T>
	{
	public:
		myIterator(T* theRow, T theNoEdge, int numberOfVertices)
		{
			row = theRow;
			noEdge = theNoEdge;
			n = numberOfVertices;
			currentVertex = 1;
		}

		~myIterator()
		{
		}

		int next()
		{  // Return next vertex if any. Return 0 if no next vertex.
		   // find next adjacent vertex
			for (int j = currentVertex; j <= n; j++)
				if (row[j] != noEdge)
				{
					currentVertex = j + 1;
					return j;
				}
			// no next adjacent vertex
			currentVertex = n + 1;
			return 0;
		}

		int next(T& theWeight)
		{	// Return next vertex if any. Return 0 if no next vertex.
			// Set theWeight = edge weight.
			// find next adjacent vertex
			for (int j = currentVertex; j <= n; j++)
				if (row[j] != noEdge)
				{
					currentVertex = j + 1;
					theWeight = row[j];
					return j;
				}
			// no next adjacent vertex
			currentVertex = n + 1;
			return 0;
		}

	protected:
		T* row;           // row of adjacency matrix
		T noEdge;         // theRow[i] == noEdge iff no edge to i
		int n;            // number of vertices
		int currentVertex;
	};

	myIterator* iterator(int theVertex)
	{	// Return iterator for vertex theVertex.
		checkVertex(theVertex);
		return new myIterator(a[theVertex], noEdge, n);
	}

	void output(ostream& out) const
	{	// Output the adjacency matrix.
		for (int i = 1; i <= n; i++)
		{
			copy(a[i] + 1, a[i] + n + 1, ostream_iterator<T>(out, "  "));
			out << endl;
		}
	}

	void bfs(int v, int reach[], int label) const
	{	// Breadth-first search. reach[i] is set to label for
		// all vertices reachable from vertex v.
		arrayQueue<int> q(n);
		reach[v] = label;
		q.push(v);
		while (!q.empty())
		{
			// remove a labeled vertex from the queue
			int w = q.front();
			q.pop();

			// mark all unreached vertices adjacent from w
			for (int u = 1; u <= n; u++)
				// visit an adjacent vertex of w
				if (a[w][u] != noEdge && reach[u] == 0)
				{       // u is an unreached vertex
					q.push(u);
					reach[u] = label; // mark reached
				}
		}
	}

	void dfs(int v, int reach[], int label) const
	{
		arrayStack<int> s(n);
		reach[v] = label;
		s.push(v);
		while (!s.empty())
		{
			int w = s.top();
			s.pop();

			// mark all unreached vertices adjacent from w
			for (int u = n; u >= 1; u--)
				// visit an adjacent vertex of w
				if (a[w][u] != noEdge && !reach[u])
				{	// u is an unreached vertex
					s.push(u);
					reach[u] = label; // mark reached
				}
		}
	}

	linkedWDigraph<T>& convertToList()
	{	// return linkedWDigraph Type pointer
		linkedWDigraph<T> *l = new linkedWDigraph<T>(n);

		// n*n loop to get all edges
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (a[i][j])
					l->insertEdge(new weightedEdge<int>(i, j, a[i][j]));

		return *l;
	}

};

// overload <<
template<class T>
ostream& operator<<(ostream& out, const adjacencyWDigraph<T>& x)
{
	x.output(out);
	return out;
}
#endif
