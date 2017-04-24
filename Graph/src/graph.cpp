//============================================================================
// Name        : graph.cpp
// Author      : Blaise Wang
// Version     :
// Copyright   : 2016
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "graph.h"
#include "adjacencyWDigraph.h"
#include "linkedWDigraph.h"
#include "weightedEdge.h"
#include <numeric>

using namespace std;

int main() {
    int n = 2;
    graph<int> *h[n];

    h[0] = new linkedWDigraph<int>(7);
    h[1] = new adjacencyWDigraph<int>(7);

    adjacencyWDigraph<int> g1(7);
    linkedWDigraph<int> g2(7);

    for (int j = 0; j < n; j++) {
        h[j]->insertEdge(new weightedEdge<int>(1, 2, 9));
        h[j]->insertEdge(new weightedEdge<int>(1, 3, 9));
        h[j]->insertEdge(new weightedEdge<int>(2, 5, 9));
    }
    g1.insertEdge(new weightedEdge<int>(1, 2, 9));
    g1.insertEdge(new weightedEdge<int>(1, 3, 9));
    g1.insertEdge(new weightedEdge<int>(2, 5, 9));

    g2.insertEdge(new weightedEdge<int>(1, 2, 9));
    g2.insertEdge(new weightedEdge<int>(1, 3, 9));
    g2.insertEdge(new weightedEdge<int>(2, 5, 9));

    for (int i = 0; i < n; i++) {
        cout << "Graph " << i + 1 << " is" << endl;
        cout << "Number of Vertices = " << h[i]->numberOfVertices() << endl;
        cout << "Number of Edges = " << h[i]->numberOfEdges() << endl;
        h[i]->output(cout);
        cout << endl << endl;
    }

    int hReach[8], g1Reach[8], g2Reach[8];

    cout << "Doing dfs" << endl;
    for (int i = 0; i < 1; i++) {
        for (int j = 1; j <= 7; j++) {
            hReach[j] = 0;
            g1Reach[j] = 0;
            g2Reach[j] = 0;
        }

        h[0]->dfs(1, hReach, 1);
        h[0]->dfs(3, hReach, 2);
        g1.dfs(1, g1Reach, 1);
        g1.dfs(3, g1Reach, 2);
        g2.dfs(1, g2Reach, 1);
        g2.dfs(3, g2Reach, 2);

        for (int j = 1; j <= 7; j++) {
            cout << hReach[j] << " ";
        }
        cout << endl;
        for (int j = 1; j <= 7; j++) {
            cout << g1Reach[j] << " ";
        }
        cout << endl;
        for (int j = 1; j <= 7; j++) {
            cout << g2Reach[j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    adjacencyWDigraph<int> a1(7);
    linkedWDigraph<int> a2(7);

    a2 = g1.convertToList();
    a2.output(cout);

    a1 = g2.convertToMatrix();
    a1.output(cout);

    return 0;
}
