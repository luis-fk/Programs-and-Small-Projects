//encapsulation is the idea of making some stuff private and other
//public in our code. For instance, attribtues should always be private
//instaces may be public and methods can be either, depending on weather
//or not we want users to use them

class pc {
    //making the attributes private prevents the users from changing theses
    //values however they want
    private String model;
    private String processor;
    private String graphicsCard;
    private int storage;
    private int ram;

    public pc (String m, String p, String gr, int s, int r){
        model = m;
        processor = p;
        graphicsCard = gr;
        storage = s;
        ram = r;
    }

    //this are the only 2 methods the user has access to, so he cannot
    //change the values of the computer special upgrade and can only
    //print the details of the computer by calling this function
    public void upgrade() {
        specialUpgrade();
    }

    public void describe() {
        System.out.printf("%nYou have a %s computer, with a %s processor and a %s graphics " +
                            "card. It also has %dGB of storage and %dGB of RAM%n", 
                            model, processor, graphicsCard, storage, ram);
    }

    private void specialUpgrade() {
        processor = "i7";
        storage = 2000;
        ram = 16;
    }

    //here is a function that's called a getter, meaning it is used to
    //get the attribute's info. Theses functions start with get.
    public String getModel (){
        return model;
    }

    public String getGraphicsCard () {
        return graphicsCard;
    }

    //here we have setter, that change attributes. Here is the step
    //where we can validade the user input before actually changing 
    //the attribute
    public void setGraphicsCard(String newGraphicsCard) {
        graphicsCard = newGraphicsCard;
    }
}

public class encapsulation {
    public static void main(String[] args){
        pc myPc = new pc("Acer", "i5", "NVIDIA", 1000, 8);

        myPc.describe();
        myPc.upgrade();
        myPc.describe();

        System.out.println(myPc.getModel());

        myPc.setGraphicsCard("AMD");
        System.out.println(myPc.getGraphicsCard());
    }
}

