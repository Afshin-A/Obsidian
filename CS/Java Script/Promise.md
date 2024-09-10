A promise objects encapsulates an asynchronous process, its completion status (pending, fulfilled, rejected), and how to handle each completion scenario.
```js
const executor = (resolve, reject) => {
	    let success = true; // Simulate success or failure
	    if (success) {
	        resolve("Operation successful!");
	    } else {
	        reject("Operation failed!");
	    }
	};
const myPromise = new Promise(executor);
```

In the example above, a `Promise` object is declared with two functions as arguments. Some operation is done asynchronously (meaning it is done in a separate thread, and the result is returned to the main thread) and the result is stored in `success`. If successful, `resolve` is called, if not `reject` is called. 

How to instantiate a Promise object
```js
// Handling the promise
myPromise
	// if operation is sucessful, the result is passed to the `result` variable, which is then used inside `console.log`
    .then(result => {
        console.log(result); // Logs "Operation successful!" if successful
    })
    .catch(error => {
        console.error(error); // Logs "Operation failed!" if rejected
    });
```

```js
someAsyncFunction()
    .then(response => {
        console.log(response);
    })
    .catch(error => {
        console.error(error);
    });
```
# async/wait

```js
const fetchData = async () => {
    try {
        const response = await someAsyncFunction(); // Wait for the promise to resolve
        console.log(response); // Continue with the resolved value
    } catch (error) {
        console.error(error); // Handle any errors
    }
};

// Assuming someAsyncFunction is defined elsewhere and returns a promise
fetchData();
```

`await` waits until the promise returned by `someAsyncFunction()` is resolved. If no problems, it will execute `console.log()`. If not, it will throw an error which is caught by the `catch` statement.


# Example
## Directly using promises
```js
const travel = async function(req, res, next) {
	// await means wait for the fetch function to complete and return a promise. It is part of the syntax
    await fetch(tripsEndpoint, options) // returns a promise. results are passed to the next .then() in the chain as `res`
        .then(res => res.json()) // returns a promise
        // if successful, the argument function inside `.then()` is executed, and the results are passed to the next .then() as `json`
        .then(json => // returns a promise
        // `json` variable is used in the rendering of the view
            res.render('travel', { title: 'Travlr Getaways', trips: json })
        )
        // if any promises in the chain fail, an error is thrown and caught here
        .catch(err => res.status(500).send(err.message));
};
```
The following snippet is equivalent to the one above:
```js
const travel = async function(req, res, next) {
    try {
        const response = await fetch(tripsEndpoint, options);
        const json = await response.json();
        res.render('travel', { title: 'Travlr Getaways', trips: json });
    } catch (err) {
        res.status(500).send(err.message);
    }
};

```
