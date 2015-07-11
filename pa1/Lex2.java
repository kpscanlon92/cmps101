// Name: Kelly Scanlon
// User: kpscanlo
// Assignment: pa1

import java.io.*;
import java.util.Scanner;
import java.lang.String;


class Lex2 {
   public static void main(String[] args) throws IOException {
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      String[] lines = null;
      int  lineNumber = 0, n = 0;
      List L = new List();

      if(args.length < 2) {
         System.err.println("Usage: FileIO infile outfile");
         System.exit(1);
      }

      in = new Scanner(new File(args[0]));
      while( in.hasNextLine() ) {
         line = in.nextLine();
         lines = line.split("\\n");
         n = lines.length;
      }
      in.close();

      while( lineNumber < n ) {
         if(lineNumber > 0) {
            L.moveTo(lineNumber - 1);
            int i = lineNumber - 1;
            String tmp = lines[lineNumber];
            while(i > 0 && tmp.compareTo(lines[L.getElement()])<0) {
               L.movePrev();
               i--;
            }
            if(tmp.compareTo(lines[L.getElement()])<0)
               L.insertBefore(lineNumber);
            else
               L.insertAfter(lineNumber);
         } else {
            L.append(lineNumber);
         }
         lineNumber++;
      }
      
      out = new PrintWriter(new FileWriter(args[1]));
      L.moveTo(0);
      for(int i = 0; i < n; i++) {
         out.println(lines[L.getElement()]);
         L.moveNext();
      }
      out.close();
   }
}

