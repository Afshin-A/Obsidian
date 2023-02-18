From `java.util.Arrays` we have:
```java
@SafeVarargs
public static <T> List<T> asList​(T... a) { ... }
```

method description

Let's study the header for this method:
- `public` means the method is public.
- `static` means the method is not tied to an instance of the class, and we do not need to instantiate the class to use it.
- `<T>` is a generic type. 
- `List<T>` is the return type. The method will return an object of type `List` (including its subclasses due to polymorphism). Because of the generic type `T`, `List<T>` means the list can contain objects of any type, since there are no bounds defined for `T`.
- `asList` is the method name.

### Variable Arguments (Varargs)
`T... a` allows you to have a variable number (including 0) of arguments. They must all be of type `T`.
We can treat as the vararg `a` normal array.
We can also mix regular arguments with variable arguments, but:
- We can only have 1 varargs
- varargs must be the last parameter
```java
public static <T> void varargExample(int a, String b, T... c) { /*...*/ }
```
