// ----------------------------------------------------------------------------
// Name: Kelly Scanlon
// User: kpscanlo
// Assignment: pa5
//
// Graph.c
// This is a Graph ADT used to store Graphs as well as search through
// them using a Depth First Search.
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
   int* f;
   int order;
   int time;
   int size;
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
   G->f = calloc(n+1, sizeof(int));
   G->order = n;
   G->time = UNDEF;
   G->size = 0;

   int i = 1;
   for(i = 1; i <= n; i++){
      G->adj[i] = newList();
      G->color[i] = 'W';
      G->p[i] = NIL;
      G->d[i] = UNDEF;
      G->f[i] = UNDEF;
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
      free((*pG)->f);
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

// getParent()
// Will return the parent of vertex u in the Depth-First tree 
// created by DFS(), or NIL if DFS() is not yet been called.
// Pre: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u) {
   if(u < 1 || u > getOrder(G)) {
      printf("Graph Error: getParent() called on unknown vertex.\n");
      exit(1);
   }
   return G->p[u];
}

// getDiscover()
// Returns the dicover time from the giver vertex u.
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u) {
   if(u < 1 || u > getOrder(G)) {
      printf("Graph Error: getDiscover() called on unknown vertex.\n");
      exit(1);
   }
   return G->d[u];
}

// getFinish()
// Returns the finish time from the giver vertex u.
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u) {
   if(u < 1 || u > getOrder(G)) {
      printf("Graph Error: getFinish() called on unknown vertex.\n");
      exit(1);
   }
   return G->f[u];
}


/*** Manipulation procedures ***/

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

// visit()
// Helper function for DFS()
void visit(Graph G, List S, int u) {
   int v;
   G->color[u] = 'G';
   G->time++;
   G->d[u] = G->time;
   moveTo(G->adj[u], 0);
   while(getIndex(G->adj[u]) != -1) {
      v = getElement(G->adj[u]);
      if(G->color[v] == 'W') {
         G->p[v] = u;
         visit(G, S, v);
      }
      moveNext(G->adj[u]);
   }
   G->color[u] = 'B';
   G->time++;
   G->f[u] = G->time;
   prepend(S, u);
}


// DFS()
// Runs the DFS algorithm on the Graph G.
void DFS(Graph G, List S) {
   if(length(S) != getOrder(G)) {
      printf("Graph Error: DFS() called on graph whose order != the stack size\n");
      exit(1);
   }
   
   int x;
   List L = newList();
   for(int i = 0; i <= getOrder(G); i++) {
      G->color[i] = 'W';
      G->d[i] = UNDEF;
      G->f[i] = UNDEF;
      G->p[i] = NIL;
   }
   
   G->time = 0;
   
   if( length(S) > 0) { 
      moveTo(S, 0);
   }
   while(getIndex(S) != -1) {
      x = getElement(S);
      if(G->color[x] == 'W') {
         visit(G, L, x);
      }
      moveNext(S);
   }

   clear(S);
   if( length(L) > 0 ) {
      moveTo(L, 0);
   }
   while(getIndex(L) != -1) {
      append(S, getElement(L));
      moveNext(L);
   }
   freeList(&L);
}

/*** Other operations ***/

// transpose()
// Returns a reference to a new graph object representing the transpose
// of G.
Graph transpose(Graph G) {
   Graph T = newGraph(getOrder(G));
   int i, x;
   for( i = 1; i <= getOrder(G); i++) {
      if( length(G->adj[i]) > 0 ) {
         moveTo(G->adj[i], 0);
      }
      while(getIndex(G->adj[i]) != -1) {
         x = getElement(G->adj[i]);
         addArc(T, x, i);
         moveNext(G->adj[i]);
      }
   }
   return T;
}

// copyGraph()
// Returns a reference to a new graph which is a copy of G.
Graph copyGraph(Graph G) {
   Graph N = newGraph(getOrder(G));
   int i;
   for(i = 1; i <= getOrder(N); i++) {
      if(length(G->adj[i]) > 0) {
         moveTo(G->adj[i], 0);
      }
      while( getIndex(G->adj[i]) != -1 ) {
         append(N->adj[i], getElement(G->adj[i]));
         moveNext(G->adj[i]);
      }
      N->color[i] = G->color[i];
      N->d[i] = getDiscover(G, i);
      N->f[i] = getFinish(G, i);
      N->p[i] = getParent(G, i);
   }
   N->size = getSize(G);
   N->time = G->time;
   return N;
}

// printGraph()
// Prints the adjacency list representation of G to the file pointed 
// to by out.
void printGraph(FILE* out,Graph G) {
   int i;
   for(i = 1; i <= getOrder(G); i++) {
      fprintf(out, "%d: ", i);
      printList(out, G->adj[i]);
      fprintf(out, "\n");
   }
}

