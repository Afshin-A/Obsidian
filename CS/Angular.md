# Commands

`ng serve` - for testing, automatically refreshes changes
`ng build` - for production
`ng generate component new-component-name`
`ng new project-name --no-standalone` - create a new project

# Components

```ts
import { Component } from '@angular/core'
@Component({
	selector: 'app-root',
	templateURL: './app-component.html',
	styleUrls: ['./app.component.css']
})
export class AppComponent {
	title = 'app title'
}

import { BrowserModule } from '@angular/platform-browser'
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

`app-component.html`
```html
<!-- This is called text interpolation -->
<h1>Welcome to {{title}}</h1>
<!-- This is possible, but we should keep logic in the typescript -->
{{1+2}}
```

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


components are consumers of services
component must be in a module before it can be used in another component

component tags  can be used  in all other components in the same module

life cycle hooks is code that we can run at a specific life cycle event of a component or directive, for example when they are created `ngOnInit` or when they are destroyed `onOnDestroy`, or when they're changed `ngOnChanges`. as an example, You would use these to fetch some data from a database and delete it to prevent memory leeks

Text interpolation is the ability to pass dynamic variables from the typescript sub-component to the html part as text. 

## Typescript/JavaScript Notes
In typescript, the `!:` syntax is a way of assuring the compiler a value will be assigned a value to and ignore errors:
```typescript
name!: string
```

`let` and `var`
`var` allows 

## Child-Parent Component Relationship
Parent: remote controller
Child: the on/off button
When you press the button, a signal is sent from the child to the parent. The parent then takes some action. 

## Declarative binding using `@Output` decorator
This is the most common way you can send data from a child component to its parent.
```ts
import {Component, OnInit, Output, EventEmitter } from '@angular/core';
@Component({
	selector: 'app-child',
	template: `<button (click)="sendMessage()">Send message</button>`,
	style: ''
})
export class ChildComponent implements OnInit {
	@Output() messageEvent = new EventEmitter<string>();
	sendMessage() {
		this.messageEvent.emit('New message from child!');
	}
	constructor() { }
	ngOnInit(): void { }
}
```

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


This is Angular’s **template binding system** wiring up two TypeScript classes. You can pass variables and events from child to parent and vice versa. In the example above, `messageEvent` from `ChildComponent` is being passed to `receiveMessage` from `ParentComponent.` `$event` carries the data passed to the parent. 

You'll notice a similar pattern in both the child and parent:

`<button (click)="sendMessage()">Send message</button>
`<app-child (messageEvent) = "receiveMessage($event)"></app-child>`

The parenthesis around `click` mean that it is an event. This is Angular’s event binding syntax. `Click` is standard DOM event in browsers that is triggered when a button is clicked. 
Similarly, brackets indicate a class property.

## Declarative binding using `@Input` decorator
This is used to pass data from parent to a child
```ts
import { Component, OnInit, Input } from '@angular/core';

@Component({
	selector: 'app-child',
	template: 'say {{childMessage}}',
	style: ''
})
export class ChildComponent implements OnInit {
	@Input childMessage: string
	constructor() {}
	ngOnInit(): void {}
}

```


```ts
import { Component } from '@angular/core';
@Component({
	selector: 'app-parent',
	template: '<app-child [childMessage]="'Hello from parent'"></app-child>',
	style: ''
})
export class ParentComponent { }
```


## Accessing Child from within Parent using `@ViewChild`

the child can only be accessed after the view has been initialized
```ts
import { Component } from '@angular/core';

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
import { Component, ViewChild } from '@angular/core';
import { ChildComponent } from '../child/child-component';
@Component({
	selector: 'parent-child',
	template: '',
	style: ''
})
export class ParentComponent {
	@ViewChild(ChildComponent) child;
	ngAfterViewInit() {
		console.log(this.child.message);
		this.child.message;
	}
}
```


## Component Styling

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





## Content Projection
It's a way to project content from the parent into the child, basically duplicating elements from the parent into the child. It allows for reusability without changing the child's code

`<ng-content></ng-content>` is a place holder in the child. The parent component's html will be projected where that tag is in the child 

  

It is possible to have multiple projections. Use the select attribute for the ng-content tag.
```html
<ng-content select=".header"></ng-content> <!-- Projects content with class="header" -->
<ng-content select=".body"></ng-content>
```

# Template statements
Method calls for event bindings. Used to route event call to a response method.
We've already seen this in [[Angular#Declarative binding using `@Output` decorator]]
```html
<app-child (messageEvent) = "receiveMessage($event)"></app-child>
```

 One thing to notice is that the context ( what `this` points to) for these template statements is the instance of the component class, and we cannot access the global namespace and use things like `document`, `window`, and others. 
 So you cannot have something like `<app-child (click) = "document.querySelector('div').style.color = 'blue'"></app-child>`

Angular strives to avoid directly manipulating the DOM. For that, we either use declarative bindings or component logic. However, you can access `document` or `window` in the typescript file of the component


## Pipes
Functions for manipulating data format. These can be chained
```
{{ todaysDate | date : short | uppsercase}}
```
`date` and `uppercase` are built in pipes. the syntax `:` is used to define options for the pipe.

We can create custom pipes
```
ng g p pipe-name
```
[Here's a list of other common, built in angular pipes](https://angular.dev/guide/templates/pipes#built-in-pipes)


## Property binding
data binding mechanism that allows for passing data from the component to the view template

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

Do not use text interpolation to set an element's attribute like
```html
<input value="{{ inputText }}">
```
## HTML Attributes Vs. DOM properties

HTML attributes are static. e.g. id, class, value, disabled, type, aria-label

DOM properties are dynamic and are generated upon the browser generating the DOM from the HTML code. e.g.value, disabled, className, style, checked.
Not every attribute have a corresponding property, and they're not always in sync. i.e. a change in property doesn't necessarily mean the attribute is also updated.


DOM properties control the live state of a webpage, while the HTML attributes are static. So **we should not change attributes, we should change properties.** 

## Attribute binding
Some attributes don't have a corresponding DOM property. Or, sometimes we just want to manipulate HTML attributes directly, dynamically. In this case, we can do something like this:
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

  updateId() {
    this.testId = 'test-456'; // Updates the data-test attribute
  }
}
```

## Class binding
dynamically add or remove CSS classes on an element. You can use this to add a single CSS class, or multiple ones to an element:

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
    <div [ngClass]="classObj">Content</div>
    <button (click)="toggleClasses()">Toggle Classes</button>
  `,
  styles: [`
    .active { background-color: yellow; }
    .bordered { border: 2px solid blue; }
  `]
})
export class MyComponent {
  classObj = { active: true, bordered: false };

  toggleClasses() {
    this.classObj = { active: !this.classObj.active, bordered: !this.classObj.bordered };
  }
}
```

## Style binding
this lets you dynamically add or change a style of an element
```typescript
@Component({
  selector: 'app-my-component',
  template: `
    <div [style.backgroundColor]="bgColor">Content</div>
    <button (click)="changeColor()">Change Color</button>
  `
})
```

```typescript

import { Component } from '@angular/core';

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


## Two way binding

Two way binding is a shorthand that combines property binding and event binding together

```ts
import { Component, Input, OnInit } from '@angular/core';
@Component({
	selector: 'app-app-sizer':,
	template: `
		<button (click)=dec()">-</button>
		<button (click)=inc()">+</button>
		<label [style.font-size.px]="size">FontSize: {{size}}></label>
	`,
	style: []
})
export class AppSizerComponent implements OnInit {
	@Input() size: number;
	@Output() sizeChange = new EventEmitter<number>();
	constructor() {}
	ngOnInit(): void {}
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
	style: []
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

In reality, following this format, Angular will evaluate quick `(sizeChange)="fontSizepx"` as `(sizeChange)="fontSizepx=$event"`
recall that `$event` refers to the data passed by the event


## Two way binding via Template variables


## Directives
classes that add additional behavior to elements
built in directive types:
### Component directives
These are just Angular components consisted of view (HTML) and logic (TypeScript)
### Attribute directives
These can be attached (as attributes) to existing html elements to alter their behavior and appearance. 

Built in attribute directives include:
- `NgClass` as seen in [[Angular#Class binding|class binding]]
- `NgStyle` as used in [[Angular#Style binding|style binding]]
- `NgModel` adds two way binding to an HTML form element

You can even do something like this when class binding
```html
<div [ngClass]="isSpecial > 'special' : ''">Example</div>
```

Example of a custom attribute directive:
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
We can get the index of an item as followsL
```
<div *ngFor="let item of items; let i = index"><{{i}}- {{item.name}}</div>
```


How to create a custom structural directive:
```typescript
import { Directive, Input, TemplateRef, ViewContainerRef } from '@angular/core';

@Directive({
  selector: '[appUnless]'
})
export class UnlessDirective {
  @Input() set appUnless(condition: boolean) {
    if (!condition) {
      this.vcRef.createEmbeddedView(this.templateRef); // Show element
    } else {
      this.vcRef.clear(); // Remove element
    }
  }

  constructor(
    private templateRef: TemplateRef<any>,
    private vcRef: ViewContainerRef
  ) {}
}
```

```html
<div *appUnless="isHidden">Show this unless isHidden is true</div>
```

`TemplateRef`
	Represents an **embedded template** that can be used to instantiate **embedded views**.

`router-outlet`, seen in [[Angular#Routing|routing]], is a structural directive.
```html
<router-outlet></router-outlet>
```
It's used as a standalone HTML element, unlike attribute directives that attach to existing elements. 
## Injectables
These are classes marked with the the `@Injectable` decorator, which can be used to store data and logic to be used across several components as a dependency. 

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

The `providedIn: 'root'` line registers this service with the Angular DI (dependency Injection) system, and makes it available at the root level, so it's available to the entire application as a singleton. This is supposedly the modern way.

However, it is possible to define a `providers` array for each module, which defines the dependencies that module has. This is still a valid method.
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
  constructor(public myService: MyService) {}
}
```
Or, you can have:
```ts
@Component({
	selector: 'app-compoent',
	providers: [MyService]
})
export class AppComponent {
  constructor(public myService: MyService) {}
}
```

- Provider: instructions to the Dependency Injection (DI) system on how to obtain a value for a dependency.
- Injector: A level-based container dedicated to managing services: it knows where to find the services, instantiating and managing them in memory, the scope the services are available. 
- Injector hierarchy: injectors operate at 3 levels. The component, module, and the root. Some services are only available to a component, while some are available to a module and everything inside, including 


## Observables
These are a special type of services in Angular that handle asynchronous and event-driven data streams. Angular uses a JavaScript library named RxJS. 
It works like the following:
An observable emits a stream of data. An observer or subscriber subscribes to the observable and listens in for updates. Multiple components can subscribe to the same observable.
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
    value!: number;
    // assuring typescript this variable will be assigned a value
    private subscription!: Subscription;
    ngOnInit(): void { }
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
We need to be careful to end our subscriptions when we're done, otherwise there will be memory leaks in the application.

## Routing
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
  // register the routes
  imports: [RouterModule.forRoot(routes)], // New: forRoot
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


Finally, we need to place the `<router-outle></router-outle>` directive tags in the main application component to render whatever component the user clicks the link for
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

### Dynamic Routing using Observables
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

  constructor(
    // inject services via constructor
    private route: ActivatedRoute,
    private router: Router
  ) {}

  ngOnInit() {
    // Subscribe to route parameters observable
    this.subscription = this.route.paramMap.subscribe((params: ParamMap) => { 
      this.productId = params.get('id'); // New: get method
    });
  }

  goBack() {
    this.router.navigate(['/']); // New: navigate method
  }

  ngOnDestroy() {
    this.subscription.unsubscribe();
  }
}
```

We can improve performance with lazy-loading, loading components and their associated services only when the user navigates to those components. This way, loading the entire application at the start, thus avoiding a delay. 

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
    CommonModule, // New: Provides common directives like ngIf, ngFor
    RouterModule.forChild(routes) // New: Configures child routes
  ]
})
export class ProductsModule {}
```
A couple of notes:
- Previously, we used the `RouterModule.forRoot`, which configures routes for the entire application. Here, we're using `RouterModule.forChild`. It configures and scopes the child routes to this module, not the entire application. We are lazy-loading this module, after all. The child routes will be loaded in when this module is needed. 
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


### Using Query Parameters 
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

## forms
### Template forms
As the name suggests, these are defined in the html template using directives and minimal typescript code. Even form validation is done in the template using HTML5 features.
Directives are enabled when we import `FormsModule` into the module responsible for the component in which we want to create the form:
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
        <input
          type="text"
          id="name"
          name="name"
          [(ngModel)]="user.name"
          required <!-- HTML5 validation -->
          #nameControl="ngModel"
        >
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
Importing the `ngForm` directive automatically assigns it to all `<form>` elements in the template. 
`#userForm` is a template variable
`ngForm` creates an instance that keeps track of the state of the form

```html
<input [(ngModel)]="user.name" #nameControl="ngModel">
```
`nameControl` is a template variable. It refers to the instance of the `ngModel` directive created for this `<input>` element.

### Reactive forms

we need `ReactiveFormsModule` 
we use observables to update and validate forms

`FormGroup`, `FormControl`, and `FormArray` classes are used for defining a form model, which is bound to the template using the `formGroup` and `formControl` directives
template forms are limited. reactive forms are scalable; they're suitable for complex forms, and they can be more easily tested

- `FormControl` represents a single field, i.e. its state, including value and validation
- `FormGroup` represents a section consisting of multiple `FormGroup` fields 
- `ValueChanges` is an observable type that keeps track of changes to a `FormControl` or `FormGroup`
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
<form [formGroup]="userForm" (ngSubmit)="onSubmit()"> <!-- Bind to our  -->
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


