1. To what extent was your testing approach aligned to the software requirements? Support your claims with specific evidence.

My approach to this project has been very similar to test-driven development, where given the requirements, we to first create test cases and then write code that passes those test cases. Therefore, my code directly follows from, and with help from `Validations` methods, enforces the software requirements. As an example, consider the `Client.setFirstName()`
```java
public void setFirstName(final String firstName) {  
    Validations.validateObjectNotNull(firstName);  
    Validations.validateStringLengthIsInRange(firstName, 10);  
    // if no exception is thrown, proceed with assignment  
    this.firstName = firstName;  
}
```
The `Validations` houses a collection of static methods that ensure String literals have certain properties, and would throw run time exceptions otherwise. The requirements for `Client.firstName` are that:
- It should not be null
- It should not be empty
- It should not be longer than 10 characters
Consequently, `Validations.validateObjectNotNull(firstName)` ensures the argument is not `null`.  `Validations.validateStringLengthIsInRange(firstName, 10)` ensures the String argument's length is between 0 (exclusive) and 10 (inclusive).