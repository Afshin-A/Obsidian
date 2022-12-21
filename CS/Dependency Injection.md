```java
// Approach 1 - Bad
public class Service {
	Database database = new Database();
}

// Approach 2 - Bad
public class Service {
	Database database;

	public Service() {
		database = new Database();
	}
}

// Approach 3 - Good
public class Service1 {
	Database database;

	// Depencency injection
	public Service(Database database) {
		this.database = database;
	}
}

public class Main {
	public static void main(String[] args) {
		// depencency
		Database database = new Database();

		// depencency injection
		Service service = new Service(database);
	}
}
```

The problem with approaches 1 and 2 is that we are making the `Service1` class "tightly coupled" with the `Database` class. If there was some sort of an issue with the `Database` class and could not be instantiated then the `Service` class also break.
As we learned in [[Software Testing Principles and Strategies|software testing]], to perform integration testing on a system with multiple components that are not ready, we can create mock-ups of those classes that perform the bare minimum for testing purposes. This wouldn't be possible unless we make use of the dependency injection concept.
Now suppose we have another class,  `Service2`, that uses the `Database` class. Following approach 1 or 2, we would be creating two instances of `Database`. There could be thousands of such Service classes, and creating thousands of separate `Database` objects would gratuitously fill up the memory heap. We can eliminate this issue by a combination of dependency injection and the [[Singleton|Singleton design pattern]].

In summary, the advangate of dependency injection is that we can substitude malfunctioning or incomplete dependencies with something else that works.