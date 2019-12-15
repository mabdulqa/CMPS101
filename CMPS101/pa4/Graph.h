//-----------------------------------------------------------------
//  CMPS101 PA4
//  Mohammad Abdulqder (mabdulqa)
//  
//  Graph.h
//  Header file for Graph ADT with its public functions.
//-----------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include "List.h"

#define NIL -10
#define UNDEF -20

// structs --------------------------------------------------------------------

// Graph type
typedef struct GraphObj* Graph;


// Constructors-Destructors ----------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object.
Graph newGraph(int n);


// freeGraph()
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph* pG);

// Acess Functions -------------------------------------------------------------

// getOrder()
// returns the number of vertices in Graph G.
int getOrder(Graph G);

// getSize()
// returns the number of edges in Graph G.
int getSize(Graph G);

// getDiscover()
// returns the discovery time of said vertex.
// Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u);

// getParent()
// returns the parent of the given vertex.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getFinish()
// returns the finish time of said vertex.
// Pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u);

// Manipulaton procedures ------------------------------------------------------

// makeNull()
// deletes all edges in G, making it a null graph.
void makeNull(Graph G);

// addEdge()
// adds a new edge to the graph G in adj[u] and adj[v].
// pre: 1 <= u <= getOrder(G) and 1 <= u <= getOrder(G).
void addEdge(Graph G, int u, int v);

// addArc()
// adds a new edge to graph G into adj[u] but not adj[v]
// pre: 1 <= u <= getOrder(G) and 1 <= u <= getOrder(G).
void addArc(Graph G, int u, int v);

// BFS()
// the classic BFS algorithm.
void DFS(Graph G, List S);

// Other operations ------------------------------------------------------------

// transpose()
// returns the transpose of Graph G.
Graph transpose(Graph G);

// copyGraph()
// returns an identical copy of the graph G.
Graph copyGraph(Graph G);

// printGraph()
// prints adjacency list of Graph G to out.
void printGraph(FILE* out, Graph G);

// Helper functions ------------------------------------------------------------

// Visit()
// helper function for DFS.
void Visit(Graph G, int x, List S);

// end of ADT operations -------------------------------------------------------

#endif

