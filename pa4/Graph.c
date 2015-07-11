// ----------------------------------------------------------------------------
// Name: Kelly Scanlon
// User: kpscanlo
// Assignment: pa4
//
// Graph.c
// This is a Graph ADT used to store Graphs as well as search through
// them using a Breath First Search.
// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

/*** structs ***/

// private GraphObj type
typedef struct GraphObj {
   List* adj;
   char* color;
   int* p;
   int* d;
   int order;
   int size;
   int source;
} GraphObj;

// private Graph type
typedef struct GraphObj* Graph;

/*** Constructors ***/

// newGraph()
// Returns a reference to a new empty Graph.
Graph newGraph(int n) {
   Graph G = malloc(sizeof(GraphObj));

   G->adj = calloc(n+1, sizeof(List));
   G->color = calloc(n+1, sizeof(char));
   G->p = calloc(n+1, sizeof(int));
   G->d = calloc(n+1, sizeof(int));
   G->order = n;
   G->size = 0;
   G->source = NIL;

   int i = 1;
   for(i = 1; i <= n; i++){
      G->adj[i] = newList();
      G->color[i] = 'W';
      G->p[i] = NIL;
      G->d[i] = INF;
   }
   return G;
}

// freeGraph()
// Frees all heap memory associated with Graph pG, and sets *pG to NULL.
void freeGraph(Graph* pG) {
   if(pG != NULL && (*pG) != NULL) {
      int i = 1;
      for(i = 1; i <= getOrder(*pG); i++) {
         freeList(&((*pG)->adj[i]));
      }
      free((*pG)->adj);
      free((*pG)->color);
      free((*pG)->p);
      free((*pG)->d);
      free(*pG);
      *pG = NULL;
   }
}

/*** Access functions ***/

// getOrder()
// Returns the order of the graph.
int getOrder(Graph G) { 
   if(G == NULL) {
      printf("Graph Error: getOrder() called on NULL Graph.\n");
      exit(1);
   }
   return G->order;
}

// getSize()
// Returns the size of the graph.
int getSize(Graph G) {
   if(G == NULL) {
      printf("Graph Error: getSize() called on NULL Graph.\n");
      exit(1);
   }
   return G->size;
}

// getSource()
// Returns the source vertex most recently used in function BFS(), or
// NIL if BFS() has not yet been called.
int getSource(Graph G) {
   if(G == NULL) {
      printf("Graph Error: getSource() called on NULL Graph.\n");
      exit(1);
   }
   return G->source;
}
// getParent()
// Will return the parent of vertex u in the Breadth-First tree 
// created by BFS(), or NIL if BFS() is not yet been called.
// Pre: 1<=u<=getOrder(G)
int getParent(Graph G, int u) {
   if(u < 1 || u > getOrder(G)) {
      printf("Graph Error: getParent() called on unknown vertex.\n");
      exit(1);
   }
   return G->p[u];
}

// getDist()
// Returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not yet been called.
// Pre: 1<=u<=getOrder(G)
int getDist(Graph G, int u) {
   if(u < 1 || u > getOrder(G)) {
      printf("Graph Error: getDist() called on unknown vertex.\n");
      exit(1);
   }
   return G->d[u];
}

// getPath()
// Append to the List L the vertices of a shortest path in G from 
// source to u, or appends to L the value NIL if no such path exists.
// Pre: 1<=u<=getOrder(G)
// Pre: getSource(G) != NIL
void getPath(List L, Graph G, int u) {
   if(u < 1 || u > getOrder(G)) {
      printf("Graph Error: getPath() called on unknown vertex.\n");
      exit(1);
   }
   if(getSource(G) == NIL) {
      printf("Graph Error: getPath() called on undefined source.\n");
      exit(1);
   }
   
   if( u == getSource(G) ) {
      append(L, u);
   } else if ( getParent(G, u) == NIL) {
      append(L, NIL);
   } else {
      prepend(L, u);
      int par = getParent(G, u);
      while( (par != getSource(G)) && (par != NIL) ) {
         prepend(L, par);
         par = getParent(G, par);
      }
      prepend(L, par);
   }
}

/*** Manipulation procedures ***/

// makeNull()
// Deletes all edges of G, restoring it to its original (no edge) 
// state. 
void makeNull(Graph G) {
   int i = 1;
   for(i = 1; i <= getOrder(G); i++) {
      clear(G->adj[i]);
      G->color[i] = 'W';
      G->p[i] = NIL;
      G->d[i] = INF;
   }
   G->size = 0;
   G->source = NIL;
}

// addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency
// List of v and v to the adjacency List of u.
// Pre: 1<=u<=getOrder(G) && 1<=v<=getOrder(G)
void addEdge(Graph G, int u, int v) {
   if(u < 1 || u > getOrder(G)) {
      printf("Graph Error: addEdge() called on unknown vertex.\n");
      exit(1);
   }
   if(v < 1 || v > getOrder(G)) {
      printf("Graph Error: addEdge() called on unknown vertex.\n");
      exit(1);
   }
   
   int curr = -1;

   moveTo(G->adj[u], 0);
   if(getIndex(G->adj[u]) != -1)
      curr = getElement(G->adj[u]);
   while(curr < v && getIndex(G->adj[u]) != -1) {
      moveNext(G->adj[u]);
      if(getIndex(G->adj[u]) != -1)
         curr = getElement(G->adj[u]);
   }
   if(getIndex(G->adj[u]) !=  -1) {
      insertBefore(G->adj[u], v);
   } else {
      append(G->adj[u], v);
   }

   moveTo(G->adj[v], 0);
   if(getIndex(G->adj[v]) != -1)
      curr = getElement(G->adj[v]);
   while(curr < u && getIndex(G->adj[v]) != -1) {
      moveNext(G->adj[v]);
      if(getIndex(G->adj[v]) != -1)
         curr = getElement(G->adj[v]);
   }
   if(getIndex(G->adj[v]) !=  -1) {
      insertBefore(G->adj[v], u);
   } else {
      append(G->adj[v], u);
   }

   G->size++;
}

// addArc()
// Inserts a new directed edge from u to v, i.e. v is added to the 
// adjacency List of u (but not u to the adjacency List of v).
// Pre: 1<=u<=getOrder(G) && 1<=v<=getOrder(G)
void addArc(Graph G, int u, int v) {
   if(u < 1 || u > getOrder(G)) {
      printf("Graph Error: addEdge() called on unknown vertex.\n");
      exit(1);
   }
   if(v < 1 || v > getOrder(G)) {
      printf("Graph Error: addEdge() called on unknown vertex.\n");
      exit(1);
   }
   
   int curr = -1;

   moveTo(G->adj[u], 0);
   if(getIndex(G->adj[u]) != -1)
      curr = getElement(G->adj[u]);
   while(curr < v && getIndex(G->adj[u]) != -1) {
      moveNext(G->adj[u]);
      if(getIndex(G->adj[u]) != -1)
         curr = getElement(G->adj[u]);
   }
   if(getIndex(G->adj[u]) !=  -1) {
      insertBefore(G->adj[u], v);
   } else {
      append(G->adj[u], v);
   }

   G->size++;
}

// BFS()
// Runs the BFS algorithm on the Graph G with source s, setting the
// color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s) {
   if( s < 1 || s > getOrder(G) ) {
      printf("Graph Error: BFS() called on out of bounds source\n");
      exit(1);
   }
   
   G->source = s;

   int i;
   for(i = 1; i <= getOrder(G); i++) {
      G->color[i] = 'W';
      G->d[i] = INF;
      G->p[i] = NIL;
   }
   
   int x, y;
   
   G->color[s] = 'G';
   G->d[s] = 0;
   G->p[s] = NIL;

   List Q = newList();
   append(Q, s);
   while(length(Q) > 0) {
      x = front(Q);
      deleteFront(Q);
      moveTo(G->adj[x], 0);
      while(getIndex(G->adj[x]) != -1) {
         y = getElement(G->adj[x]);
         if( G->color[y] == 'W') {
            G->color[y] = 'G';
            G->d[y] = getDist(G, x) + 1;
            G->p[y] = x;
            append(Q, y);
         }
         moveNext(G->adj[x]);
      }
      G->color[x] = 'B';
   }
   freeList(&Q);
}

/*** Other operations ***/

// printGraph()
// Prints the adjacency list representation of G to the file pointed 
// to by out.
void printGraph(FILE* out,Graph G) {
   int i;
   for(i = 1; i <= getOrder(G); i++) {
      fprintf(out, "%d: ", i);
      printList(out, G->adj[i]);
   }
}

