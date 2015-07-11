//-----------------------------------------------------------------------------
// Name: Kelly Scanlon
// User: kpscanlo
// Assignment: pa5
//
// FindComponent.c
// This is the main program that does the following:
// +Read the input file.
// +Assemble a graph object G using newGraph() and addArc()
// +Print the adjacency list representation of G to the output file.
// +Run DFS on G and G transpose, processing the vertices in the 
// second call by decreasing finish times from the first call.
// +Determine the strong components of G.
// +Print the strong components of G to the output file in 
// topologically sorted order.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){
   int s, d, n = 0;
   List  L = newList(); 
   Graph G = NULL;
   Graph G_Trans = NULL;
   
   FILE *in, *out;
   char line[MAX_LEN];
   char * token;


   // Check command line for correct number of arguments
   if( argc != 3 ) {
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // Open file for reading
   in = fopen(argv[1], "r");
   if( in == NULL ) {
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   // Get the number of vertices in Graph
   fgets(line, MAX_LEN, in);
   token = strtok(line, " \n");
   n = atoi(&token[0]);

   // Build graph G 
   G = newGraph(n);
   while(fgets(line, MAX_LEN, in) != NULL) {
      token = strtok(line, " \n");
      s = atoi(token);
      token = strtok(NULL, " \n");
      d = atoi(token);
      if(s != 0)
         addArc(G, s, d);
      else
         break;
   }

   
   // Open file for writing
   out = fopen(argv[2],"w");
   if( out == NULL ) {
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   // Print adjacency list representation of G
   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out , G);
   fprintf(out, "\n");


   // Initialize the list
   for(int i = 1; i <= getOrder(G); i++) {
      append(L, i);
   }

   // Run DFS on G and G_Trans 
   DFS(G, L);
   G_Trans = transpose(G);
   DFS(G_Trans, L);

   // Find the number of Strongly Connected Components
   int scc = 0;
   for(int i = 1; i <= getOrder(G); i++) {
      if(getParent(G_Trans, i) == NIL) scc++;
   }
   fprintf(out, "G contains %d strongly connected components:\n", scc);

   // Print the strongly connected components
   int i = 1, x;
   List cc = newList();
   if( length(L) > 0 ) {
      moveTo(L, length(L)-1);
   }
   while( getIndex(L) != -1 && i <= scc) {
      x = getElement(L);
      fprintf(out, "Component %d: ", i);
      while( getParent(G_Trans, x) != NIL && getIndex(L) != -1) {
         prepend(cc, x);
         movePrev(L);
         if(getIndex(L) != -1)
            x = getElement(L);
      }
      if(getIndex(L) != -1) {
         prepend(cc, x);
         movePrev(L);
      }   
      printList(out, cc);
      fprintf(out, "\n");
      clear(cc);
      i++;
   }

   // Close Files
   fclose(in);
   fclose(out);

   // Free objects 
   freeList(&cc);
   freeList(&L);
   freeGraph(&G);
   freeGraph(&G_Trans);

   return(0);
}

