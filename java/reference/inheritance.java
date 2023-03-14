//we have two classes, person as the superclass and superhero as the subclass, 
//which share common attributes to avoid having to create such a similar 
//class, we can simply extend person into superhero. 
class person {
    private String name;
    private int age;
    private String occupation;
    
    public person (String na, int a, String o) {
      name = na;
      age = a;
      occupation = o;
    }

    public String getName() {
      return name;
    }
    
    public int getAge() {
      return age;
    }
    
    public String getOccupation() {
      return occupation;
    }
    
    //here the key word final makes it so sayHello can only be used here
    //and not it any other subclass, so no function with the same name
    //can exist
    public final void sayHello() {
      System.out.println("Hello, my name is " + name + ".");
    }
    
    public void sayAge() {
      System.out.println("I am " + age + " years old.\n");
    }
  }
  
  class superHero extends person {
    private String secretIdentity;
    private String nemesis;

    //super can be used with dot notation to access values and functions
    //declared in the superclass, in the case below, we are using it to
    //call the constructor from the superclass
    public superHero(String na, int a, String o, String s, String ne) {
      super(na, a, o);
      secretIdentity = s;
      nemesis = ne;
    }

    public void setSecretIdentity(String newIdentity) {
      secretIdentity = newIdentity;
    }

    public void setNemesis(String newNemesis) {
      nemesis = newNemesis;
    }

    public String getSecretIdentity() {
      return secretIdentity;
    }

    public String getNemesis() {
      return nemesis;
    }
  }
  
  public class inheritance {
    public static void main(String[] args) {
      person p = new person("Samantha", 29, "Programmer");
      p.sayHello();
      p.sayAge();

      superHero hero = new superHero("Wonder Woman", 27, "intelligence officer", "Amazon", "Cheeta");
      hero.sayHello();
      hero.sayAge();

      System.out.println(hero.getSecretIdentity());
      System.out.println(hero.getNemesis() + "\n");

      //below is an example of the substitution principle, we can simply call
      //the function to print a class' greeting like below
      substitution(p);

      //but at the same time we can use the subclass to subsitute the
      //superclass even though the function accepts a person as a paremeter
      substitution(hero);
    }

    public static void substitution(person p) {
      p.sayHello();
    }
  }