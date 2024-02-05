Suppose we have classes that use different ways to store data, be it different objects from the `Collection` library, the `Dictionary` library, or even plain old java Arrays. This design pattern brings unity into our custom classes by allowing us to iterate all through their data in the same way.

 `Iterator` (available for all `Collection` classes) and `ListIterator` (available for `List` classes)  from `java.util` aren't a new concept. We've previously used them to navigate and manipulate
```java
ArrayList<Integer> list = new ArrayList<>();
Iterator<Integer> itr = list.iterator();
while(itr.hasNext()) {
	System.out.println(itr.next() + " ");
}
```
`ListIterator` offers more functionality such as traversing backwards, and adding to the list.
In addition to polymorphism and enhanced-for loops, `Iterator` retains its current position in a list, allowing list traversals much faster than traditional for-loops, which restarts at the begining of a list every time.

```java
public <T> void iteratorTest(Collection<T> c) {
	Iterator<T> itr = c.iterator();
}
```



Suppose you have 3 classes. These classes internally use 3 different data structures. `ArrayList<String>`, `String[]`, and `HashTable<String>`.
Different data structures offer an `Iterator` in different ways. 
`ArrayList` has `.iterator()`, `HashTable` has `values().iterator()`, and arrays do not have a direct way.
So we need to unify our classes by making them implement an interface. This interface will force the classes to implement their own ways of returning an iterator.
```java
import java.util.Iterator;
public interface OffersIterator {
	Iterator<String> getIterator();
}

public class Class1 implements OffersIterator {
	private HashTable<String> data;
	public Class1() {
		data = new HashTable();
	}
	public Iterator<String> getIterator() {
		return data.values().iterator();
	}
}
```

If another class needs to iterate over the data structures inside our 3 classes, that class would contain `Iterator` fields, not ADT (Abstract Data Type) fields.

```java
public class DataPurveyor {
	public void showData(OffersIterator i) {
		while (i.hasNext()) {
			// do something
		}
	}
}
```

Once again, we can see [[OOO Basics#Abstraction|abstraction]] in work here: `DataPurveyor.showData()` does not know anything about the objects it receives as argument. `DataPurveyor` does not depend on any other classes either (loose coupling).