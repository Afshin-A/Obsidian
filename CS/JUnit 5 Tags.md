It is possible to sort through unit tests and only run a selection of tests. We can "tag" the unit tests.

```java
@Test
@Tag("Functional")
void functionalTest1() {
	//...
}
```
In Intellij, go to run configurations, under Build and Run select Tags from the drop menu. Then enter the name of the tag.

We can also create custom annotations that include the Tag annotation

```java
import org.junit.jupiter.api.Tag;  
  
import java.lang.annotation.ElementType;  
import java.lang.annotation.Retention;  
import java.lang.annotation.RetentionPolicy;  
import java.lang.annotation.Target;  
  
@Target({ElementType.TYPE, ElementType.METHOD})  
@Retention(RetentionPolicy.RUNTIME)  
@Tag("non-functional")  
@Tag("performance")
public @interface Performance {}
```
```java
@Test
@Perfomance
void functionalTestExample() {
	//...
}
```

A test case can have multiple tags. This means `functionalTestExample()` would be executed if we filter for "non-functional" or "performance" test cases.
This can be used to form a structural hierarchy for the test types, such as:
![[Pasted image 20221125122039.png]]
_Mastering Software Testing with JUnit 5_ (page 113)