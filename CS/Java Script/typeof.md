```js
console.log(typeof 'Hello');
console.log(typeof 1);
```

# `Number.toFixed(x)`
Sets the number of decimal places 
```js
let x = 1.26e5
console.log(x.toFixed(1)); // outputs 126000.0
```


# Spread operator

Works similar to unpacking in python
```js
const geoOptions = {
	distanceField: "distance.calculated",
    spherical: true,
    maxDistance: 20000,
    limit: 10
};

const geoOptions2 = {
	authorized: true,
	...geoOptions 
}

const alphabet = ['a', 'b', 'c', 'd'];

console.log(geoOptions2);
console.log(...alphabet);
```

# `String.split()`
Returns an array of strings split
```js
const str = "Hello World!";
console.log(str.split(' ')); // returns ["Hello", "World!"]
console.log(str.split('')); // returns ['H', 'e', 'l', 'l', 'o', 'W', 'o'...]
```

# `.push()`
`Array.prototype.push()` appends an element to an array
```js
const a = ['Hello', 'world'];
a.push('!'); // returns ['Hello', 'world', '!']
```

# `.slice()`
Returns a new array
```js
const animals = ['pigs', 'goats', 'sheep'];
const a = animals.slice(1, 3); // a = ['goats', 'sheep']
const b = animals.slice(-1); // b = ['sheep']
```

# `.pop()`
Removes and returns the last element of an array

# `Array.prototype.reduce(callback, initialValue)`

For each value in an array, perform the `callback` function and use the result for the next value in the array. For the first iteration use `initialValue`

```js
const array = [1, 2, 3, 4];
const initialValue = 0;
const sumWithInitial = array1.reduce(
// accumulator is the result of the previous iteration
  (accumulator, currentElement) => accumulator + currentElement,
  initialValue,
);
```

We can rewrite the above as:
```js
const array = [1, 2, 3, 4];
const initialValue = 0;

const sum = (accumulator, currentElement) => {
    console.log(accumulator);
    console.log(currentElement);
    console.log();
    return accumulator + currentElement;
}

// sumWithInitial is 1 + 2 + 3 + 4, and equals 10
const sumWithInitial = array1.reduce(sum, initialValue);
```


# Object destcruction
```js
const func = (acc, {rating}) => {
	return acc + rating;
}
```
is equivalent to writing
```js
const func = (acc, review) => {
	const rating = review.rating;
	return acc + rating;
}
```