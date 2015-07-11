// Name: Kelly Scanlon
// User: kpscanlo
// Assignment: pa1

// List.java
// A integer bi-directional queue

class List {

   private class Node {
      // Fields
      int data;
      Node prev;
      Node next;
      // Constructor
      Node(int data) { 
         this.data = data; 
         prev = null; 
         next = null; 
      }
      // toString: Overides Object's toString method.
      public String toString() {
         return String.valueOf(data);
      }
   }
   
   // Fields
   private Node front;
   private Node back;
   private Node cursor;
   private int cursor_inx;
      
   // Constructor
   // Creates a new empty list.
   List() { 
      front = back = cursor = null;
      cursor_inx = -1;
   }

   // Access functions //////////////////////////////////////////////////////////////////
   
   // length():  Returns numberof elements in this list.
   int length() {
      int result = 0;
      for (Node curr = front; curr != null; curr = curr.next) {
         result++;
      }
      return result;
   }

   // getIndex(): Returns the index of the cursor element in this list, or
   // returns -1 if the cursor element is undefined.
   int getIndex() {
      return cursor_inx;
   }

   // front(): Returns front element in this list. 
   // Pre: length()>0
   int front() {
      if (this.length() <= 0) {
         throw new RuntimeException("List Error: front() called on empty list");
      }
      return front.data;
   }
   
   // back(): Returns back element in this List.
   // Pre: length()>0
   int back() {
      if (this.length() <= 0) {
         throw new RuntimeException("List Error: back() called on empty list");
      }
      return back.data;
   }
   
   // getElement(): Returns cursor element in this list.
   // Pre: length()>0, getIndex()>=0
   int getElement() {
      if (this.length() <= 0) {
         throw new RuntimeException("List Error: getElement() called on empty list"); 
      }
      if (this.getIndex() < 0) {
         throw new RuntimeException("List Error: getElement() called with undefined cursor");
      }
      return cursor.data;
   }
   
   
   // equals(): Returns true if this List and L are the same integer
   // sequence. The cursor is ignored in both lists.
   boolean equals(List L) {
      boolean flag = true;
      Node N = this.front;
      Node M = L.front;

      if ( this.length() == L.length() ){
         while( flag && N!=null) {
            flag = (N.data==M.data);
            N = N.next;
            M = M.next;
         }
         return flag;
      } else {
         return false;
      }
   }
   
   // Manipulation procedures ///////////////////////////////////////////////////////////
   
   // clear(): Re-sets this List to the empty state.
   void clear() {
      front = back = cursor = null;
      cursor_inx = -1;
   }
   
   // moveTo(): If 0<=i<=length()-1, moves the cursor to the element
   // at index i, otherwise the cursor becomes undefined.
   void moveTo(int i) {
      if ( (0 <= i) && (i <= (this.length()-1)) ) {
         Node curr = front;
         for(int inx = 0; inx < i; inx++) {
            curr = curr.next;
         }
         cursor = curr;
         cursor_inx = i;
      } else {
         cursor = null;
         cursor_inx = -1;
      }
   }
   
   // movePrev(): If 0<getIndex()<=length()-1, moves the cursor one step toward the
   // front of the list. If getIndex()==0, cursor becomes undefined.
   // If getIndex()== -1, cursor remains undefined. This operation is
   // equivalent to moveTo(getIndex()-1).
   void movePrev() {
      if( (0 < this.getIndex()) && (this.getIndex() <= (this.length()-1)) ) {
         cursor = cursor.prev;
         cursor_inx--;
      } else if (this.getIndex() == 0) {
         cursor = null;
         cursor_inx = -1;
      } else if (this.getIndex() == -1) {
         cursor = null;
         cursor_inx = -1;
      }
   }

   // moveNext(): If 0<=getIndex()<length()-1, moves the cursor one step toward the
   // back of the list. If getIndex()==length()-1, cursor becomes
   // undefined. If index==-1, cursor remains undefined. This
   // operation is equivalent to moveTo(getIndex()+1).
   void moveNext() {
      if( (0 <= this.getIndex()) && (this.getIndex() < (this.length()-1)) ) {
         cursor = cursor.next;
         cursor_inx++;
      } else if (this.getIndex() == this.length()-1) {
         cursor = null;
         cursor_inx = -1;
      } else if (this.getIndex() == -1) {
         cursor = null;
         cursor_inx = -1;
      }
   }
   
   // prepend(): Inserts new element before front element in this List.
   void prepend(int data) {
      Node node = new Node(data);
      if( this.length() == 0 ) {
         front = back = node;
      } else {
         node.next = front;
         front.prev = node;
         front = node;
      }
      if(this.getIndex() != -1) {
         cursor_inx++;
      }
   }
   
   // append(): Inserts new element after back element in this List.
   void append(int data) {
      Node node = new Node(data);
      if (this.length() == 0) {
         front = back = node;
      } else {
         node.prev = back;
         back.next = node;
         back = node;
      }
   }

   // insertBefore(): Inserts new element before cursor element in this List.
   // Pre: length()>0, getIndex()>=0
   void insertBefore(int data) {
      if(this.length() <= 0) {
         throw new RuntimeException("List Error: insertBefore() called on empty list.");
      }
      if(this.getIndex() < 0) {
         throw new RuntimeException("List Error: insertBefore() called on undefined cursor.");
      }
      Node node = new Node(data);
      if(cursor == front) {
         front.prev = node;
         node.next = front;
         front = node;
         cursor_inx++;
      } else {
         cursor.prev.next = node;
         node.prev = cursor.prev;
         cursor.prev = node;
         node.next = cursor;
         cursor_inx++;
      }
   }
   
   // insertAfter(): Inserts new element after cursor element in this List.
   // Pre: length()>0, getIndex()>=0
   void insertAfter(int data) {
      if(this.length() <= 0) {
         throw new RuntimeException("List Error: insertAfter() called on empty list.");
      }
      if(this.getIndex() < 0) {
         throw new RuntimeException("List Error: insertAfter() called on undefined cursor.");
      }
      Node node = new Node(data);
      if(cursor == back) {
         back.next = node;
         node.prev = back;
         back = node;
      } else {
         cursor.next.prev = node;
         node.next = cursor.next;
         cursor.next = node;
         node.prev = cursor;
      }
   }
   
   // deleteFront(): Deletes the front element in this List. Pre: length()>0
   void deleteFront() {
      if(this.length() <= 0) {
         throw new RuntimeException("List Error: deleteFront() called on empty list.");
      }
      if(this.length() > 1) {
         front = front.next;
         front.prev = null;
         if(cursor_inx != -1)
            cursor_inx--;
      } else {
         this.clear();
      }
   }

   //void deleteBack(): Deletes the back element in this List. Pre: length()>0
   void deleteBack() {
      if(this.length() <= 0) {
         throw new RuntimeException("List Error: deleteBack() called on empty list.");
      }
      if(cursor == back) {
         cursor = null;
         cursor_inx = -1;
      }
      if(this.length() > 1) {
         back = back.prev;
         back.next = null;
      } else {
         this.clear();
      }
   }

   // delete(): Deletes cursor element in this List. Cursor is undefined after this
   // operation. Pre: length()>0, getIndex()>=0
   void delete() {
      if(this.length() <= 0) {
         throw new RuntimeException("List Error: delete() called on empty list.");
      }
      if(this.getIndex() < 0) {
         throw new RuntimeException("List Error: delete() called on undefined cursor.");
      }
      if(cursor == front) {
         front = front.next;
         front.prev = null;
      } else if(cursor == back) {
         back = back.prev;
         back.next = null;
      } else {
         cursor.prev.next = cursor.next;
         cursor.next.prev = cursor.prev;
      }
      cursor = null;
      cursor_inx = -1;
   }
   
   // Other methods /////////////////////////////////////////////////////////////////////

   // toString(): Overides Object's toString method. Creates a string
   // consisting of a space separated sequence of integers
   // with front on the left and back on the right. The
   // cursor is ignored.
   public String toString() {
      String str = "";
      for(Node N = front; N != null; N = N.next) {
         str += N.toString() + " ";
      }
      return str;
   }
   
   // copy(): Returns a new list representing the same integer sequence as this
   // list. The cursor in the new list is undefined, regardless of the
   // state of the cursor in this List. This List is unchanged.
   List copy() {
      List L = new List();
      Node N = this.front;

      while( N != null ) {
         L.append(N.data);
         N = N.next;
      }
      return L;
   }
   
   // concat(): Returns a new List which is the concatenation of
   // this list followed by L. The cursor in the new list
   // is undefined, regardless of the states of the cursors
   // in this list and L. The states of this list and L are
   // unchanged.
   List concat(List L) {
      List list = new List();
      Node this_N = this.front;
      Node L_N = L.front;

      while( this_N != null ) {
         list.append(this_N.data);
         this_N = this_N.next;
      }
      while( L_N != null ) {
         list.append(L_N.data);
         L_N = L_N.next;
      }
      return list;
   }

}
