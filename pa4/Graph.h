// ----------------------------------------------------------------------------
// Name: Kelly Scanlon
// User: kpscanlo
// Assignment: pa4
//
// Graph.h
// Header file for Graph ADT
// ----------------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#define INF -2
#define NIL -1

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

// getSource()
// Returns the source vertex most recently used in function BFS(), or
// NIL if BFS() has not yet been called.
int getSource(Graph G);

// getParent()
// Will return the parent of vertex u in the Breadth-First tree 
// created by BFS(), or NIL if BFS() is not yet been called.
// Pre: 1<=u<=getOrder(G)
int getParent(Graph G, int u);

// getDist()
// Returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not yet been called.
// Pre: 1<=u<=getOrder(G)
int getDist(Graph G, int u);

// getPath()
// Append to the List L the vertices of a shortest path in G from 
// source to u, or appends to L the value NIL if no such path exists.
// Pre: 1<=u<=getOrder(G)
// Pre: getSource(G) != NIL
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/

// makeNull()
// Deletes all edges of G, restoring it to its original (no edge) 
// state. 
void makeNull(Graph G);

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

// BFS()
// Runs the BFS algorithm on the Graph G with source s, setting the
// color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s);

/*** Other operations ***/

// printGraph()
// Prints the adjacency list representation of G to the file pointed 
// to by out.
void printGraph(FILE* out,Graph G);

#endif

