# Introduction
The Prototype Design Pattern is all about cloning objects.

There exists a method `clone()` inside `java.lang.Object`:
```java
Protected Object clone() {
	...
}
```
If you wish that a custom class inherit this method, the class must implement the `Cloneable` interface.

## Reference Copying

```java
ArrayList<Integer> list1 = new ArrayList<>();
ArrayList<Integer> list2 = list1;
```
`list1` and `list2` point to the same object in memory. We're basically giving the reference of `list1` to `list2`.

## Shallow Copying

```java
public class CloneableTestClass implements Cloneable {  
    int field1;  
    String field2;  
    ArrayList<Integer> field3;  
  
    public CloneableTestClass(int field1, String field2, ArrayList<Integer> field3) {  
        this.field1 = field1;  
        this.field2 = field2;  
        this.field3 = field3;  
    }  
  
    @Override  
    protected Object clone() throws CloneNotSupportedException {
	    // calls java.lang.Object.clone();
	    // clone() only works with objects of type Cloneable, like CloneableTestClass
	    // clone() performs a shallow-copy.
		return super.clone();
    }  
}
```

```java
public static void main(String[] args) throws CloneNotSupportedException {  
    ArrayList<Point> pointList = new ArrayList<>(List.of(new Point(0, 0)));  
    CloneableTestClass cloneableTestClass1 = new CloneableTestClass(1, "Hello", pointList);  
    CloneableTestClass cloneableTestClass2 = (CloneableTestClass)cloneableTestClass1.clone();
	
	// field1 is an int literal. As long as it is not assigned a new value,  cloneableTestClass1.field1 and cloneableTestClass2.field1 have the same memory address.
cloneableTestClass1.field1 = 5;
	// But if we change one field, they no longer share the same objects.  
boolean int_equal = System.identityHashCode(cloneableTestClass1.field1) == System.identityHashCode(cloneableTestClass2.field1);
	// int_equal is false;

	// The same thing applies to Strings

	// IN OTHER WORDS: Shallow copying actually deep-copies literal values, including String objects

	// But field3 is an ArrayList<Point> object.
	boolean array_list_equal = System.identityHashCode(cloneableTestClass1.field3) == System.identityHashCode(cloneableTestClass2.field3);
	// array_list_equal is true
	// In other words, changing cloneableTestClass1.field3 also changes cloneableTestClass2.field3
}
```

## Deep Copying

Modifying `CloneableTestClass.clone()` from above:
```java
@Override  
protected Object clone() throws CloneNotSupportedException {
	// perform shallow-copying first  
	CloneableTestClass clone = (CloneableTestClass) super.clone();  
	// manually setting up a deep-copy for the fields that are not literals
	// NOTE: This form of ArrayList instantiation (in general, Collection objects) doesn't deep-copy elements over to the new ArrayList. It shallow-copies them.
	clone.field3 = new ArrayList<>(this.field3);  
	return clone;
}
```

```java
public static void main(String[] args) throws CloneNotSupportedException {  
    ArrayList<Point> pointList = new ArrayList<>(List.of(new Point(0, 0)));  
    CloneableTestClass cloneableTestClass1 = new CloneableTestClass(1, "Hello", pointList);  
    CloneableTestClass cloneableTestClass2 = (CloneableTestClass)cloneableTestClass1.clone();

	boolean array_list_equal = System.identityHashCode(cloneableTestClass1.field3) == System.identityHashCode(cloneableTestClass2.field3);
	// array_list_equal is now false
	// While that may be the case, the elements of these two ArrayList<Point> objects are still the same. This is becase the ArrayList<>(this.field3) type of instantiation actually shallow-copies each Point object from one ArrayList to the Other. In Other words, these Point objects point to the same locations in memory:
	boolean point_equal = System.identityHashCode(cloneableTestClass1.field3.get(0)) == System.identityHashCode(cloneableTestClass2.field3.get(0));
	// point_equal is actually true.

	// But this cycle finally ends with the int literal values inside the Point objects
	boolean int_equal = System.identityHashCode(cloneableTestClass1.field3.get(0).x) == System.identityHashCode(cloneableTestClass2.field3.get(0)).x;
	// int_equal is true, but they're not the same. Changing one does not change the other.
}
```

# Prototype Design Pattern

In conclusion, the prototype deisgn pattern is basically implementing the `Cloneable` interface. You can also introduce abstraction (generalization) to the system with a `CloneFactory` class:
```java
public class CloneFactory {
	public static CloneableTestClass makeClone(CloneableTestClass ctco) {
		// ctco = cloneable test class object
		// I made it up!
		return ctco.clone();
	}
}
```
This is useful if `CloneableTestClass` had numerous subclasses. Because `CloneableTestClass` is the superclass type and implements `Cloneable`, either the superclass or the subclass must implement the `clone` method somewhere along the hierarchy. And of course, polymorphism allows us to refer subclasses as their superclass type.
[[OOO Basics#Abstraction|Abstraction]] means the `CloneFactory` has no idea what `ctco` is or what it contains, and does not need to. It only knows that `ctco` is a subclass of `CloneableTestClass`.
