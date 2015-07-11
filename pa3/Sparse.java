//-----------------------------------------------------------------------------
//  Name: Kelly Scanlon
//  User: kpscanlo
//  Assignment: pa3
// 
//  Sparse.java
//  This is the main program that implements Matrix.java and List.java.
//  It takes in two arguments for the input file and the output file.
//  It reads through the input file which contains the information for
//  two matrices, A and B. It then outputs to the file: A, B, (1.5)A, 
//  A+B, A+A, B-A, A-A, transpose(A), AB, BB.
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;
import java.lang.String;

public class Sparse{
   public static void main(String[] args){
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      int lineNumber = 0;
      String[] token = null;
      int tokenLength;
      int n, a=0, b=0;
      Matrix A = new Matrix(1);
      Matrix B = new Matrix(1);

      int i, j;
      double data;

      if(args.length != 2) {
         System.err.println("Usage: FileIO infile outfile");
         System.exit(1);
      }
      try {
         in = new Scanner(new File(args[0]));
         while(in.hasNextLine()) {
            line = in.nextLine();
            token = line.split("\\s+");
            tokenLength = token.length;

            if(lineNumber == 0) {
               n = (int) Integer.parseInt(token[0]);
               a = (int) Integer.parseInt(token[1]);
               b = (int) Integer.parseInt(token[2]);
               A = new Matrix(n);
               B = new Matrix(n);
            } else if ( lineNumber > 1 && lineNumber < (a+2) ) {
               i = (int) Integer.parseInt(token[0]);
               j = (int) Integer.parseInt(token[1]);
               data = (double) Double.parseDouble(token[2]);
               A.changeEntry(i, j, data);
            } else if ( lineNumber > (a+2) && lineNumber < (a+2+b+1) ) {
               i = (int) Integer.parseInt(token[0]);
               j = (int) Integer.parseInt(token[1]);
               data = (double) Double.parseDouble(token[2]);
               B.changeEntry(i, j, data);
            }
            lineNumber++;
         }
         in.close();
      } catch (FileNotFoundException ex) {
         System.err.println("Sparse Error: infile not found");
         System.exit(1);
      }
      if( a != A.getNNZ() || b != B.getNNZ()) {
         System.err.println("Sparse Error: Number of non-zero values is incorrect");
         System.exit(1);
      }
      
      try {
         out = new PrintWriter(new FileWriter(args[1]));

         out.printf("A has %d non-zero entries:%n", A.getNNZ());
         out.println(A);

         out.printf("B has %d non-zero entries:%n", B.getNNZ());
         out.println(B);

         out.println("(1.5)*A =");
         Matrix C = A.scalarMult(1.5);
         out.println(C);

         out.println("A+B =");
         Matrix D = A.add(B);
         out.println(D);

         out.println("A+A =");
         Matrix E = A.add(A);
         out.println(E);
 
         out.println("B-A =");
         Matrix F = B.sub(A);
         out.println(F);

         out.println("A-A =");
         Matrix G = A.sub(A);
         out.println(G);

         out.println("Transpose(A) =");
         Matrix H = A.transpose();
         out.println(H);

         out.println("A*B =");
         Matrix I = A.mult(B);
         out.println(I);

         out.println("B*B =");
         Matrix J = B.mult(B);
         out.println(J);
         
         out.close();
      } catch (IOException ex) {
         System.err.println("Sparse Error: ");
         System.exit(1);
      }
   }
}

