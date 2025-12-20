Interfaces are specifically used to define object types.
They can be implemented by classes. 
We can define the same interface multiple times and the typescript compiler merges them all into one, with what's called "declaration merging".
Interfaces can extend other interfaces.

A type is an alias for another type.
They can extend each other, but they cannot be re-declared.
Types are versatile and can be assigned to virtually any other type, including primitive types, tuples, function signatures,, objects, etc..
```ts
type MyString = string;
type MyId = string | number;
type MyTuple = [string, number];
type MyFunc = (a: string) => number;
```

