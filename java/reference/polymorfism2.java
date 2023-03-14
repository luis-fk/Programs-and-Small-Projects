//an abstract class works through inheritance
abstract class Person {
    private String name;
    
    public String getName() {
      return name;
    }
    
    public void setName(String newName) {
      name = newName;
    }
    
    //when having an abstract method, the subclass will override it
    //this is useful for subclasses with their own methods
    public abstract String greeting();
  }
  
  class Engineer extends Person {
    private String specialty;
    
    public Engineer(String n, String s) {
      setName(n);
      specialty = s;
    }
    
    public String greeting() {
      return "Hello, my name is " + getName() + " and I am a(n) " + specialty + ".";
    }
  }
  
  class Artist extends Person {
    private String specialty;
    
    public Artist(String n, String s) {
      setName(n);
      specialty = s;
    }
    
    public String greeting() {
      return "My name is " + getName() + " and I work with " + specialty + ".";
    }
  }
  
  public class polymorfism2 {  
    public static void main(String[] args) {
        //here "p" and "a" are of type person
        Person p = new Engineer("Calvin", "civil engineer");
        Person a = new Artist("Maria", "water colors");

        System.out.println(p.greeting());
        System.out.println(a.greeting());
      
    }
  }