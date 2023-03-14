class mangaCharacter {
    //here are the attributes of the class
    String name;
    String skill;
    long bounty;
    int age;
    //final here makes the attribute "crew" unchangable
    final String crew = "Straw Hats";

    //here is the constructor for the class that assign values to the attributes
    //when they are instanciated 
    mangaCharacter(String n, String s, long b, int a) {
        name = n;
        skill = s;
        bounty = b;
        age = a;  
    }

    //here is a constructur to make a deep copy of a an already existing object
    mangaCharacter(mangaCharacter c) {
        name = c.name;
        skill = c.skill;
        bounty = c.bounty;
        age = c.age;
    }

    //here are function that can be called for each object created to
    //change their attributes
    void changeAge (int amount) {
        age = amount;
    }

    void changeName (String newName) {
        name = newName;
    }

    void changeSkill (String newSkill) {
        skill = newSkill;
    }

    //below is an example of a static method that adds functionality to the class
    //we are basically calling another function from a funtiction within the class
    static long addBounty (long bounty1, long bounty2) {
        return bounty1 + bounty2;
    }

    static void printBounty (mangaCharacter character1, mangaCharacter character3){
        long totalBounty = addBounty(character1.bounty, character3.bounty);
        System.out.printf("Their combined bounty is %,d.", totalBounty);
    }
}

public class objects {
    public static void main(String[] args){
        //this creates a new object of class "mangaCharacter"
        mangaCharacter character1 = new mangaCharacter("Luffy", "Rubber", 3000000000L, 17);
        System.out.println("This character's name is " + character1.name + ", he is " + character1.age +
                            " years old before the time skip, and his skill is " + character1.skill + ".");
        
        //this changes the attribute skill
        character1.skill = "Sun God";
        System.out.println("Luffy then discovered that his new skill became " + character1.skill + ".");

        //this changes the attribute internally by calling the function "changeAge"
        character1.changeAge(19);
        System.out.println("After the time skipe Luffy became " + character1.age + ".");     
        
        //this makes a shallow copy of character1, so any value changed in either character
        //will affect the other as seen below
        mangaCharacter character2 = character1;
        //character2 name is now Luffy since it is a copy
        System.out.println(character2.name);
        //change character1 name to Zoro
        character1.changeName("Zoro");
        //character2 name also changes to Zoro
        System.out.println(character2.name);
        //change character2 back to Luffy
        character2.changeName("Luffy");
        //character1 also becomes Luffy
        System.out.println(character1.name);

        //this makes a deepcopy of character1 which allows us to change the values of
        //this new character without changing character1
        mangaCharacter character3 = new mangaCharacter(character1);
        character3.changeName("Zoro");
        character3.changeSkill("Swordsman");
        character3.bounty = 1111000000L;
        System.out.println("Another member of the " + character3.crew + " is " + character3.name + ".");

        //an easier way would be to just create a new object instead
        mangaCharacter character4 = new mangaCharacter("Nami", "Weather", 366000000L, 19);
        System.out.println("Yet another member of the " + character4.crew + " is " + character4.name +
                            " whose skill is " + character4.skill + ".");

        System.out.printf("%s has a bounty of %,d and %s has a bounty of %,d. %n", 
                            character1.name, character1.bounty, character3.name, character3.bounty);
        mangaCharacter.printBounty(character1, character3);
    }
}
