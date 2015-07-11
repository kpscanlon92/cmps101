//-----------------------------------------------------------------------------
// Name: Kelly Scanlon
// User: kpscanlo
// Assignment: pa2
//
// Lex.c
// 
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 160


char *strdup (const char *s) {
   char *d = malloc (strlen (s) + 1);
   if (d == NULL) return NULL;
   strcpy (d,s);
   return d;
}


int main (int argc, char * argv[]) {

   int n = 0;
   int lineNumber = 0;
   FILE *in, *out;
   char line[MAX_LEN];

   List L = newList();

   // check command line for correct number of arguments
   if( argc != 3 ){
     printf("Usage: %s <input file> <output file>\n", argv[0]);
     exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   if( in==NULL ){
     printf("Unable to open file %s for reading\n", argv[1]);
     exit(1);
   }
   while( fgets(line, MAX_LEN, in) != NULL ) {
      n++;
   }
   fclose(in);
   
   char* lines[n];

   in = fopen(argv[1], "r");
   while( fgets(line, MAX_LEN, in) != NULL) {
      lines[lineNumber] = strdup(line);
      if(lineNumber > 0) {
         moveTo(L, lineNumber-1);
         int i = lineNumber - 1;
         char* tmp;
         tmp = lines[lineNumber];
         while(i > 0 && strcmp(tmp, lines[getElement(L)])<0) {
            movePrev(L);
            i--;
         }
         if(strcmp(tmp, lines[getElement(L)])<0) 
            insertBefore(L, lineNumber);
         else
            insertAfter(L, lineNumber);
      } else {
         append(L, lineNumber);
      }
      lineNumber++;
   }
   fclose(in);

   out = fopen(argv[2], "w");
   if( out==NULL ){
     printf("Unable to open file %s for writing\n", argv[2]);
     exit(1);
   }

   moveTo(L, 0);
   for(int i = 0; i < n; i++) {
      fprintf(out, lines[getElement(L)]);
      moveNext(L);
   }
   
   for(int i = 0; i < n; i++) {
      free(lines[i]);
   }

   freeList(&L);
   fclose(out);

   return(0);

}

