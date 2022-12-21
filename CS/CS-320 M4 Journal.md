1. To what extent was your testing approach aligned to the software requirements? Support your claims with specific evidence.
My approach to this project has been very similar to test-driven development where, given the requirements, we create the test cases first and write code that passes those tests. Therefore, my code directly follows from and--with help from `Validations` methods--enforces the software requirements. As an example, consider the `Client.setFirstName()` method:
```java
public void setFirstName(final String firstName) {  
    Validations.validateObjectNotNull(firstName);  
    Validations.validateStringLengthIsInRange(firstName, 10);  
    // if no exception is thrown, proceed with assignment  
    this.firstName = firstName;  
}
```
The `Validations` class houses a collection of static methods that ensure String literals have certain properties, and would throw run time exceptions otherwise. The requirements for `Client.firstName` are as follows:
- It should not be `null`
- It should not be empty
- It should not be longer than 10 characters
Consequently, `Validations.validateObjectNotNull(firstName)` ensures the argument is not `null`.  `Validations.validateStringLengthIsInRange(firstName, 10)` ensures the length of String argument is between 0 (exclusive) and 10 (inclusive).


2. Defend the overall quality of your JUnit tests for the contact service and task service. In other words, how do you know that your JUnit tests were effective on the basis of coverage percentage?
Data in the following table originates from Intellij's "Run with Coverage" feature. It provides insight into how thorough our test cases examine the associated classes. 

Test Class|Associated Class|Methods (% Coverage)|Lines (% Coverage)
-------|-----|:-----:|:---:
`ContactServiceTest`|`ContactService`|100|100
`TaskServiceTest`|`TaskService`|100|100
`ContactTest`|`Contact`|75|90
`TaskTest`|`Task`|50|78
All Tests |`Validations`|100|100

We can see the test cases cover the entirety of `ContactService` and `TestService` classes. These classes each have only 1 private field, and there is no intrinsic need for methods like setters and getters ,  `toString()`, `hashCode()`, or `equals()`. On the contrary,  tthe aforementioned  methods are conducive to the `Contact` and `Task` classes because they hold many fields that need to be compared. There are also many one-liner methods that do not merit any testings and were therefore omitted from test cases. As a result, the data for `ContactTest` and `TaskTest` tests deviates from the ideal 100% coverage.


3. How did you ensure that your code was technically sound? Cite specific lines of code from your tests to illustrate.
As a fundamental principle in software testing, absence of defects is a fallacy. This program is no exception. It is constantly going through changes as new test cases reveal defects.
For example, there were originally no test cases for when any data members were assigned to `null`. I erroneously believed that JRE does not allow `null` to be passed as arguments, and therefore omitted those tests to save resources. In fact, `null` cannot be passed to literal types such as `int`, `boolean`, etc. in Java. However, objects, including those of type `String`, can be replaced with `null` when passed to method parameters. Through more testings, this defect was discovered and corrected relatively early in the project's life cycle. `Validations.validateObjectNotNull(Object o)` now checks for `null` in every setter methods in the project:
```java
public void setTaskDescription(final String taskDescription) {  
    Validations.validateObjectNotNull(taskDescription);  
    Validations.validateStringLengthIsInRange(taskDescription, 50);  
    this.taskDescription = taskDescription;  
}
```


4. How did you ensure that your code was efficient? Cite specific lines of code from your tests to illustrate.
I believe there are two factors that play major roles in my program's efficiency. 
First, reusability. Early in this project's life cycle, I began seeing myself writing similar methods in the `TaskService`, `ContactService`, and `AppointmentService` classes. To avoid superflous and inefficient code, I decided to refactor the common functionality of these methods in a `Service` superclass. (Refer to the UML diagram for this project.) A similar issue resulted in refactoring many authentication methods as the general, `static` methods that are now in the `Validations` class. 
Second, using a Map as the underlying ADT in `ContactServie` and `TaskService` methods. To illustrate, consider the `TaskService` class. 
Per the software requirements, this service class must manage a `Collection` of `Task` objects. Furthermore, each `Task` must have a unique `id`, indicating the `Task` objects are unique. At first thought, a `Set` may appear the best choice to store a collection of unique items. However, since the `Set` interface does not provide a `get()` method, we cannot simply retrieve and update the `Task` objects--another functional requirement for `TaskService`. We could use an `Iterator` and perform a brute-force search, but this approach is extremely inefficient for large `Sets`.
Instead, we use a `Map` (more specifically, a `HashMap`) that connects `taskID` to `Task`. We can easily  fulfill the requirements mentioned above using the `Map.get()` and `Map.put()` methods. Consequentally, managing `taskID` becomes the responsibility of the `TaskService` class. In other words,  `taskID` is not an attribute of `Task`. As expounded, this change significantly improves the efficiency of the program.