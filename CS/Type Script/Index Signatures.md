Normally in typescript, you can define an object type with definite fields and types like this:
```ts
metadata: {
    documentId: string;
    userId: string;
    timestamp: string;
    nonce?: string;
  };
```
So every object of type `metadata` must have the following keys: `documentId, userId, timestamp`. Optionally, it may also have a `nonce` key. The values of all these must be strings.
Otherwise, the typescript compiler will throw an error.

Now what if we didn't want such a rigid structure? What if we wanted to add versatility to the objects?
Suppose we don't know how many fields there would be because some of them were optional. And some keys may have different types of values. 
In a such a case, we use a special typescript syntax that's referred to as an *index signature*:
```ts
fields: {
    [fieldId: string]: string | number | boolean | File | null;
  }
```
This means that the `fields` object can have an arbitrary number of fields. The keys are all of type `string`, while the value types can range anywhre from `string`, `number`, `boolean`, `File`, and `null`.
