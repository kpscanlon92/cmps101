//-----------------------------------------------------------------------------
// Name: Kelly Scanlon
// User: kpscanlo
// Assignment: pa4
//
// GraphTest.c
// This is a way to test the Graph ADT in isolation. 
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]){
   int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   List  L = newList();
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   printf("The Order of this undirected Graph is: %d\n", getOrder(G));
   printf("The Size of this undirected Graph is: %d\n", getSize(G));
   printf("Undirected Graph:\n");
   printGraph(stdout, G);
   

   BFS(G, 1);
   getPath(L, G, 2);

   fprintf(stdout, "\nThe distance from %d to %d is ", getSource(G), 2);
   if(getDist(G, 2) == INF) {
      fprintf(stdout, "infinity\n");
      fprintf(stdout, "No %d-%d path exists\n", getSource(G), 2);
      fprintf(stdout, "The parent of %d is: %d\n", 2, getParent(G, 2));
   }  else {
      fprintf(stdout, "%d\n", getDist(G, 2));
      fprintf(stdout, "A shortest %d-%d path is: ", getSource(G), 2);
      printList(stdout, L);
      fprintf(stdout, "The parent of %d is: %d\n", 2, getParent(G, 2));
   }

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveTo(E,0);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = getElement(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Make Directed Graph
   makeNull(G);
   printf("The Order of this Graph after makeNull() is: %d\n", getOrder(G));
   printf("The Size of this Graph after makeNull() is: %d\n\n", getSize(G));
   
   freeGraph(&G);
   G = newGraph(5);
  
   // Directed graph from lecture notes 7/21/14 
   addArc(G, 2, 1);
   addArc(G, 1, 4);
   addArc(G, 4, 2);
   addArc(G, 4, 5);
   addArc(G, 3, 2);
   addArc(G, 3, 5);

   printf("The Order of this directed Graph is: %d\n", getOrder(G));
   printf("The Size of this directed Graph is: %d\n", getSize(G));
   printf("Directed Graph:\n");
   printGraph(stdout, G);


   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeList(&L);
   freeGraph(&G);

   return(0);
}

