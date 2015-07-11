//-----------------------------------------------------------------------------
// Name: Kelly Scanlon
// User: kpscanlo
// Assignment: pa2
//
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// structs ----- --------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj {
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj {
   Node front;
   Node back;
   Node cursor;
   int cursor_inx;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes prev, next, and data 
// fields. Private.
Node newNode(int data) {
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return N;
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL
void freeNode(Node* pN) {
   if (pN != NULL && *pN != NULL) {
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns a reference to new empty List
List newList(void) {
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->cursor_inx = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL) {
   if (pL != NULL && *pL != NULL) {
      while( length(*pL) > 0 ) {
         deleteBack(*pL);   
      }
      free(*pL);
      *pL = NULL;
   }
}

// Access functions -----------------------------------------------------------

// length()
// Returns number of elements in this list.
int length(List L) {
   int result = 0;
   for (Node curr = L->front; curr != NULL; curr = curr->next) {
      result++;
   }
   return result;
}

// getIndex()
// Returns the index of the cursor element in this list, or
// returns -1 if the cursor element is undefined.
int getIndex(List L) {
   return L->cursor_inx;
}

// front()
// Returns front element in this list. Pre: length()>0
int front(List L) {
   if ( L == NULL ) {
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if ( length(L) <= 0 ) {
      printf("List Error: calling front() on empty List\n");
      exit(1);
   }
   return (L->front->data);
}

// back()
// Returns back element in this List. Pre: length()>0
int back(List L) {
   if ( L == NULL ) {
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if ( length(L) <= 0 ) {
      printf("List Error: calling back() on empty List\n");
      exit(1);
   }
   return (L->back->data);
}

// getElement()
// Returns cursor element in this list. Pre: length()>0, getIndex()>=0
int getElement(List L) {
   if ( L == NULL ) {
      printf("List Error: calling getElement() on NULL List reference\n");
      exit(1);
   }
   if ( length(L) <= 0 ) {
      printf("List Error: calling getElement() on empty List\n");
      exit(1);
   } 
   if ( getIndex(L) < 0 ) {
      printf("List Error: calling getElement() on undefined cursor\n");
   }
   return (L->cursor->data);
}

// equals()
// Returns true if this List and L are the same integer
// sequence. The cursor is ignored in both lists.
int equals(List A, List B) {
   int flag = 1;
   Node N = NULL;
   Node M = NULL;

   if ( A==NULL || B==NULL ) {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   N = A->front;
   M = B->front;
   if ( length(A) != length(B) ) {
      return 0;
   }
   while ( flag && N!=NULL ) {
      flag = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return flag;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Re-sets this List to the empty state.
void clear(List L) {
   if (L != NULL) {
      while( length(L) > 0 ) {
         deleteBack(L);   
      }
   }
   L->front = L->back = L->cursor = NULL;
   L->cursor_inx = -1;
}

// moveTo()
// If 0<=i<=length()-1, moves the cursor to the element
// at index i, otherwise the cursor becomes undefined.
void moveTo(List L, int i) {
   if ( L == NULL ) {
      printf("List Error: calling moveTo() on NULL List reference\n");
      exit(1);
   }
   if ( (0 <= i) && (i <= (length(L)-1)) ) {
      Node curr = L->front;
      for(int inx = 0; inx < i; inx++) {
         curr = curr->next;
      }
      L->cursor = curr;
      L->cursor_inx = i;
   } else {
      L->cursor = NULL;
      L->cursor_inx = -1;
   }
}

// movePrev()
// If 0<getIndex()<=length()-1, moves the cursor one step toward the
// front of the list. If getIndex()==0, cursor becomes undefined.
// If getIndex()== -1, cursor remains undefined. This operation is
// equivalent to moveTo(getIndex()-1).
void movePrev(List L) {
   if ( L == NULL ) {
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   if( (0 < getIndex(L)) && (getIndex(L) <= (length(L)-1)) ) {
      L->cursor = L->cursor->prev;
      L->cursor_inx = L->cursor_inx - 1;
   } else if (getIndex(L) == 0) {
      L->cursor = NULL;
      L->cursor_inx = -1;
   } else if (getIndex(L) == -1) {
      L->cursor = NULL;
      L->cursor_inx = -1;
   }
}

// moveNext()
// If 0<=getIndex()<length()-1, moves the cursor one step toward the
// back of the list. If getIndex()==length()-1, cursor becomes
// undefined. If index==-1, cursor remains undefined. This
// operation is equivalent to moveTo(getIndex()+1).
void moveNext(List L) {
   if ( L == NULL ) {
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   if( (0 <= getIndex(L)) && (getIndex(L) < (length(L)-1)) ) {
      L->cursor = L->cursor->next;
      L->cursor_inx = L->cursor_inx + 1;
   } else if (getIndex(L) == (length(L)-1)) {
      L->cursor = NULL;
      L->cursor_inx = -1;
   } else if (getIndex(L) == -1) {
      L->cursor = NULL;
      L->cursor_inx = -1;
   }
}

// prepend()
// Inserts new element before front element in this List.
void prepend(List L, int data) {
   if ( L == NULL ) {
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
   
   Node N = newNode(data);
   if( length(L) == 0 ) {
      L->front = L->back = N;
   } else {
      N->next = L->front;
      L->front->prev = N;
      L->front = N;
   }
   if(getIndex(L) != -1) {
      L->cursor_inx = L->cursor_inx+1;
   }
}

// append()
// Inserts new element after back element in this List.
void append(List L, int data) {
   if ( L == NULL ) {
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }

   Node N = newNode(data);
   if (length(L) == 0) {
      L->front = L->back = N;
   } else {
      N->prev = L->back;
      L->back->next = N;
      L->back = N;
   }
}

// insertBefore()
// Inserts new element before cursor element in this List.
// Pre: length()>0, getIndex()>=0
void insertBefore(List L, int data) {
   if ( L == NULL ) {
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if(length(L) <= 0) {
      printf("List Error: insertBefore() called on empty list.\n");
      exit(1);
   }
   if(getIndex(L) < 0) {
      printf("List Error: insertBefore() called on undefined cursor.\n");
      exit(1);
   }
   Node node = newNode(data);
   if(L->cursor == L->front) {
      L->front->prev = node;
      node->next = L->front;
      L->front = node;
      L->cursor_inx++;
   } else {
      L->cursor->prev->next = node;
      node->prev = L->cursor->prev;
      L->cursor->prev = node;
      node->next = L->cursor;
      L->cursor_inx++;
   }
}

// insertAfter()
// Inserts new element after cursor element in this List.
// Pre: length()>0, getIndex()>=0
void insertAfter(List L, int data) {
   if ( L == NULL ) {
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if(length(L) <= 0) {
      printf("List Error: insertAfter() called on empty list.\n");
      exit(1);
   }
   if(getIndex(L) < 0) {
      printf("List Error: insertAfter() called on undefined cursor.\n");
      exit(1);
   }
   Node node = newNode(data);
   if(L->cursor == L->back) {
      L->back->next = node;
      node->prev = L->back;
      L->back = node;
   } else {
      L->cursor->next->prev = node;
      node->next = L->cursor->next;
      L->cursor->next = node;
      node->prev = L->cursor;
   }
}

// deleteFront()
// Deletes the front element in this List. Pre: length()>0
void deleteFront(List L) {
   if ( L == NULL ) {
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if(length(L) <= 0) {
      printf("List Error: deleteFront() called on empty list.\n");
      exit(1);
   }
   Node tmp = L->front;
   if(length(L) > 1) {
      L->front = L->front->next;
      L->front->prev = NULL;
      if(L->cursor_inx != -1)
         L->cursor_inx--;
   } else {
      L->front = L->back = L->cursor = NULL;
      L->cursor_inx = -1;
   }
   freeNode(&tmp);
}

// deleteBack()
// Deletes the back element in this List. Pre: length()>0
void deleteBack(List L) {
   if ( L == NULL ) {
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
   if(length(L) <= 0) {
      printf("List Error: deleteBack() called on empty list.\n");
      exit(1);
   }
   if(L->cursor == L->back) {
      L->cursor = NULL;
      L->cursor_inx = -1;
   }
   Node tmp = L->back;
   if(length(L) > 1) {
      L->back = L->back->prev;
      L->back->next = NULL;
   } else {
      L->front = L->back = L->cursor = NULL;
      L->cursor_inx = -1;
   }
   freeNode(&tmp);
}

// delete()
// Deletes cursor element in this List. Cursor is undefined after this
// operation. Pre: length()>0, getIndex()>=0
void delete(List L) {
   if ( L == NULL ) {
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   if(length(L) <= 0) {
      printf("List Error: delete() called on empty list.\n");
      exit(1);
   }
   if(getIndex(L) < 0) {
      printf("List Error: delete() called on undefined cursor.\n");
      exit(1);
   }
   Node tmp = L->cursor;
   if(L->cursor == L->front) {
      L->front = L->front->next;
      L->front->prev = NULL;
   } else if(L->cursor == L->back) {
      L->back = L->back->prev;
      L->back->next = NULL;
   } else {
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
   }
   L->cursor = NULL;
   L->cursor_inx = -1;
   freeNode(&tmp);
}

// Other operations -----------------------------------------------------------

// printList()
// Prints data elements in L on a single line to file out.
void printList(FILE* out, List L) {
   if ( L == NULL ) {
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }
   
   Node N = NULL;
   for(N = L->front; N != NULL; N = N->next) {
      printf("%d ", N->data);
   }
   printf("\n");
}

// copyList()
// Returns a new list representing the same integer sequence as this
// list. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L) {
   if ( L == NULL ) {
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(1);
   }
   List list = newList();
   Node N = L->front;

   while( N != NULL ) {
      append(list, N->data);
      N = N->next;
   }
   return list;
}

// concatList()
// Returns a new List which is the concatenation of
// this list followed by L. The cursor in the new list
// is undefined, regardless of the states of the cursors
// in this list and L. The states of this list and L are
// unchanged.
List concatList(List A, List B) {
   if ( A == NULL  || B == NULL ) {
      printf("List Error: calling concatList() on NULL List reference\n");
      exit(1);
   }

   List list = newList();
   Node N = A->front;
   Node M = B->front;

   while( N != NULL ) {
      append(list, N->data);
      N = N->next;
   }
   while( M != NULL ) {
      append(list, M->data);
      M = M->next;
   }
   return list;
}



