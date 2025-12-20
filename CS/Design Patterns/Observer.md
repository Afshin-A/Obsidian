This design pattern is used to update many objects without tight coupling.

In short, it stores a list of observer objects. When a condition becomes true, it updates some field in all of those objects

A **Subject** (publisher/observable) sends updates to the **Observers** (subscribers/receivers).
It's called the subject because the observers are observing it.
*Observers observe the subject for changes.*
One advantage of this pattern is loose coupling between the Subject and Observer, meaning the Subject does not need to know anything about the Observers. And, making changes in one class does not affect the other classes.

```plantuml
@startuml Strategy Design Pattern

skinparam groupInheritance 2
hide empty members

interface Subject {
	+ void register(Observer o)
	+ void unregister(Observer o)
	+ void notifyObservers()
}

class StockGrabber implements Subject {
	- ArrayList<Observer> subscriberList
	- double ibmStockPrice
	- double appleStockPrice
	- double googleStockPrice
	+ void register(Observer o)
	+ void unregister(Observer o)
	+ void notifyObservers()
	+ void setIbmStockPrice(double ibmPrice)
	+ void setAppleStockPrice(double applPrice)
	+ void setGoogleStockPrice(double goglPrice)
}

interface Observer {
	+ void update(double ibmPrice, double applPrice, double goglPrice)
}

class StockObserver implements Observer {
	- double ibmPrice
	- double applPrice
	- double goglPrice
	- static int subscriberIDTracker
	- int subscriberID
	- Subject publisherReference
	+ StockObserver(Subject publisherReference)
	+ void update(double ibmPrice, double applPrice, double goglPrice)
}

class MainProgram {
	+ void checkIbmPrice()
	+ void checkApplPrice()
	+ void checkGoglPrice()
}

Subject -> Observer
MainProgram -> StockGrabber

@enduml
```
[Click here if the diagram does not load.](https://www.plantuml.com/plantuml/png/jLJ1QeD043rNy1_cQ6XowRc41091Q6be-WFhEjbiTNTbTWs4ad_lAj6irlJK7lNDp7lFDsCShQnZv6fLmjuHSoZEi44hXOOTSmv9nr4SsKBgYX5J8CZKLQgFID8npH6UukWeSmHKbJk3GfKXsQP7QjzzOBvaNsUVo1rynT738voCp85GIElnv2spI2SaCBCRMklVSMsSF9mxo2OUkZIKl6JMUX-65rjYcLS2KbKbAjJE3cGiO4t4pY-UvBcRimHRPvQJz7qDq9RbfivA19cfTkoE9CSGO9MVFmq9OyG8-o_t7MJHfQ7Iv2Q_VHwMheVQay3IHFLsP2VfROg-_38ClfSV95zNkT-oiR0vZCddS6z-a79F4CGy80q3dCnk8ZKHlFJ7uIG7RobOZdJpGOmNI6t966jVThjM-PdI-cjvnmCIwkiM3CGdzujdV__TNfdKEpAYEUOW5dv4NgJNgU5AjS2wc_u3sNOi_H5sRXRBFeeu2baz49veqxD2dVjVq3S0)
`MainProgram` is responsible for creating a publisher object (`StockGrabber`), managing the subscribers (`StockObserver`) and checking for changes in stock prices. To check price changes, `MainProgram` could connect to another program, a database, etc..

`StockGrabber` is the publisher. It keeps a list of the subscribers, can add, remove from the list, and  `update` them.
For example, the only way to make changes to `ibmStockPrice` is by calling the setter `setIbmStockPrice()`. And whenever there is a change, the subscribers should be notified, so `setIbmStockPrice()` also calls `notifyObservers()`. `notifyObservers()` would go through the list its subscribers and update each one.

Why do we need a `Subject` interface?

`StockObserver` represents the subscribers, and there could be many of them. There could be different classes, and as along as they implement the `Observer` interface, the publisher would send them updates. The subscribers could then choose to do whatever they want with the received  update (update implies pblisher sends data to subscribers).
There is a new feature in `StockObserver`: The constructor takes a reference of the publisher, and using that reference, automatically registers itself to the publisher.

```java
public interface Subject {  
    // In java, interface methods are public and abstract by default  
    void register(Observer observer); 
    void unregister(Observer observer);  
    void notifyObservers();  
}

// Updates stock prices. Sends updates to observers 
public class StockGrabber implements Subject {  
	private ArrayList<Observer> subscriberList;  
	private double ibmPrice;  
	private double applePrice;
	private double googlePrice; 
	 
    public StockGrabber() {  
        subscriberList = new ArrayList<>();  
    }
    
    @Override 
    public void register(Observer observer) {  
        subscriberList.add(observer);  
    }
    @Override  
    public void unregister(Observer observer) {
        subscriberList.remove(observer);  
    }  
    @Override  
    public void notifyObservers() {  
        for (Observer observer : subscriberList) {  
            observer.update(ibmPrice, applePrice, googlePrice);  
        }  
    }
    
    public void setIbmPrice(double ibmPrice) {  
        this.ibmPrice = ibmPrice;  
        // Whenever imbPrice changes, we notify all the subscribers of that change  
        this.notifyObservers();  
    } 
    public void setApplePrice(double applePrice) {  
        this.applePrice = applePrice;  
        this.notifyObservers();  
    }
    public void setGooglePrice(double googlePrice) {  
        this.googlePrice = googlePrice;  
        this.notifyObservers();  
    }


public interface Observer {  
    public void update(double ibmStockPrice, double appleStockPrice, double googleStockPrice);  
}


public class StockObserver implements Observer {  
    private double imbPrice;  
    private double applePrice;  
    private double googlePrice;  
	private static int subscriberIDTracker = 0;
	private int subscriberID;  
    private Subject publisherReference; 
     
    public StockObserver(Subject stockGrabber) {  
        this.publisherReference = stockGrabber;  
        // increment observerIDTracker first, then permanently save it locally in this object  
        this.subscriberID = ++subscriberIDTracker;  
        System.out.println("New Observer (ID: " + this.subscriberID + ") created.");  
        // subscriber registers itself into the publisher  
        this.publisherReference.register(this);  
    }  
  
    @Override  
    public void update(double ibmStockPrice, double appleStockPrice, double googleStockPrice) {  
        this.imbPrice = ibmStockPrice;  
        this.applePrice = appleStockPrice;  
        this.googlePrice = googleStockPrice;  
        subscriberReadsStockPrices();  
    }  
  
    public void subscriberReadsStockPrices() {  
        System.out.printf("Observer: %d\nIBM: %s\nApple: %s\nGoogle: %s\n\n", subscriberID, imbPrice, applePrice, googlePrice);  
    }  
}

public class MainProgram {  
    public static void main(String[] args) {  
        StockGrabber publisher = new StockGrabber();  
  
        StockObserver subscriber1 = new StockObserver(publisher);  
        publisher.setIbmPrice(147.05);  
        StockObserver subscriber2 = new StockObserver(publisher);  
        publisher.setApplePrice(142.16);  
        publisher.setGooglePrice(92.83);  
        publisher.unregister(subscriber2);  
        publisher.notifyObservers();  
    }  
}
```


# Here's a video explanation
<iframe width="560" height="315" src="https://www.youtube.com/embed/7B1DFe0VBxI?si=b5FDvc9pyYxkSS2e" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>