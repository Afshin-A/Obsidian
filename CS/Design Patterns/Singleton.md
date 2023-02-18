Some classes should only be instantiated once. The Singleton design pattern helps with that.

```java
public class SingletonClass {
	// must be static because getInstance() is static
	private static SingletonClass instance = null;
	// private constructor does not allow instantiation
	private SingletonClass() {
	}
	// must be static because, how else can you call the method for the first time without being able to instantiate the class?
	public static void getInstance () {
		if (instance == null) {
			instance = new SingletonClass();
		}
		return instance;
	}
}
```

This works perfectly good. But a multithreading applications can sometimes bypass it and create multiple instances. If 2 threads both get to `instance == null` at the same time, they would both inter the `if` body and create 2 new instances:

```java
static boolean firstThread = true;  
  
public static SingletonScrabble getInstance() {

	/* In a multithreaded application, the first thread enters this statement, and sleeps. The second thread then enters, seeing the firstThread boolean value is now false, and proceeds to create an instance because instance is null at this point. Then, the first thread wakes up and creates a second instance, thereby ruining the whole point of the  Singleton design pattern */

        if (instance == null) {  
            if (firstThread) {  
                firstThread = false;  
                try {
                    Thread.sleep(1000);  
                } catch (InterruptedException e) {  
                    throw new RuntimeException(e);  
                }  
            }  
            instance = new SingletonScrabble();  
            Collections.shuffle(instance.letterList);  
        }  
        return instance;  
    }  
}
```

Solution: use `synchronized`. It means all threads have to wait their turn before accessing this method
Method 1. add the keyword synchronized to the method header for `getInstance()` 
The problem with this way is that it significantly slows down the program

```java
static boolean firstThread = true;  
  
public static synchronized SingletonScrabble getInstance() {

        if (instance == null) {  
            if (firstThread) {  
                firstThread = false;  
                try {
                    Thread.sleep(1000);  
                } catch (InterruptedException e) {  
                    throw new RuntimeException(e);  
                }  
            }  
            instance = new SingletonScrabble();  
            Collections.shuffle(instance.letterList);  
        }  
        return instance;  
    }  
}
```

Method 2: The right way
```java
static boolean firstThread = true;  
  
public static SingletonScrabble getInstance() {
    synchronized (SingletonScrabble.class) {  
        if (instance == null) {  
            if (firstThread) {  
                firstThread = false;  
                try {  
                    Thread.sleep(0);  
                } catch (InterruptedException e) {  
                    throw new RuntimeException(e);  
                }  
            }  
            instance = new SingletonScrabble();  
            Collections.shuffle(instance.letterList);  
        }  
        return instance;  
    }  
}
```