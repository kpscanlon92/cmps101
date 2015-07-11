//-----------------------------------------------------------------------------
//  Name: Kelly Scanlon
//  User: kpscanlo
//  Assignment: pa3
// 
//  MatrixTest.java
//  This is a way to test the Matrix ADT in isolation.
//-----------------------------------------------------------------------------

public class MatrixTest{
   public static void main(String[] args){
      // Test making a new Matrix
      int i, j, n=100000;
      Matrix A = new Matrix(n);
      Matrix B = new Matrix(n);

      // Test adding entries to matrices
      A.changeEntry(1,1,1); B.changeEntry(1,1,1);
      A.changeEntry(1,2,2); B.changeEntry(1,2,0);
      A.changeEntry(1,3,3); B.changeEntry(1,3,1);
      A.changeEntry(2,1,4); B.changeEntry(2,1,0);
      A.changeEntry(2,2,5); B.changeEntry(2,2,1);
      A.changeEntry(2,3,6); B.changeEntry(2,3,0);
      A.changeEntry(3,1,7); B.changeEntry(3,1,1);
      A.changeEntry(3,2,8); B.changeEntry(3,2,1);
      A.changeEntry(3,3,9); B.changeEntry(3,3,1);

      // Print out Matrix A
      System.out.printf("A has %d non-zero entries%n", A.getNNZ());
      System.out.printf("A has size %d:%n", A.getSize());
      System.out.println(A);

      // Print out Matrix B
      System.out.printf("B has %d non-zero entries%n", B.getNNZ());
      System.out.printf("B has size %d:%n", B.getSize());
      System.out.println(B);
      
      // Test scalarMult()
      Matrix C = A.scalarMult(1.5);
      System.out.printf("(1.5)*A has %d non-zero entries%n", C.getNNZ());
      System.out.printf("(1.5)*A has size %d:%n", C.getSize());
      System.out.println(C);

      // Test add()
      Matrix D = A.add(A);
      System.out.printf("A+A has %d non-zero entries%n", D.getNNZ());
      System.out.printf("A+A has size %d:%n", D.getSize());
      System.out.println(D);

      // Test sub()
      Matrix E = A.sub(A);
      System.out.printf("A-A has %d non-zero entries%n", E.getNNZ());
      System.out.printf("A-A has size %d:%n", E.getSize());
      System.out.println(E);

      // Test transpose()
      Matrix F = B.transpose();
      System.out.printf("Transpose(B) has %d non-zero entries%n", F.getNNZ());
      System.out.printf("Transpose(B) has size %d:%n", F.getSize());
      System.out.println(F);

      // Test milt()
      Matrix G = B.mult(B);
      System.out.printf("B*B has %d non-zero entries%n", G.getNNZ());
      System.out.printf("B*B has size %d:%n", G.getSize());
      System.out.println(G);

      // Test copy()
      Matrix H = A.copy();
      System.out.printf("Copy(A) has %d non-zero entries%n", H.getNNZ());
      System.out.printf("Copy(A) has size %d:%n", H.getSize());
      System.out.println(H);
      
      // Test equals()
      if(A.equals(H)) System.out.println("A equals Copy(A)");
      else System.out.println("A does not equal Copy(A)");
      if(A.equals(B)) System.out.println("A equals B");
      else System.out.println("A does not equal B");
      if(A.equals(A)) System.out.println("A equals A");
      else System.out.println("A does not equal A");

      // Test makeZero()
      A.makeZero();
      System.out.printf("makeZero(A) has %d non-zero entries%n", A.getNNZ());
      System.out.printf("makeZero(A) has size %d:%n", A.getSize());
      System.out.println(A);
   }
}
