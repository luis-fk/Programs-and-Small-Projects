//composition is the idea of making a class out of an attribute
//of another class, to expand the details of it. It similar to a SQL
//ID that is shared among tables and can be used to retrieve information
//from it
class Car {
    private String make;
    private String model;
    private int year;
    private Engine engine;
    
    public Car(String ma, String mo, int y, Engine e) {
      make = ma;
      model = mo;
      year = y;
      engine = e;
    }
    
    public void describe() {
      System.out.println(String.format("%s %s %s", make, model, year));
    }

    public String getMake() {
        return make;
    }

    public String getmodel() {
        return model;
    }
    
    public Engine getEngine() {
      return engine;
    }
  }
  
  class Engine {
    private String configuration;
    private double displacement;
    private int horsepower;
    private int torque;
    
    public Engine(String c, double d, int h, int t) {
      configuration = c;
      displacement = d;
      horsepower = h;
      torque = t;
    }
    
    public void describe() {
        System.out.println(String.format("%s %.2f %d %d", configuration, displacement, 
                                         horsepower, torque));
      }
  }
  
  public class composition {  
    public static void main(String[] args) {
  
    Engine engine1 = new Engine("V8", 5.8, 326, 344);
    Car car1 = new Car("De Tomaso", "Pantera", 1979, engine1);
    
    //this will call getEngine from "car", which will then return the 
    //"engine1" class which will be passed to describe in the "engine"
    //class
    car1.getEngine().describe();
    }
  }