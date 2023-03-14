class TestClass {
    public int sum(int n1, int n2, int n3) {
      return n1 + n2 + n3;
    }
    
    public int sum(int n1, int n2) {
      return n1 + n2;
    }
  }
  
  public class polymorfism {  
    public static void main(String[] args) {
      
    TestClass tc = new TestClass();
    //in java, when calling a function, the program will look for a method
    //with the same number of arguments as are being passed on to the class
    //this is called method overloading
    System.out.println(tc.sum(1, 2, 3));
    System.out.println(tc.sum(1, 2));
      
    }
  }