Suppose you have a class like this:
```c#
public class BankAccount
{
    public string AccountNumber { get; init; }
    public decimal Balance { get; } = 0; // inline 
    public BankAccount() { }
}
```
# Property Accessors
## Set Accessors

1. No `set`—The property can only be set inline in the class or via constructor. It then becomes immutable. Cannot use the [[Object Initialization in CSharp#Object Initializer syntax|object initializer syntax]] with this accessor.
```c#
public decimal Balance { get; }
```

2. `private set`—Only the class can internally set or modify the value.
```c#
public decimal Balance { get; private set;}
```

3. `init`—Anyone *can* set the value during object initialization with constructor, or by using the object initializer syntax. But once the value is set, it becomes read-only and can never be changed.
```c#
public decimal Balance { get; init;}
```

4. `set`—Anyone can set the value
```c#
public decimal Balance { get; set;}
```


# Object Initializer Syntax
If allowed by access the [[Object Initialization in CSharp#Set Accessors|property accessors]], you can use the following syntax to set the properties when instantiating a class:
```c#
public static void Main() {
	var myBankAccount = new BankAccount() 
	{
		AccountNumber = "123456";
	}
}
```
What this does is, *initializing an object then immediately setting its properties.*



In JSON parsing, **"top level"** refers to ==the **outermost container or value** that wraps the entire JSON string==. It represents the absolute starting point of the JSON structure, containing all other nested elements.