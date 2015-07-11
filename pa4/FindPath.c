//-----------------------------------------------------------------------------
// Name: Kelly Scanlon
// User: kpscanlo
// Assignment: pa4
//
// FindPath.c
// This is the main class for the program which implements both the 
// Graph ADT and the List ADT. It takes in two arguments: input file
// and the output file. It reads in the first section of the input file
// to build a graph. The next section of the input file is pairs of 
// integers in the range 1 to n which specify a pair of vertices in 
// the graph. Using the results from the Breath First Search (BFS), it
// outputs th distance of the vertices and the shortest path from the 
// source to destination.
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
         addEdge(G, s, d);
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
   printGraph(out , G);

   // Process vertice pairs
   while(fgets(line, MAX_LEN, in) != NULL) {
      token = strtok(line, " \n");
      s = atoi(token);
      token = strtok(NULL, " \n");
      d = atoi(token);
      if(s != 0) {
         BFS(G, s);
         clear(L);
         getPath(L, G, d);

         fprintf(out, "\nThe distance from %d to %d is ", s, d);
         if(getDist(G, d) == INF) {
            fprintf(out, "infinity\n");
            fprintf(out, "No %d-%d path exists\n", s, d);
         }  else {
            fprintf(out, "%d\n", getDist(G, d));
            fprintf(out, "A shortest %d-%d path is: ", s, d);
            printList(out, L);
         }
      } else {
         break;
      }
   }

   // Close Files
   fclose(in);
   fclose(out);

   // Free objects 
   freeList(&L);
   freeGraph(&G);

   return(0);
}
