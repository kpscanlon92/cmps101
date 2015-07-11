//-----------------------------------------------------------------------------
//  Name: Kelly Scanlon
//  User: kpscanlo
//  Assignment: pa3
//
//  Matrix.java
//  A matrix ADT that represents the "sparse" entries using 
//  a List ADT to contain each row, and the list nodes contain the
//  entries (col, data).
//-----------------------------------------------------------------------------

class Matrix {
   
   private class Entry {
      // Fields
      int col;
      double data;
      // Constructor
      Entry(int col, double data) {
         this.col = col;
         this.data = data;
      }
      public String toString() {
         String str = "(";
         str += String.valueOf(this.col) + ", ";
         str += String.valueOf(this.data) + ")";
         return str;
      }
      public boolean equals(Object x) {
         if( !(x instanceof Entry) ) return false;
         if (x == this) return true;
         Entry E = (Entry)x;

         if (this.col == E.col && this.data == E.data) return true;
         return false;
      }
   }

   // Fields
   private List[] row;
   private int size;
   private int NNZ;

   // Constructor
   // Makes a new n x n zero Matrix.
   // Pre: n>=1
   Matrix(int n) {
      if(n < 1) {
         throw new RuntimeException("Matrix Error: Matrix size not valid");
      }
      size = n;
      NNZ = 0;
      row = new List[size];
      for (int i = 0; i < size; i++)
         row[i] = new List();
   }

   // Access Function
   // getSize(): Returns n, the number of rows and columns of this Matrix
   int getSize() {
      return size;
   }

   // getNNZ(): Returns the number of non-zero entries in this Matrix
   int getNNZ() {
      return NNZ;
   }

   // equals(): overrides Object's equals() method
   public boolean equals(Object x) {
      if ( !(x instanceof Matrix) ) return false;
      if (x == this) return true;
      Matrix M = (Matrix)x;

      boolean flag = true;
      int i = 0;
      if (this.size == M.size && this.NNZ == M.NNZ) {
         while(i < size && flag) {
            flag = this.row[i].equals(M.row[i]);
            i++;
         }
      } else {
         return false;
      }
      return flag;
   }

   
   // Manipulation procedures
   // makeZero(): set this Matrix to the zero state
   void makeZero() {
      for(int i = 0; i < size; i++) {
         row[i].clear();
      }
      NNZ = 0;
   }

   // copy(): returns a new Matrix having the same entries as this Matrix
   Matrix copy() {
      Matrix M = new Matrix(size); 
      List R;

      for(int i = 0; i < size; i++) {
         R = row[i];
         R.moveTo(0);
         while(R.getIndex() != -1) {
            Entry E = (Entry) R.getElement();
            E = new Entry(E.col, E.data);
            M.row[i].append(E);
            R.moveNext();
         }
      }
      M.NNZ = NNZ;
      
      return M;
   }

   // changeEntry(): changes the ith row, jth column of this Matrix to x
   // pre: 1<=i<=getSize(), 1<=j<=getSize()
   void changeEntry(int i, int j, double x) {
      if(i<1 || i>this.getSize() || j<1 || j>this.getSize()) {
         throw new RuntimeException("Matrix Error: changeEntry() called for invalid entry");
      }

      List R = row[i-1];

      // If the row is empty, create Entry and place into row
      if(R.length() == 0 && x != 0) {
         Entry E = new Entry(j, x);
         R.append(E);
         NNZ++;
      } 
      // If the row isn't empty, find place in row to place or replace entry
      else if (x != 0) {
         R.moveTo(0);
         Entry currE = (Entry) R.getElement();
         int currCol = currE.col;
         while(R.getIndex() != -1) {
            if(currCol == j) {
               currE.data = x;
               return;
            } else if(currCol > j) {
               Entry E = new Entry(j, x);
               R.insertBefore(E);
               NNZ++;
               return;
            } else {
               R.moveNext();
               if(R.getIndex() != -1) {
                  currE = (Entry) R.getElement();
                  currCol = currE.col;
               }
            }
         }
         Entry E = new Entry(j, x);
         R.append(E);
         NNZ++;
      }
   }

   // scalarMult(): returns a new Matrix that is the scalar product of this Matrix with x
   Matrix scalarMult(double x) {
      Matrix M = this.copy();

      for(int i = 0; i < size; i++){
         M.row[i].moveTo(0);
         while(M.row[i].getIndex() != -1) {
            Entry currE = (Entry) M.row[i].getElement();
            M.changeEntry(i+1, currE.col, currE.data*x);
            M.row[i].moveNext();
         }
      }

      return M;
   }

   // add(): returns a new Matrix that is the sum of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix add(Matrix M) {
      if(this.getSize() != M.getSize()) {
         throw new RuntimeException("Matrix Error: add() called with Matrices of different sizes");
      }

      if(M == this) {
         M = this.copy();
      }

      Matrix N = new Matrix(size);

      for(int i = 0; i < size; i++) {
         M.row[i].moveTo(0);
         row[i].moveTo(0);
         
         while((M.row[i].getIndex() != -1) || (row[i].getIndex() != -1)) {
            if(M.row[i].getIndex() != -1 && row[i].getIndex() != -1) {
               Entry McurrE = (Entry) M.row[i].getElement();
               Entry currE = (Entry) row[i].getElement();
               if(McurrE.col == currE.col) {
                  Entry E = new Entry(McurrE.col, currE.data+McurrE.data);
                  if(E.data != 0) {
                     N.row[i].append(E);
                     N.NNZ++;
                  }   
                  M.row[i].moveNext();
                  row[i].moveNext();
               } else if (McurrE.col > currE.col) {
                  Entry E = new Entry(currE.col, currE.data);
                  if(E.data != 0) {
                     N.row[i].append(E);
                     N.NNZ++;
                  }
                  row[i].moveNext();
               } else if (McurrE.col < currE.col) {
                  Entry E = new Entry(McurrE.col, McurrE.data);
                  if(E.data != 0) {
                     N.row[i].append(E);
                     N.NNZ++;
                  }
                  M.row[i].moveNext();
               }
            } else if((M.row[i].getIndex() != -1) && (row[i].getIndex() == -1)) {
               Entry McurrE = (Entry) M.row[i].getElement();
               Entry E = new Entry(McurrE.col, McurrE.data);
               if(E.data != 0) {
                  N.row[i].append(E);
                  N.NNZ++;
               }
               M.row[i].moveNext();
            } else if((M.row[i].getIndex() == -1) && (row[i].getIndex() != -1)) {
               Entry currE = (Entry) row[i].getElement();
               Entry E = new Entry(currE.col, currE.data);
               if(E.data != 0) {
                  N.row[i].append(E);
                  N.NNZ++;
               }
               row[i].moveNext();
            }
         }
      }

      return N;
   }
   
   // sub(): returns a new Matrix that is the difference of this Matrix with M
   // pre getSize()==M.getSize()
   Matrix sub(Matrix M) {
      if(this.getSize() != M.getSize()) {
         throw new RuntimeException("Matrix Error: add() called with Matrices of different sizes");
      }

      if(M == this) {
         M = this.copy();
      }

      Matrix N = new Matrix(size);

      for(int i = 0; i < size; i++) {
         M.row[i].moveTo(0);
         row[i].moveTo(0);
         
         while((M.row[i].getIndex() != -1) || (row[i].getIndex() != -1)) {
            if(M.row[i].getIndex() != -1 && row[i].getIndex() != -1) {
               Entry McurrE = (Entry) M.row[i].getElement();
               Entry currE = (Entry) row[i].getElement();
               if(McurrE.col == currE.col) {
                  Entry E = new Entry(McurrE.col, currE.data-McurrE.data);
                  if(E.data != 0) {
                     N.row[i].append(E);
                     N.NNZ++;
                  }
                  M.row[i].moveNext();
                  row[i].moveNext();
               } else if (McurrE.col > currE.col) {
                  Entry E = new Entry(currE.col, currE.data);
                  if(E.data != 0) {
                     N.row[i].append(E);
                     N.NNZ++;
                  }
                  row[i].moveNext();
               } else if (McurrE.col < currE.col) {
                  Entry E = new Entry(McurrE.col, -McurrE.data);
                  if(E.data != 0) {
                     N.row[i].append(E);
                     N.NNZ++;
                  }
                  M.row[i].moveNext();
               }
            } else if((M.row[i].getIndex()) != -1 && (row[i].getIndex() == -1)) {
               Entry McurrE = (Entry) M.row[i].getElement();
               Entry E = new Entry(McurrE.col, -McurrE.data);
               if(E.data != 0) {
                  N.row[i].append(E);
                  N.NNZ++;
               }
               M.row[i].moveNext();
            } else if((M.row[i].getIndex() == -1) && (row[i].getIndex() != -1)) {
               Entry currE = (Entry) row[i].getElement();
               Entry E = new Entry(currE.col, currE.data);
               if(E.data != 0) {
                  N.row[i].append(E);
                  N.NNZ++;
               }
               row[i].moveNext();
            }
         }
      }

      return N;
   }

   // transpose(): returns a new Matrix that is the transpose of this Matrix
   Matrix transpose() {
      Matrix M = new Matrix(size);
      List R;
      Entry E;
      int j;

      for(int i = 0; i < size; i++) {
         R = row[i];
         if(row[i].length() != 0) {
            R.moveTo(0);
            while(R.getIndex() != -1) {
               E = (Entry)R.getElement();
               j = E.col;
               E = new Entry(i+1, E.data);

               M.row[j-1].append(E);
               R.moveNext();
            }
         }
      }
      M.NNZ = NNZ;
      return M;
   }

   // mult(): returns a new Matrix that is the product of this Matrix with M
   // pre: getSize()==M.getSize()
   Matrix mult(Matrix M) {
      if( size != M.size ) {
         throw new RuntimeException("Matrix ErrorL mult() called on matrices that are not of equal sizes.");
      }
      
      Matrix N = new Matrix(size);
      List R;
      List C;
      Entry E;
      double x;

      Matrix TM = M.transpose();

      for(int i = 0; i < size; i++) {
         R = row[i];
         for(int j = 0; j < size; j++) {
            C = TM.row[j];
            x = dot(R,C);
            if(x != 0) {
               E = new Entry(j+1, x);
               N.row[i].append(E);
               N.NNZ++;
            }
         }
      }
      return N;
   }

   // dot(): returns the dot product of a row and column in a Matrix
   private static double dot(List P, List Q) {
      double dot = 0;
      
      if((P.length() != 0) && (Q.length() != 0)){
         Entry PcurrE;
         Entry QcurrE;

         P.moveTo(0);
         Q.moveTo(0);
         while((P.getIndex() != -1) && (Q.getIndex() != -1)) {
            PcurrE = (Entry) P.getElement();
            QcurrE = (Entry) Q.getElement();

            if( PcurrE.col == QcurrE.col) {
               dot += PcurrE.data*QcurrE.data;
               P.moveNext();
               Q.moveNext();
            } else if( PcurrE.col < QcurrE.col) {
               P.moveNext();
            } else {
               Q.moveNext();
            }
         }
      }
      return dot;
   }

   // Other Functions
   // toString(): overrides Object's toString() method
   public String toString() {
      String str = "";
      for ( int i = 0; i < size; i++) {
         if( row[i].length() != 0) {
            str += String.valueOf(i+1) + ": ";
            str += row[i].toString() + "\n";
         }
      }
      return str;
   }

}

