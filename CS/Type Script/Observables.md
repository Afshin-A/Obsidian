Provided by the RxJs library, they're powerful and heavily used in Angular apps.

You have an observable and an observer. Observer subscribes to the observable and receives data. Observable pushes data to the observer/subscriber.

Observables and observers are a data structure. The RxJS library is design pattern for transferring data around around our application. Sometimes data is emitted across the web, and that is when a communication protocol like HTTP or [[Web Sockets]] are used. RxJS itself does not use these; a different part of the application.

An observable can have unlimited observers. Each observer get their own stream of data. I.e. the data streams are independent.


Let's define a simple observable:
```ts
import { Observable } from `rxjs`;

const myObservable$ = new Observable(
	
	observer => { 
		var error: bool = False;
		observer.next(1); // emit the next value
		observer.next(2);
		if (error) { observer.error(); } // throw an error
		observer.complete('success'); // close the data flow
	}
);
```
Observable defines how data is created and sent to the observers. It takes in a lambda function (an observer function). This function takes takes has an observer argument.
Essentially, when we subscribe to an observable, we're passing the observer reference to it.

Now let's define an observer. 
```ts
const myObserver = {
	next: value => console.log(`${value}`),
	error: err => console.log(`${err}`),
	coomplete: msg => console.log(`${err}`)
};
```

Subscribing is as follows:
```ts
myObservable$.subscribe(myObserver);
```


### Operators
An operator is a function that takes in an observable, modifies the data stream, and returns a new observable. Example: `filter()` lets you filter stream data and `map()` lets you map (convert/relate) data. For example, map a page `click` event to the x and y position of where the click happened: 
```ts
const clicks$ = fromEvent(document, 'click'); // creates an observable that emits a click event from the document anytime the user clicks in the page

// creating new observable that emits x and y positions of a click
const position$ = clicks$.pipe(
	// map (i.e. convert) click event to x and y positions
	map(event=>({x:event.clientX, y:event.clientY}))
);

positions$.subscribe(pos => console.log(pos));
```

You can chain multiple operators together using the `.pipe()` method, creating a pipeline that eventually spits out an observable we can subscribe to.

<b><u>Each operator in the pipe returns a new observable</u></b>

Here's a more concrete example. Let's say we have a search bar. We want to detect when the user types something and send an API request.
```ts
import { fromEvent, of } from 'rxjs';
import { debounceTime, pluck, filter, distinctUntilChanged, switchMap } from 'rxjs/operators';


// The full observable pipeline
const searchInput = document.getElementById('search-input');

// create observable that emits a keyup event from the searchInput object from the document whenever the user clicks or types something 
fromEvent(searchInput, 'keyup').pipe(
  debounceTime(300), // we want to wait at least 300 ms in between events to avoid constant API calls
  pluck('target', 'value'), // this operator plucks/extracts data
  filter(text => text.length > 2), // only search when text length is 3 chars long or more
  distinctUntilChanged(), // Only emit when the current value is different than the last. this avoids key presses lile ctrl or shift
  switchMap(query => searchAPI(query)) // 
)
.subscribe(results => {
  console.log('Displaying results:', results);
  // Code to display results to the user
});
```

#### `pluck`
`pluck` works kinda like `map`. It's used to extract data, if your data is an object, you can directly extract a field value:
`pluck(field)`.
You can also look for nested fields: `pluck(target, value)`, which extracts `target.value` from the emitted data

#### `tap`
The tap operator doesn't modify, it takes in the data and performs some actions with it.

#### `switchMap`
`switchMap` maps each source value to a new observable. When a new source value arrives, it unsubscribes from the previous inner observable and switches to the new one, so only the latest inner observable’s emissions are sent downstream.
```ts
const source$ = interval(3000); // emits 0, 1, 2, ... every 3s

const result$ = source$.pipe(
  switchMap(() => interval(1000)) // emits 0, 1, 2 ... every 1s
);

result$.subscribe(x => console.log(x));
```
This example will output:
```sh
0
1
2
0
1
2
0
1
2
...
```
Source fires a value, the inner observable starts emitting values every second. Then the source fires again and the inner observable restarts. 
The `.subscribe` captures the values emitted by the inner observable and prints them in the console.
#### Subjects
Subjects are a type of observables, with two differences:
- Only 1 process emits the same data to all observers. Subjects are called "hot", unlike "cold" observables that use independent processes for different observers.
- Subjects can be used as an observable *AND* an observer.


```ts
import { Subject } from 'rxjs';

const messageBus$ = new Subject();
// Component 1: The Logger
// This function can be called from anywhere in the app to send a message
function logEvent(message) {
  console.log(`Logger is sending: "${message}"`);
  messageBus$.next(message);
}
// Component 2: The Status Indicator
console.log('Status Indicator is ready to receive messages.');
messageBus$.subscribe(
  message => {
    console.log(`Status Indicator received: "${message}"`);
    // In a real app, this would update the UI
  }
);
```

The syntax here is a little different. Subject doesn't need to take in an observer function as argument. You can call the `next` method anywhere on it.

#### `BehaviorSubject`
They're used to manage the state of an application, like enforcing RBAC using JWT.

This is a type of a subject. Just like a subject, it uses the same process to emit the same type of value to all its subscribers. 
You have to initialize it with a value and you have to define what type of values it can take:
```ts
private roleSubject = new BehaviorSubject<string | null>(null);
```
Just like a subject, you can call the next method anywhere.
When an observer subscribes, it will immediately receive the last emitted value.

 `<string | null>` is a generic type parameter. It means our `BehaviorSubject` will only return `string` or `null` objects
# Read only observables
Sometimes observables hold important information that should not be modified. In that case, we can use the `asObservable` method which returns a read only copy  



