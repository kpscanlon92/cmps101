//-----------------------------------------------------------------------------
//  Name: Kelly Scanlon
//  User: kpscanlo
//  Assignment: pa3
//
//  ListTest.java
//  This is a way to test the List ADT in isolation. 
//-----------------------------------------------------------------------------

public class ListTest{
   public static void main(String[] args){
      List A = new List();
      List B = new List();

      for(int i=1; i<=20; i++){
         A.append(i);
         B.prepend(i);
      }
      System.out.println("A = " + A);
      System.out.println("B = " + B);
      
      System.out.print("A = ");
      for(A.moveTo(0); A.getIndex()>=0; A.moveNext()){
         System.out.print(A.getElement()+" ");
      }
      System.out.println();
      System.out.print("Backwards B = ");
      for(B.moveTo(B.length()-1); B.getIndex()>=0; B.movePrev()){
         System.out.print(B.getElement()+" ");
      }
      System.out.println();
      
      if(A.equals(B)) System.out.println("A equals B");
      else System.out.println("A does not equal B");
      
      System.out.println("The front element in A is: " + A.front());
      System.out.println("The front element in B is: " + B.front());
      System.out.println("The back element in A is: " + A.back());
      System.out.println("The back element in B is: " + B.back());
      A.moveTo(5);
      System.out.println("Moved cursor to 5");
      A.insertBefore(-1);
      System.out.println("Insert -1 before cursor");
      A.moveTo(15);
      System.out.println("Moved cursor to 15");
      A.insertAfter(-2);
      System.out.println("Insert -2 after cursor");
      A.moveTo(10);
      System.out.println("Moved cursor to 10");
      A.delete();
      System.out.println("Deleted 10 List item");
      A.deleteFront();
      System.out.println("Deleted front List item");
      A.deleteBack();
      System.out.println("Deleted back List item");
      System.out.println("A = " + A);
      A.clear();
      System.out.println("Length after clear: " + A.length());
   }
}

