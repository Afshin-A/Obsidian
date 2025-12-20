# Typescript/JavaScript Notes
In typescript, the `!:` syntax is a way of assuring the compiler a value *won't be undefined*, it will be assigned a value to later, so ignore errors
```typescript
name!: string
```
## Difference between `var` and `let`
In short, `var` is the modern version of `let`. 
### 1. Hoisting
- `var` creates a variable and initializes it to `undefined`, even if the user does not explicitly set a variable.
- `let` does not initialize a variable. 
- Both hoist the variable to the top of their scope. This means that if you attempt to access a `let` variable before initialization, you will get a `ReferenceError` while `var` will not cause an error.
### 2. Scopes
- `var` is function scoped, just like a normal variable in other languages.
- `let` is block scoped. 
```ts
function letExample() {
	let y = 1;
	if (true) {
		let y = 2; // This is a new variable
	}
}
```
### 3. Redeclaration
With `let`, you cannot redeclare the same variable, where as you can with `var`
```ts
let a = 1;
let a = 2; // error 
```

### `const`
In terms of hoisting, `const` works like `let`.

# Installing Angular
First install Angular CLI using npm package manager:
```shell
npm install -g @angular/cli
```
It's best to install it globally to avoid confusing `node_modules` in every directory of your project.
# Commands
- `ng serve` — for testing, automatically refreshes changes
- `ng build` — for production
- `ng generate component new-component-name`
	- `ng g c` for short
- `ng new project-name --no-standalone` - create a new project

In addition, you can build or serve angular using npm. Check the `scripts` property inside `package.json`. It should look something like this:
```json
  "scripts": {
    "ng": "ng",
    "start": "ng serve",
    "build": "ng build",
    "watch": "ng build --watch --configuration development",
    "test": "ng test"
  },
```

# Traditional Angular Vs. Standalone
While the majority of this guide has the non-standalone (traditional/modular) format, you should know there is very little difference in syntax on the surface. Behind the scenes, however, standalone applications, especially for small apps, are faster. For larger apps, modules should be used, however. 

Refer to [[portal-woh journal#Angular Traditional vs. Standalone|this journal entry]] for more information.

Basically, groups related of components, directives, pipes, etc. are declared in the scope of a module. When we want to use one component, we have to import the module, which imports everything else in the module too.

Standalone means that components, directives, pipes, etc. can exist on their own. They define their own dependencies 
# Modules
Modules group together components, services, etc.. to be compiled together as a unit. If you want to use a component within an external component, you have to import its module. 
```ts
import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from './app-component';
// Just like in python, this decorator is adding functionality to the Module class 
// This is the main module
@NgModule({
	declarations: [AppComponent],
	imports: [BrowserModule],
	// defines the entry point into the application
	bootstrap: [AppComponent] // entry point into the application
})
export class AppModule { } // export the module
```
# Components
The building blocks of Angular applications.
```ts
import { Component } from '@angular/core'
@Component({
	selector: 'app-root',
	templateURL: './app-component.html',
	styleUrls: ['./app.component.css']
})
export class AppComponent {
	title = 'app title';
}
```


Components are rendered via their selector tags. 
`index.html`
```html
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>Loc8rPublic</title>
</head>
<body>
  <app-root></app-root>
</body>
</html>
```

Trivia:
- Components are consumers of services
- In traditional Angular, component must be in a module before it can be used in another component.
- **Modern Angular does not require modules. Components can be standalone, meaning they manage their own imports and exports.**
- Component tags  can be used  in all other components in the same module
# Life Cycle Hooks
Sometimes we want to run some code when a component is created (e.g. opening a connection to the database to fetch some data) or when it is destroyed (unsubscribing from observers, etc..). We can use **life cycle hooks** to accomplish that: code that specifically runs during a certain life-cycle event of a component or directive. Examples include: `ngOnInit`, `onOnDestroy`, or and `ngOnChanges`.

# Text interpolation
It is the ability to pass dynamic variables from the typescript sub-component to the html part as text. 
```html
<h1>Welcome to {{title}}</h1>
<!-- This is possible, but we should keep logic in the typescript -->
{{1+2}}
```

However, text interpolation is slowly getting phased out. The recommended way is to use **signals**:
```ts
@Component(
	selector: 'home-component,
	standalone: true,
	imports: [],
	template: '''
		<h1>{{title()}}</h1>
	'''
	styleUrl: './home-component.css'
)
export class HomeComponent {
	title = signal('Welcome to my app');
}
```
# Child-Parent Component Relationship 
Components follow a hierarchy. At the very top, you have the main application component; it usually goes by the `app-root` tags. Everything in the app is embedded within this component.

As an analogy, you can think of a remote controller. The body of the remote is the parent that processes information passed to it from its children, the buttons. When you press button, a signal is sent from the child to the parent. The parent then takes some action. 

Passing information from child to parent, vice versa, and even both ways, can be done in several ways.
## Declarative binding using `@Output` decorator / Event binding
This is the most common way you can send data from a child component to its parent with an `EventEmitter`
The output binding is always an instance of the **`EventEmitter`** class.   

When the click event is detected for the button, the function `sendMessage()` gets called. 
`@Output()` is used to mark a class property available for event binding in the parent component's template. 
`EventEmitter` is an extension of the `Subject` class from `RxJS`, used specifically in Angular along side the `Output` decorator to pass data from a child component to the parent component.
```ts
import {Component, Output, EventEmitter } from '@angular/core';
@Component({
	selector: 'app-child',
	template: `<button (click)="sendMessage()">Send message</button>`,
	style: ''
})
export class ChildComponent implements {
	constructor() { }
	@Output() messageEvent = new EventEmitter<string>();
	sendMessage() {
		this.messageEvent.emit('New message from child!');
	}
}
```
In the child component's template, clicking the button triggers the `click` event, which in turn calls the `sendMessage` function. This function triggers an event of its own.
Incoming `click` event from the DOM triggers the `sendMessage` function in this component.
```ts
import { Component } from '@angular/core';
@Component({
	selector: 'app-parent',
	template: `
		<app-child (messageEvent) = "receiveMessage($event)"></app-child>	
		<p>Message from child: {{ message }}</p>
		`
})
export class ParentComponent {
	message: string = '';
	receiveMessage(message: string) {
		this.message = message;
	}
}
```
Incoming `messageEvent` from the child component triggers the `receiveMessage` function in this (i.e. the parent) component. The data passed along with the event can be captured via `$event`, which is passed to the `receiveMessage` function.

What we're doing here is also called **event binding**. We're binding events to function calls. 
The syntax is the same across both examples for the child and the parent components:
```ts
<tag (someEvent)="function($event)" />
```
Read it like this: `someEvent` relevant to `tag` is triggered, and it calls `function` to be called. The data from the event is referenced as `$event`, and it's passed to the `function`

### Why is it called declarative binding?
Declarative programming is about abstraction. We tell Angular *what* we want, and the framework will work its low level magic.
Imperative programming focuses on *how* it's some. We have to define every minute detail ourselves. 
<iframe width="560" height="315" src="https://www.youtube.com/embed/oesGIySeFsM?si=V3goEg9uD_9_79xX" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
### Template statements
The function that responds to an event call.  In the example above, `sendMessage()` is a template statement.
Statements have their own context, which is usually within the scope of the component class (everything the `this` keyword can access). As such, we cannot access the global namespace and use variables like `document`, `window`, and others, in the statements.
For example, we cannot have something like `<app-child (click) = "document.querySelector('div').style.color = 'blue'"></app-child>`
Angular strives to avoid directly manipulating the DOM. For that, we either use declarative bindings or component logic. However, you can access `document` or `window` in the typescript file of the component
## Declarative binding using `@Input` decorator
This is used to pass data from parent to the child component.
```ts
// child-component.ts
import { Component, Input } from '@angular/core';
@Component({
	selector: 'app-child',
	template: 'say {{ message }}',
})
export class ChildComponent {
	@Input message: string;
}

// parent-component.ts
import { Component } from '@angular/core';
@Component({
	selector: 'app-parent',
	template: '<app-child [message]="userInput"></app-child>',
	style: ''
})
export class ParentComponent { 
	const userInput = "Hello from parent!";
}
```
This is also referred to as property binding. The parent component is setting `message` property of the child component.
## `@ViewChild`
With this decorator, a parent component can query and gain programmatic access to a single child component, directive, or a plain HTML element within its template.

```ts
@Component({
	selector: 'app-child',
	template: '',
	style: ''
})
export class ChildComponent {
	message = 'message from child';
}
```

```ts
import { Component, ViewChild, AfterViewInit } from '@angular/core';
import { ChildComponent } from ...
@Component({
	selector: 'parent-child',
	template: '',
	style: ''
})
export class ParentComponent implements AfterViewInit {
	@ViewChild(ChildComponent) child;
	ngAfterViewInit() {
		console.log(this.child.message);
		this.child.message;
	}
}
```
The child can only be accessed after the view has been initialized. Therefore, we must use the `ngAfterViewInit` life-cycle hook, as shown above.


# Component Styling
There are 4 ways to apply styling to a component.
```
1 - styles: ['h2 color: red']
2 - styleUrls: [./child.component.css]

3 - <link rel="stylesheet" href=''></link>
4 - <style></style> 
```

```css
:host {
	display: block;
}
:host(.active) {
	border: 1px solid green;
}
:host-contect(.theme-light) h2 {
	background-color: blue;
}
```

# Content Projection
It's a way to project, basically duplicate, elements from the parent into the child component. It allows for reusability without changing the child's code
This is done using the `<ng-content>` tag, a placeholder. in the child. The parent component's html code will be *projected* to where ever the `ng-content` tag is placed in the child component.

It is also possible to have multiple projections. Use the select attribute for the ng-content tag.
```html
<ng-content select=".header"></ng-content> <!-- Projects content with class="header" -->
<ng-content select=".body"></ng-content>
```
# Pipes
Pipes are functions used for manipulating data format. These can be chained
```ts
{{ todaysDate | date : short | uppsercase}}
```
`date` and `uppercase` are built in pipes. the syntax `:` is used to define options for the pipe.

We can create custom pipes
```
ng g p pipe-name
```
[Here's a list of other common, built in angular pipes](https://angular.dev/guide/templates/pipes#built-in-pipes)



# HTML Attributes Vs. DOM properties
- HTML attributes are static. e.g. id, class, value, disabled, type, aria-label
- DOM properties are dynamic and are generated when the browser generates the DOM from the HTML code. e.g.value, disabled, className, style, checked.
- The browser parses the HTML code and generates a live, dynamic version of the page as a tree (data structure).  
- Not every attribute have a corresponding property, and they're not always in sync. i.e. a change in property doesn't necessarily mean the attribute is also updated.

DOM properties control the live state of a webpage, while the HTML attributes are static. <u>So in general, we should not change attributes, we should change properties</u>

# Property binding
This is a data binding mechanism that allows for passing data from the component to the view template.
We've also seen it in [[Angular#Declarative binding using `@Input` decorator]], where the parent component, from its template, sets a property of the child component. 

There are different types of property binding, as we'll see in the next sub sections. 
They all use the same syntax:
```html
<component [property]="variable" />
```
Read the syntax like this: some `property` of `component` is set to equal `variable`. 
`variable` is defined in the typescript file of the parent component


```ts
@Component({
  selector: 'app-my-component',
  template: `
    <input [value]="inputText" (input)="updateText($event)">
    <p>Current value: {{ inputText }}</p>
  `
})
export class MyComponent {
  inputText = 'Hello, Angular!';
  
  updateText(event: Event) {
    this.inputText = (event.target as HTMLInputElement).value;
  }
}
```
In a component, we can set the property of an html element dynamically using typescript.
Warning: Do not use text interpolation to set an element's attribute:
```html
// BAD!!!
<input value="{{ inputText }}">
```


### Attribute Binding
Some HTML attributes don't have a corresponding DOM property. Or, sometimes we just want to manipulate HTML attributes directly and dynamically. In this case, we can do something like this:
```typescript
@Component({
  selector: 'app-my-component',
  template: `
    <div [attr.data-test]="testId">Content</div>
    <button (click)="updateId()">Update ID</button>
  `
})
export class MyComponent {
  testId = 'test-123';
  // Updates the data-test attribute
  updateId() {
    this.testId = 'test-456';
  }
}
```
### CSS Class Binding
Dynamically add or remove CSS classes on an element. You can use this to add a single CSS class, or multiple ones to an element:
```
single class:
<element [class.class-name]="booleanExpression"></element>

multiple class:
<element [ngClass]="classObj"></element>
<element [ngClass]="{ class1: true, class2: false }"
```

```typescript
// my-component.component.ts
import { Component } from '@angular/core';

@Component({
  selector: 'app-my-component',
  template: `
    <div [ngClass]="stylesObj">Content</div>
    <button (click)="toggleClasses()">Toggle Classes</button>
  `,
  styles: [`
    .active { background-color: yellow; }
    .bordered { border: 2px solid blue; }
  `]
})
export class MyComponent {
  // CSS styles defined in an object
  stylesObj = { active: true, bordered: false };
  // template statement 
  toggleStyleClass() {
    this.stylesObj = { active: !this.classObj.active, bordered: !this.classObj.bordered };
  }
}
```
### Style Binding
this lets you dynamically add or change a style of an element

Example 1:
```typescript 
@Component({
  selector: 'app-my-component',
  template: `
    <div [style.backgroundColor]="bgColor">Content</div>
    <button (click)="changeColor()">Click to change background Color</button>
  `
})```

Example 2:
```typescript
@Component({
  selector: 'app-my-component',
  template: `
    <div [ngStyle]="styleObj">Content</div>
    <button (click)="updateStyles()">Update Styles</button>
  `
})
export class MyComponent {
  styleObj = {
    'background-color': 'lightblue',
    'font-size': '16px',
    'border': '1px solid black'
  };

  updateStyles() {
    this.styleObj = {
      'background-color': 'lightgreen',
      'font-size': '20px',
      'border': '2px dashed red'
    };
  }
}
```


# Two-Way Binding
Two way binding is a shorthand that combines property binding and event binding together
- **property binding** is the data flow *from the component to the view*: we set a property of some element in the view using a variable from the typescript file.
- **event binding** is the data flow *from the view back to the component*. An event called on an element from the view triggers a function from the typescript file to be called. 


```ts
import { Component, Input, Output } from '@angular/core';
@Component({
	selector: 'app-sizer':,
	template: `
		<button (click)=dec()">-</button>
		<button (click)=inc()">+</button>
		<label [style.font-size.px]="size">Currentn font size is: {{ size }}></label>
	`,
})
export class AppSizerComponent {
	@Input() size: number;
	@Output() sizeChange = new EventEmitter<number>();
	decrement() { this.resize(-1); }
	increment() { this.resize(+1); }
	resize(delta: number) { 
		this.size += delta;
		this.sizeChange.emit(this.size);
	}
}

@Component({
	selector: 'app-root':,
	template: `
		<app-sizer [(size)]="fontSizepx"></app-sizer>
		<!-- <app-sizer [size]="fontSizepx" (sizeChange)="fontSizepx"></app-sizer> -->
		<div [style.font-size.px]="fontSizepx">Text</div>
	`,
})
export class AppComponent {
	fontSizepx = 16;
}
```

`<app-sizer [(size)]="fontSizepx"></app-sizer>` is a shorthand way of writing `<app-sizer [size]="fontSizepx" (sizeChange)="fontSizepx"></app-sizer>`

Two way binding combines property binding and event binding together
You'll notice that the event is directly tied to a variable, not a function that changes that variable. You'll also notice the Input variable and Output event follow a naming convention:
```
x
xChange
```

In reality, following this format, Angular will evaluate `(sizeChange)="fontSizepx"` as `(sizeChange)="fontSizepx=$event"`
Recall that `$event` refers to the data passed by the event


When you use `[(size)]="fontSizepx"`, Angular automatically knows to look for an `@Input()` named size and a corresponding `@Output()` named `sizeChange`. The framework uses this naming convention as a convention to create the two-way binding. The two-way binding syntax is simply a shorthand for an `[input]` and an `(output)` pair. This is why, when you define a component with custom two-way binding, *you must adhere to this naming convention.* The name of the `@Output()` property must be the same as the `@Input()` property, with the suffix Change.

## Two way binding via Template variables


# Directives
Directives are classes that capture, add, and/or modify the behavior/state of HTML elements in the DOM.

### Component directives
All components are directives
### Attribute directives
These can be attached (as attributes) to existing html elements to alter their behavior and appearance. 

Built in attribute directives include:
- `NgClass` as seen in [[Angular#Class binding|class binding]]
- `NgStyle` as used in [[Angular#Style binding|style binding]]
- `NgModel` adds two way binding to an HTML form element. More on this [[Angular#Forms|here]].

You can even do something like this when class binding
```html
<div [ngClass]="isSpecial > 'special' : ''">Example</div>
```
#### Custom attribute directives
Convention for naming directives: `highlight.directive.ts`
```typescript
import { Directive, ElementRef, HostListener, Input } from '@angular/core';

@Directive({
  selector: '[appHighlight]'
})
export class HighlightDirective {
  @Input() appHighlight: string = 'yellow'; // Default highlight color

  constructor(private el: ElementRef) {}

  @HostListener('mouseenter') onMouseEnter() {
    this.el.nativeElement.style.backgroundColor = this.appHighlight;
  }
  @HostListener('mouseleave') onMouseLeave() {
    this.el.nativeElement.style.backgroundColor = null;
  }
}
```

```html
<div appHighlight="lightgreen">Hover me!</div>
<div [appHighlight]="'pink'">Hover me with a different color!</div>
```

`el.nativeElement` allows accessing the element in DOM
`ElementRef` is a wrapper around a native element in the view (DOM)
`.nativeElement` gives access to the underlying element
### Structural directives
Can be attached (as attributes) to existing html elements to alter their behavior and appearance. You can dynamically generate elements or straight up remove them from the DOM. They can also be used as standalone html elements.

Examples of built in structural directives are:
- `*ngIf`
- `*ngFor`
- `[ngSwitch]`

If the source list changes in any way, Angular re-creates all corresponding DOM elements. This is the default behavior, which can be inefficient. 
We can overcome this behavior by using the `trackBy` function. It must return a unique identifier for each element in the list. 


Example:
```typescript
import { Component } from '@angular/core';

@Component({
  selector: 'app-my-component',
  template: `
    <div *ngIf="showContent">This is shown conditionally</div>
    <ul>
      <li *ngFor="let item of items">{{ item }}</li>
    </ul>
    <div [ngSwitch]="value">
      <div *ngSwitchCase="1">Value is 1</div>
      <div *ngSwitchDefault>Default case</div>
    </div>
    <button (click)="toggleContent()">Toggle</button>
  `
})
export class MyComponent {
  showContent = true;
  items = ['Apple', 'Banana', 'Orange'];
  value = 1;

  toggleContent() {
    this.showContent = !this.showContent;
  }
}
```
Notes for `*ngFor`
We can get the index of an item as follows:
```html
<div *ngFor="let item of items; let i = index"><{{ i }}- {{ item.name }}</div>
```

Another example of structural directives is the `router-outlet` tag, which we explore in our discussion of [[Angular#Routing|routing]]. However, unlike other attribute directives that attach to existing elements, `router-outlet` used as a standalone HTML element.
```html
<router-outlet></router-outlet>
```
#### Custom structural directive:
```typescript
import { Directive, Input, TemplateRef, ViewContainerRef } from '@angular/core';

@Directive({
  selector: '[appUnless]'
})
export class UnlessDirective {
  constructor(private templateRef: TemplateRef<any>, private vcRef: ViewContainerRef) {}
  @Input() set appUnless(condition: boolean) {
    if (!condition) {
      this.vcRef.createEmbeddedView(this.templateRef); // Show element
    } else {
      this.vcRef.clear(); // Remove element
    }
  }
}
```

```html
<div *appUnless="isHidden">Show this unless isHidden is true</div>
```

`TemplateRef`
	Represents an **embedded template** that can be used to instantiate **embedded views**.

# Injectables (Services)
These are *classes* that represent a *service*. They're decorated with `@Injectable`,
They're used to store data and logic, and they can be injected across several components as a dependency. 
```typescript
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class FontSizeService {
  private fontSize = 16;
  getSize(): number {
    return this.fontSize;
  }
  updateSize(delta: number) {
    this.fontSize += delta;
  }
}
```
#### Angular Dependency Injection System
The `providedIn: 'root'` line registers this service with the **Angular DI (dependency Injection) system**, and makes it available at the root level, so it's available to the entire application as a singleton. This is supposedly the modern way.
*However*, it is possible to define a `providers` array for each module, which defines the dependencies that module has. This is still a valid method.
```ts
@NgModule({
  providers: [MyService] // old-school way
})
export class AppModule {}
```
You can also straight up make a service available inside a component by importing it and using it in the component constructor as follows:
```ts
@Component({...})
export class AppComponent {
 // Boom! Injected!
  constructor(public myService: MyService) {}
}
```
Or, you can list them as a dependency in the component.
```ts
@Component({
	selector: 'app-compoent',
	providers: [MyService]
})
export class AppComponent {
  constructor(public myService: MyService) {}
```

- *Provider*: instructions to the Dependency Injection (DI) system on how to obtain a value for a dependency.
- *Injector*: A level-based container dedicated to managing services: it knows where to find the services, instantiating and managing them in memory, the scope the services are available. 
- *Injector hierarchy*: injectors operate at 3 levels. The component, module, and the root. Some services are only available to a component, while some are available module wide.
# Observables
These are a special type of services in Angular that handle asynchronous and event-driven data streams. Angular uses a JavaScript library named RxJS. 
It works like the following:
An observable emits a stream of data. An observer/subscriber subscribes to the observable and listens in for updates. Multiple components can subscribe to the same observable.
HTTP requests and responses are represented as observables in Angular. These are sent and received one time only. But, observables can also act like containers for promises.

Let's get more familiar with observables by going through an example:
```ts
import { Component, OnInit, OnDestroy } from '@angular/core';
import { Observable, Subscription } from 'rxjs';

@Component({
    selector: 'app-component',
    template: `
        <p>Current value: {{value}}</p>
        <button (click)="startStream()">Start stream</button>
    `
})
export class MyComponent implements OnInit, OnDestroy {
    // assuring typescript this variable will be assigned a value
    value!: number;
    private subscription!: Subscription;
    ngOnInit(): void { }
    // create a new observable 
    startStream() {
        const numberStream = new Observable<number>(
            // observable object takes a lambda function as argument
            (observer) => {
                let count = 0;
                // this setInterval function executes a call back every 1000 ms
                const intervalID = setInterval(() => {
                    // observable emits the next value to the observer
                    observer.next(count++);
                    // stop the iteration when count is greater than 5
                    if (count > 5) {
                        observer.complete();
                        clearInterval(intervalID);
                    }
                }, 1000);
                // when the subscribers unsubscribe, we return a method that contains cleanup logic
                return () => clearInterval(intervalID);
            }
        );
        // now let's subscribe to the observer we just created
        this.subscription = numberStream.subscribe(
            {
                // what happens when observer emits the next value
                next: (val) => this.value = val,
                // when there is an error eg. in streaming
                error: (err) => console.log(err),
                // when the stream is completed/closed
                complete: () => console.log('stream is compelted')
            }
        );
    }
    // when the component is destroyed, we must also unsubscribe from the observable. i.e. close the connection
    ngOnDestroy(): void {
        this.subscription.unsubscribe();
    }
}
```
**It's important end our subscriptions when we're done**, otherwise there will be memory leaks in the application.

As we saw above, observables can take a function as argument, which defines the logic for how/when data should be emitted or the stream should conclude (finish), or throw errors. 
But, often, observables are created without such argument. Instead, they're passed to another function that calls the `next()` function. Observables can go through a pipe, which modifies the value through the use of RxJS operators. 
This example is straight out of the authentication service used for the portal-woh project. It shows an http request in the form of an observable. We use the generic type annotation `<AuthResponse>` to tell the function this is the return type we're expecting. When we subscribe to it, data that comes through moves through the pipe. The `tap` operator extracts the `accessToken` property and uses it as argument for aother function calls `setAccessToken`.
```ts
interface AuthResponse = { accessToken: string } ;
// each operator returns a new observable, which is passed to the next operator in the pipe
http.post<AuthResponse>('/api/auth/login', credentials).pipe(
      tap(res => this.setAccessToken(res.accessToken)),
      // if an operator fails, we jump to the catchError operator
      catchError(err => {
        this.logout();
        return throwError(() => err);
      })
    );
```

## Cold vs Hot Observables
A **cold observable** starts emitting data when at least one observer subscribes to it. The `Observable` class in RxJs is the standard way of using this type of observable
Every subscriber gets their own data created by a separate process. In other words, a process gets created just for you, and you start receiving data from then on. 
Cold observables are used for fresh and independent data for every subscriber. For example, HTTP requests (GET, POST), are cold observables. For example, different users want to query the database to retrieve their own data. Every request is distinct, the query data is different, because every user has their own data. 

`Observable` objects are read-only. ==Outside sources cannot call `.next()` on an observable==. It is the observable itself that internally calls the `.next()` method to emit the data. To put it another way, observables push data to observers. Observers cannot push data into the stream inside the observable.

A **hot observable** emits values regardless of whether it has any subscribers or not. In RxJs, `Subject` is the standard way to use this of observables.
When an observer subscribes, they start receiving values from that point onward. Any values emitted beforehand are missed. But, there are special types of hot observables that can change this behavior: 
- `BehaviorSubject`: It takes in an initial value. It stores the last emission, and when a new observer subscribes, they will receive the last emitted value.
- `ReplaySubject`: This works just like `BehaviorSubject`, but you can customize it to return more than just the last emitted value. You can return the last 2, 3, and so on.
The observable keeps a registry of all its subscribers; It emits the same data (that is created by 1 process) to all of them. 
Hot observables are great when data needs to be shared. For example, suppose we have an `AuthService` that gets the JWT for the user from the backend server. JWT contains user info like `userId`, which other services might need to query the database. The solution is that we use a `BehaviorSubject` to share the last JWT value with the components and services that need it. 

`Subject` is both an observable and an observer. It's an observable in the sense that it pushes data to its subscribers. It's an observable in the sense that it can get receive data as well. In other words, outside sources can call the `.next()` method on it. 
### Caching Using Observables
In addition to emitting data, observables can also be used to cache data. We already discussed how `BehaviorSubject` and `ReplaySubject` (AKA a hot observables) stores or *caches* the the last emitted value. But that's not exclusive to hot observables. HTTP requests (AKA cold observables) can be made to mimic the hot observable behavior with the `shareReplay()` operator.
```ts
private users$ = this.http.get('/api/users').pipe(
 shareReplay({ bufferSize: 1, refCount: true }) 
 );
```
 `bufferSize: 1` caches the last value and shares the single HTTP call.
`refCount: true` ensures the API call is cancelled (unsubscribed from) if the subscriber count drops to zero, freeing up resources. // The cache is also cleared, so the next subscriber will re-run the request. 
Do not confuse `replay()` with `shareReplay()`. They're both operators used in observable pipes. However, with `replay()`, data is not shared between the subscribers/observers (these two mean the same thing in this context). In other words, every subscription will cause a separate thread to run and get new data. That is not ideal for HTTP requests. 

### `ReplaySubject` vs `observable.pipe(shareReplay())`
# Routing
Looking inside `index.html`, you'll notice the line `<base href="/">` in the head.
This assumes the app folder is the application route and uses `/` **(?)**

The entire application is a single page `index.html`, hence the name single page application. 
```html
<router-outlet></router-outlet>
```
Angular dynamically updates the DOM by loading in the component the user wanted to see. The HTML5 history API keeps track of the history, making it seem as if a new html file was opened to.   

First, we define the `AppRoutingModule` where we define the routes.

`app-routing.module.ts`
```typescript
import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { HomeComponent } from './home/home.component';
import { AboutComponent } from './about/about.component';
import { NotFoundComponent } from './not-found/not-found.component';

// List of type Routes storing the route to component relationship 
const routes: Routes = [
  { path: '', component: HomeComponent }, // Default/home route
  { path: 'about', component: AboutComponent },
  { path: '**', component: NotFoundComponent } // Wildcard for 404
];

@NgModule({
  // This function is used once only in the root module. It sets up the routes, the router service and essential directives, for the entire application. 
  imports: [RouterModule.forRoot(routes)], 
  exports: [RouterModule]
})
export class AppRoutingModule {}
```

We then import this module into the main application module 
`app.module.ts`
```typescript
import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { HomeComponent } from './home/home.component';
import { AboutComponent } from './about/about.component';
import { NotFoundComponent } from './not-found/not-found.component';

@NgModule({
  declarations: [AppComponent, HomeComponent, AboutComponent, NotFoundComponent],
  imports: [BrowserModule, AppRoutingModule],
  bootstrap: [AppComponent]
})
export class AppModule {}
```
The `declarations` property registers components, directives, etc in this module. When we declare these components in the root application module, Angular compiles them and makes them available application wide.
Services are listed in the `providers` property.


Finally, we need to place the `<router-outlet></router-outle>t` directive tags in the main application component to render whatever component the user clicks the link for
```typescript
// app.component.ts
import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  template: `
    <nav>
      <a routerLink="">Home</a> | <a routerLink="/about">About</a>
    </nav>
    <router-outlet></router-outlet> <!-- New: RouterOutlet directive -->
  `
})
export class AppComponent {}
```

## Dynamic Routing using Observables
We need a few classes to achieve this:
- `ActivatedRoute` is a service that provides information about the current route. It is injected into the component via its constructor.
- `ParamMap` is an object storing key-value pairs related to the current URL. We can use it to extract information
- `paramMap` is a property of `ActivatedRoute`. It returns an observable, which we use to keep track of when there are changes to the `ParamMap` object 
- `Router` is a service we can use to programmatically direct users to a different URL

Consider the following scenario. Suppose we have a store front for some products. When the user enters a URL with a product ID, we can use an observable to detect changes to the URL, we can extract the product ID, which we can then use to query the database via an API and display appropriate information on the page.

Suppose in our `app-routing.module.ts` we have the following:
```ts
const routes: Routes: [
	{path: 'product/:id', component: ProductComponent}
]
```
We use `:` to signify a dynamic component to Angular

The product component might look something like this:
```typescript
// product.component.ts
import { Component, OnInit, OnDestroy } from '@angular/core';
import { ActivatedRoute, ParamMap } from '@angular/router'; 
import { Subscription } from 'rxjs';

@Component({
  selector: 'app-product',
  template: `
    <h2>Product ID: {{ productId }}</h2>
    <button (click)="goBack()">Back</button>
  `
})
export class ProductComponent implements OnInit, OnDestroy {
  productId: string;
  private subscription: Subscription;
  // inject services via constructor
  constructor(private route: ActivatedRoute, private router: Router) {}
  ngOnInit() {
    // Subscribe to route parameters observable
    this.subscription = this.route.paramMap.subscribe((params: ParamMap) => { 
    this.productId = params.get('id'); });
  }
  goBack() { this.router.navigate(['/']); }
  ngOnDestroy() { this.subscription.unsubscribe(); }
}
```

We can improve performance with *lazy-loading*, loading components and their associated services only when the user navigates to those components. This way, loading the entire application at the start, thus avoiding a delay. 

The main routing module will dynamically import a *feature* (as in a feature of our application) module and configure all the routes defined in there, only when that module or its subsidiaries are accessed.
```typescript
// products.module.ts
import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterModule, Routes } from '@angular/router'; // RouterModule, Routes
import { ProductListComponent } from './product-list/product-list.component';

const routes: Routes = [
  { path: '', component: ProductListComponent } // Default route for /products
];

@NgModule({
  declarations: [ProductListComponent],
  imports: [
    CommonModule, // light weight version of BrowserModule, it provides common directives like ngIf, ngFor
    RouterModule.forChild(routes) // New: Configures child routes
  ]
})
export class ProductsModule {}
```
A couple of notes:
- Previously, we used the `RouterModule.forRoot`, which configures routes for the entire application. 
- Here, we're using `RouterModule.forChild`. It configures the routes for the components in this module, but they're not added to the global router yet. Because we are lazy-loading this module, we want the components in this module to be registered only after the module is loaded.  
- We typically need to import the `BrowserModule` in to the main module. It is essential for all apps to be able to be rendered in a browser. The `CommonModule` is a lightweight module that provides common directives like `ngFor` and `ngIf` that we might need in this feature module.

Then, in our main routing module, we define `routes` as follows:
```typescript
const routes: Routes = [
  { path: '', component: HomeComponent },
  {
    path: 'products',
    loadChildren: () => import('./products/products.module').then(m => m.ProductsModule) // New: loadChildren
  },
  { path: '**', component: NotFoundComponent }
];
```

The `import` function returns a promise of the module, which then gets resolved to the module upon success. This will then make all the components in the module and their routes available. The components, directives, etc. of this feature module are not available when the app is first loaded. The browser downloads the source code only when the user navigates to a child component. 

**This can be used strategically to lazy load modules we think are less likely to be used by the user.** 

## Using Query Parameters 
We can use these for sorting, filtering, pagination, or passing settings like the language a webpage should be displayed in. They should not be used to pass sensitive information 
Getting query parameters is done similarly to a dynamic link.
Suppose we have the following template:
```typescript
// app.component.ts
import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  template: `
      <a routerLink="/products" [queryParams]="{ category: 'electronics', sort: 'price' }">
        Electronics (Sorted by Price)
      </a>
    <router-outlet></router-outlet>
  `
})
export class AppComponent {}
```
Clicking on that link would produce `/products?category=electronics&sort=price`
In our product component, we can extract the query parameters like this:
```typescript
// products.component.ts
import { Component, OnInit, OnDestroy } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Subscription } from 'rxjs';

@Component({
  selector: 'app-products',
  template: `
    <h2>Products</h2>
    <p>Category: {{ category }}</p>
    <p>Sort: {{ sort }}</p>
  `
})
export class ProductsComponent implements OnInit, OnDestroy {
  category: string;
  sort: string;
  private subscription: Subscription;

  constructor(private route: ActivatedRoute) {}

  ngOnInit() {
    this.subscription = this.route.queryParams.subscribe(params => {
      this.category = params['category'] || 'all'; // Default value
      this.sort = params['sort'] || 'default';
    });
  }

  ngOnDestroy() {
    this.subscription.unsubscribe();
  }
}
```

We can also insert query parameters into the URL as follows:

suppose the user clicks a button that sorts a table by title:
```typescript
// products.component.ts
import { Component } from '@angular/core';
import { Router, ActivatedRoute } from '@angular/router';

@Component({
  selector: 'app-products',
  template: `<button (click)="filterByBooks()">Filter Books</button>`
})
export class ProductsComponent {
  constructor(private router: Router, private route: ActivatedRoute) {}
  filterByBooks() {
    this.router.navigate(['/products'], {
      queryParams: { category: 'books', sort: 'title' } // New: queryParams option
    });
  }
}
```

## Configuring Router in Standalone Apps
Standalone apps don't have a main module or a router module. Everything more or less works around single, standalone typescript files.
The `Routes` object is defined in a file named `app.routes.ts` at the root level of the application (folder wise).
At the same level, a file named `app.config.ts` lists all the providers for the application. In there, we have `provideRouter(routes)`, which sets up all the necessary routing services using the `routes`. 
Finally, the application started via the `bootstrapApplication(App, appConfig)` function call. `App` is the main component (`app-root`) and `appConfig` is the root-level configuration for the application. 

# Forms
### Template forms
As the name suggests, these are defined in the html template using directives and minimal typescript code. Even form validation is done in the template using HTML5 features.
Directives, such as `ngForm` and `ngModel`, are responsible for managing the form. These are enabled when we import `FormsModule`.
```typescript
// app.module.ts
import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { FormsModule } from '@angular/forms'; 
import { AppComponent } from './app.component';

@NgModule({
  declarations: [AppComponent],
  imports: [BrowserModule, FormsModule],
  bootstrap: [AppComponent]
})
export class AppModule {}
```
We also need a *data model* to store information from the form:
```typescript
user = { name: '', email: '' };
```

```html
    <form #userForm="ngForm" (ngSubmit)="onSubmit()"> <!-- New: ngForm, ngSubmit -->
      <div>
        <label for="name">Name:</label>
        <input type="text" id="name" name="name" [(ngModel)]="user.name" required #nameControl="ngModel">
	    <span *ngIf="nameControl.invalid && nameControl.touched">Name is required</span>
      </div>
      <div>
        <label for="email">Email: </label>
        <input type="email" id="email" name="email" [(ngModel)]="user.email" required email>
      </div>
      <button type="submit" [disabled]="!userForm.valid">Submit</button>
    </form>
    <p *ngIf="submitted">Submitted: {{ user | json }}</p>
```
The `NgForm` directive is automatically applied to any `<form>` element in an Angular template as soon as we import the `FormsModule` or `ReactiveFormsModule`, so that we don't need to manually import `NgForm`.

The line `#userForm="ngForm"` gives the `ngForm` instance of this form a variable name. 
 This is called a *template variable*. We can use this variable to extract information about the form, such as checking if it's valid or been submitted and such. Remember that directives are classes. Every form gets their own instance of the `ngForm` directive.
 
 Similarly, every input also gets their own instance of the `ngModel` directive, which is responsible for establishing a two way connection between the `value` attribute of an `input` html element, and a corresponding variable in the typescript class. Behind the scenes, this directive handles event calls and the state of the input element. We can assign a *template variable* to the instance of the `ngModel` directive for this `input` element like this: `#nameControl="ngModel"`. Then, we can use this variable to check, for example, if the input has been touched or if it's valid: `*ngIf="nameControl.invalid && nameControl.touched"`


```html
<input [(ngModel)]="user.name" #nameControl="ngModel">
```
`nameControl` is a template variable. It refers to the instance of the `ngModel` directive created for this `<input>` element.

The directive `ngModel` when used `[(ngModel)]="user.name"` establishes a two way connection. Changes to `user.name` are reflected in the `value` field of `input`, and the `input` event pushes the `value` of the field into `user.name`. 
### Reactive forms
[[Angular#Template forms|Template forms]] are limited. So for more complex forms, we turn to *reactive forms*, which are scalable and can be tested more easily.
To use this type of forms, we need import the `ReactiveFormsModule` module; we use observables to update and validate forms
Three classes, `FormGroup`, `FormControl`, and `FormArray`, are used to define a form model, which is bound to the template using the `formGroup` and `formControl` directives.

- `FormControl` represents a single field, i.e. its state, including value and validation.
- `FormGroup` represents a section consisting of `FormControl` and even other `FormGroup` fields. 
- `ValueChanges` is an observable type that keeps track of changes to a `FormControl` or `FormGroup`.
- `FormArray` is an array of...
- `formControlName` directive 


First we define a form model using the `FormGroup` class:
```typescript
userForm: FormGroup
```
We then define `FormControl` elements with validators for the group
```typescript
ngOnInit() {
    this.userForm = new FormGroup({
      name: new FormControl('', Validators.required),
      email: new FormControl('', [Validators.required, Validators.email]) 
    });
  }
```
Using directives, we can bind these to the HTML elements in our template:
```html
<form [formGroup]="userForm" (ngSubmit)="onSubmit()">
      <div>
        <label for="name">Name:</label> 
        <!-- standard html, makes it so that users can select the input by clicking on the label. the for attribute connects the label to the input that has the id "name"-->
        <input
          type="text"
          id="name"
          formControlName="name">
          <!-- formControlName directive connects this input to the name FormControl element defined in this -->
          
      <button type="submit" [disabled]="!userForm.valid">Submit</button>
</form>
    <p *ngIf="submitted">Submitted: {{ userForm.value | json }}</p>
```


We might not know the input fields in our form. With `FormArray`, we can dynamically populate an array with `FormControl` or `FormGroup` objects. 
There's also a variety of validators, including custom validators

These seem simple and I've decided to learn these as I come across them in my project.


# Refresher

Databinding, passing data from parent to child

```ts
@Component(
	selector: 'parent-component'
	imports: [ChildComponent],
	template: `
		<child-component [paragraph]="'message()'"></child-component>
	`,
	styleUrl: './parent-style.css'
)
export class ParentComponent {
	const message = signal('Hello world!');
}

@Component(
	selector: 'child-component',
	imports: [],
	template: `
		<p>{{paragraph()}}</p>
		<!-- <p>{{paragraph}}</p> -->
	`,
	styleUrl
)
export class ChildComponent {
	paragraph = input();
	// @input paragraph: string;
}
```

```ts
@Component(
	selector: 'counting-component',
	imports: [],
	template: `
		<p>Current value: {{value()}}</p>
		<button (click)="'increment()'">Increment</button>
		<button (click)="'reset()'">Reset</button>
		<button (click)="'decrement()'">Decrement</button>
	`,
	style: ``
)
export class CountingComponent {
	this.value = signal(0);
	
	increment() {
		this.value.update((val) => val + 1);
		// this.value.set(this.val.get() + 1);
	}
	decrement() {
		this.value.update((val) => val - 1);
	}
	reset() {
		this.value.set(0);
	}
}
```

# Constructor Vs. `ngOnInit`
The constructor initializes local variables, including service instances. It instantiates the component class. After that is complete, `ngOnInit` lifecycle hook runs once after angular has finished setting up `@input` properties. Otherwise, the `@input` variable will be `undefined`

