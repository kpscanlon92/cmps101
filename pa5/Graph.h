// ----------------------------------------------------------------------------
// Name: Kelly Scanlon
// User: kpscanlo
// Assignment: pa5
//
// Graph.h
// Header file for Graph ADT
// ----------------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#define UNDEF -1
#define NIL 0

#include "List.h"

/*** Exported type ***/
typedef struct GraphObj* Graph;

/*** Constructors ***/

// newGraph()
// Returns a reference to a new empty Graph.
Graph newGraph(int n);

// freeGraph()
// Frees all heap memory associated with Graph pG, and sets *pG to NULL.
void freeGraph(Graph* pG);

/*** Access functions ***/

// getOrder()
// Returns the order of the graph.
int getOrder(Graph G);

// getSize()
// Returns the size of the graph.
int getSize(Graph G);

// getParent()
// Will return the parent of vertex u in the Depth-First tree 
// created by DFS(), or NIL if DFS() is not yet been called.
// Pre: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u);

// getDiscover()
// Returns the discover time from the given vertex u
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u);

// getFinish()
// Returns the finish time from the given vertex u
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/

// addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency
// List of v and v to the adjacency List of u.
// Pre: 1<=u<=getOrder(G) && 1<=v<=getOrder(G)
void addEdge(Graph G, int u, int v);

// addArc()
// Inserts a new directed edge from u to v, i.e. v is added to the 
// adjacency List of u (but not u to the adjacency List of v).
// Pre: 1<=u<=getOrder(G) && 1<=v<=getOrder(G)
void addArc(Graph G, int u, int v);

// DFS()
// Runs the DFS algorithm on the Graph G.
void DFS(Graph G, List S);

/*** Other operations ***/

// transpose()
// Returns a reference to a new graph object representing the transpose
// of G.
Graph transpose(Graph G);

// copyGraph()
// Returns a reference to a new graph which is a copy of G.
Graph copyGraph(Graph G);

// printGraph()
// Prints the adjacency list representation of G to the file pointed 
// to by out.
void printGraph(FILE* out,Graph G);

#endif

