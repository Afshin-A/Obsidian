[[Travl Getaways]]
Basically, you use Express on top of Node.js to send data from the database and an HTML template to the user, who will use Angular to run the JavaScript code locally on the users' computers.

Comparing two JavaScript objects **always** returns **false**.

# Asynchronous
JavaScript (therefore Express) is asynchronous. The code runs in one thread step by step. But whenever an asynchronous function is called, a new thread is created to process that function. The result is sent back to the main application thread. 

# The MEAN Stack 
All are free open source libraries
## MEAN
### Mongo
MongoDB dbms. Read all about [[MongoDB]] here.

### Express
Express is a web application framework with:
- Makes it relatively easy to set up the web server
- sets up a non-blocking directory system for your files 
- templating
- simple routing of URL requests to static files or database
- Node.js is stateless ([[Networking#Stateful Vs. Stateless Architecture|because http is stateless, remember?]]) and doesn't know who you are, so it's hard to create a personalized experience. express takes care of session management
- takes care of sending responses back to clients 
- can use template engines to build HTML response on the server 
- can use URL routing and [[Full Stack Web development using MEAN#MVC patterns|MVC patterns]]

You can have everything (API and main application) in one project, or separate (even on separate servers).

Express is responsible of connecting your application to the database
### Angular

Angular provides the basic structure and functionality that allows your app to be a single-page application. It takes care of:
- routing (changing views without reloading the page)
- data binding (connecting your app's data to the UI)
- components (building blocks of your UI).
- two-way binding: "immediately updates the HTML if the data changes and can update the data if the HTML changes." (OReily). Otherwise, you have to add event listeners and update the "data model" (idk wtf this means exactly). Angular does this automatically 


Angular isn’t only for SPAs; it can also be used to create individual components that add some rich data interactivity to an otherwise static page.

SPA stands for a single page application. It's just one document that updates without the need to be reloaded. So the server doesn't have to keep sending documents. An example is Gmail. The client's computer is running the application locally using some data (template, data from the database, the code to run locally, etc.) sent from the user.

Angular is the face of the application, the layer that makes user interaction possible
It allows the clients' browsers to run some or all of the JS code locally, instead of the traditional way of the server generating all the HTML response. 
### Node.js
Foundation platform of the stack
Not a webserver or language
It has libraries for http, so no need for NGINX or Apache
It's single threaded: fast and efficient with system resources
It is non-blocking and asynchronous

Node.js is very flexible and doesn't specify how things must be done. We can use a framework like Express to take care of common things that need to be repeated, safely.

Parses requests from Angular to Express




## The Logical Flow of the MEAN Stack 
$$\begin{align}
\text{Angular} \leftrightarrows \text{Ex} & \text{press} \leftrightarrows \text{Mongo} \\
& \uparrow \\
\text{No} & \text{de.js}
\end{align}
$$
# MEAN Stack Architectures
The MEAN stack is very versatile and can be used to solve a variety of problems. Here are some common solutions.
## Single Page Application (SPA)
Example: Gmail
You make a restless API using Mongo, Node.js, and Express. And you make a website with a single page using Angular that interacts with the API.  The app will feel faster and more responsive because you don't have to reload entire html documents.

3 shortcomings of the SPA architecture to keep in mind: **crawlability**, **analytics integration**, and **page load speed**.
1. User interface of application loads only once, and new content sent from the server don't make the page refresh or anything, so browser history and analytics package don't work. In other words, you can't really track user traffic. But there are workarounds. There are apparently open source libraries for Angular that make use of the HTML history API.
2. It makes your site hard to **crawl**. Search engines usually look at html content of a website to make recommendation. Some also look at JavaScript, but not really at the JavaScript at the backend server. 
3. SPA's have a slow start up. Initial speed is slow because the client needs to download code to run locally.

When a user first visits SPA, their browser needs to download both the framework code (Angular) and the initial application code.

**Lazy-loading** is loading only the necessary parts of the application when they are needed, rather than loading everything upfront.

## MVC pattern
Stands for model view control. It is model that simplifies/guides the process of developing web applications by breaking it into 3 parts. The Controller acts as an intermediary between Mode and View aspects of the application and the user. It decouples application components.
![[MVC summary.png]]
[Source](https://www.youtube.com/watch?v=DUg2SWWK18I&t=30s)

1. Controller - contains app logic. it defines what data is going to be sent to the template engine, which in turn uses views to create and returns the static file that is returned to the user
2. Model - data
3. View - display

The folder structure for an Express app under the MVC pattern looks like this
```
app_server
	controllers
	models
	routes
	views
bin
node_modules
public
app.js
package.json
```

## Hybrid


When your solution isn't a good fit for all the problems you're trying to solve, we go hybrid. Say you want to design a blog. You want your subscribers to be able to read your articles. So it needs to be fast on startup and crawlable, with the ability to collect user analytics. This isn't a good use for a SAP. So we follow the MVC pattern. This is more like a traditional webserver-client type of thing where we send static content to the readers. We can still use Angular to do things like search bars and... And we can still use MongoDB to save comments and user accounts info. So it's still a versatile use of the MEAN stack. 
We also want a user interface for our writers to edit and post their articles. Like an editor of some sorts online. This would be a good use of an SPA. 

A single REST API feeding separate user-facing applications, built using different parts of the MEAN stack to provide the most appropriate solution



Possible architectures
- A Node.js and Express application
- A Node.js and Express application with Angular additions for interactivity
- An Angular SPA
# Rapid 
## Server based application





# Miscellaneous Notes
You want to use end-to-end JavaScript. You can't design one facade of the app using MEAN and another using a different technology.



## Development stages
Before anything, study the client's requirements and figure out what architecture best suits the application. Design prototypes and wireframes of what the website will look like.
1. Build a static app - works with dummy data
2. Design data base
3. Design data API 
4. Connect database and application using API
5. Finish frontend or business logic of application:
	- add authentication systems 
	- data validation
	- methods for displaying error messages to users.
	- etc.




AJAX (Asynchronous JavaScript and XML) http requests to retrieve data (usually JSON) from a server without the need to reload a page


# Template Engines
## Handlebar
Handlebar is a template engine that works with Express. You can set a template engine when initializing an Express project. It allows you to create a template, so we can avoid having to rewrite for footers and headers, for example, for every webpage. 
You can eliminate using static content. Instead, you can create dynamic webpages that can be changed according to the logic of your application. Results could be different for each user. This is similar to jinga in flask.
CS465 uses handlebar 

A handlebar document is called a **view**
When we factor code, it is called a **partial**

## pug
This is another template engine that the book uses. Example uses:
```
#banner.page-header
  h1 My page
  p.lead Welcome to my page
```
compiles to:
```
<div id="banner" class="page-header">
  <h1>My page</h1>
  <p class="lead">Welcome to my page</p>
</div>
```

Notes:
- pug uses spaces for indentation, not tab
- if you don't specify HTML element, pug assumes you mean `<div>`
- 
# nodemon
Node.js applications need to be compiled before run.
Package wraps Node.js applications and restarts it whenever it detects changes. It's kinda like enabling debug mode in a flask application: you won't have manually restart the application every time.
To install globally,
```shell
npm install -g nodemon
```
To start, go to project dir and enter
```shell
demon
```

# Starting an Express Project
`cd` to a new directory
```shell
express --css=x --view=y --git
```
- `--css`: optional. defines which CSS preprocessor engine (less or stylus) to use for the project. Leave out if none.
- `--view`: mandatory. defines which HTML template engine (ejs, hbs, or pug) 
- `--git`: adds a `.gitignore` file for the project.

This will create the project dir and its layout, as well as package.json.

Then,
```shell
npm install
```
To start app,
```shell
npm start
```

## Project Dependencies
### package.json
In every node.js application, this fille specifies app metadata (like name, version, etc.) and dependencies.
### A note about dependency versions
It's not a good idea to use the latest version, signified by the `~` wildcard in front of the version number because breaking changes can create problems in the application. It's best to use minor versions (`^`) because these updates usually only contain bug fixes. If no wildcard, the app will use the exact version.
```shell
{
  "name": "travlr",
  "version": "0.0.0",
  "private": true,
  "scripts": {
    "start": "node ./bin/www"
  },
  "dependencies": {
    "cookie-parser": "~1.4.4",
    "debug": "~2.6.9",
    "express": "^4.19.2",
    "hbs": "^4.2.0",
    "http-errors": "~1.6.3",
    "morgan": "~1.9.1"
  }
}
```

### Install new packages
```shell
npm install package-name
```

> npm generates a **package-lock.json** file to maintain versions of dependencies between environments, which is helpful when you’re deploying from development to a live server.

## Express middleware
```
app.use(some code);
```
```
user request -> middleware1 -> middleware2 -> ... -> app logic -> response -> user browser
```

When the request comes in, it goes through a bunch of middleware functions. Each function does something with the request, like extracting cookie information, encoding the url, and more. The middleware will also match the requested url with a router. The router binds a url with a controller. The controller is the application logic to be executed when a url is being requested.

<center>
app.js
</center>
```js
const express = require('express');
...
const app = express();
...
const router = express.Router();
router.get(
			// This is the url
			'/',
			// This is the controller
			(reg, res) => {
			   res.render('index', {title: "Travl Getaways"});
			};
		);
...
app.use('/', indexRouter);
...
```

The controller function here is compiling an HTML file using the `res.render()` function. It sends a json to the `index.pug` file, found in `views` directory.

Since we don't want to closely couple the app components, we separate the router and controller into their own files.



# MongoDB

Mongoose is a library specifically designed for Node.js to interact with MongoDB. It handles creating databases, opening and closing connections, defining schemas and models (with data validation, and performing CRUD (Create, Read, Update, and Delete) operations on the data.

Start by importing the library
```js
const mongoose = require('mongoose');
```

Next, we define a schema
Example of a schema:
```js
const openingTimeSchema = new mongoose.Schema({
    days: {
      type: String,
      required: true
    },
    opening: String,
    closing: String,
    closed: {
      type: Boolean,
      required: true
    }
  });
```

You can have documents inside other documents. These are called subdocuments, and they have their own schemas:
```js
const locationSchema = new mongoose.Schema(
    {
        name: {
            type: String,
            required: true // input validation
        },
        address: String,
        rating: {
            type: Number,
            'default': 0, // it's good practice to wrap default in quotes because it is a js keyword
            min: 0,
            max: 5
        },
        facilities: [String], //array of strings
        // GeoJSON data. See below for example of acceptable input
        coords: {
            type: {
                type: String,
                enum: ['Point'],  // Must be 'Point'. Other types include: LineString, Polygon
                required: true    // This field must be present
            },
            coordinates: {
                type: [Number],   // Array of numbers
                required: true    // This field must be present
            }
        },
        openingTimes: {
            type: [openingTimeSchema],
            required: true
        },
        reviews: [reviewSchema]
    }
);
```

## Compiling the schema
A model is a compiled schema. After compilation, we can do CRUD.

```js
mongoose.model('Location', locationSchema, 'Locations');
```

- `mongoose` is connection name
-  `Location` is what we're naming the model
- `locationSchema` is the name of the schema
- `Locations` is the name of the collection in the database we want to push the data to


# Restful API
The specific methods and URIs depend on the data and the actions we want to perform
Use the same base URI for each collection in the database 
The same URI can be used for different http methods. 
Examples:


| Action              | Method | URL        | Example                          |
| ------------------- | ------ | ---------- | -------------------------------- |
| Create new location | POST   | /locations | http://example.com/api/locations |
| Read locations      | GET    | /locations | http://example.com/api/locations |
You can even delete a sub-document
`/locations/:locationid/reviews/:reviewid
`http://example.com/api/location/123/reviews/abc`

As with creating URLs for the pages in our website ([[Full Stack Web development using MEAN#Express middleware]]), we need routers and controllers for our API. But, we don't want to mix these with the other URLs (no decoupling), so we create a new folder in the root called `app_api`.


# GET

Mongoose model search methods
- `find`—General search based on a supplied query object
- `findById`—Looks for a specific ID
- `findOne`—Gets the first document to match the supplied query
- `geoNear`—Finds places geographically close to the provided latitude and longitude
- `geoSearch`—Adds query functionality to a geoNear operation



`.select()` allows us to specify what routes (a variable in a model is called a route) we want to retrieve. If we only want to perform operations on only certain routes, then there is no sense in retrieving entire documents.
```js
.findById(req.params.locationid)                         
    .select('-reviews -rating') // - means do not retrieve these routes
    .exec((err, location) => {
		// code
	}
```

# POST


# PUT (Update existing documents and subdocuments in the database)
The general structure for a PUT request is to first retrieve a document, make some edits, then save it to the database.
```js
/**
 * req parameter represents the http request body
 * res represents the response we send
 */
const locationsUpdateOne = (req, res) => {
// we find the document using locationid. if the request body doesn't have this value, then we cannot perform the operation and must throw an error
  if (!req.params.locationid) {
    return res
      .status(404)
      .json({
        "message": "Not found, locationid is required"
      });
  }
  // Loc is the mongoose model for our database
  Loc
    .findById(req.params.locationid)
    .select('-reviews -rating')
    .exec((err, location) => {
      if (!location) {
        return res
          .json(404)
          .status({
            "message": "locationid not found"
          });
      } else if (err) {
        return res
          .status(400)
          .json(err);
      }
      location.name = req.body.name;
      location.address = req.body.address;
      location.facilities = req.body.facilities.split(',');
      location.coords = {
        type: "Point",
        [
          parseFloat(req.body.lng),
          parseFloat(req.body.lat)
        ]
      };
      location.openingTimes = [{
        days: req.body.days1,
        opening: req.body.opening1,
        closing: req.body.closing1,
        closed: req.body.closed1,
      }, {
        days: req.body.days2,
        opening: req.body.opening2,
        closing: req.body.closing2,
        closed: req.body.closed2,
      }];
      location.save((err, loc) => {
        if (err) {
          res
            .status(404)
            .json(err);
        } else {
          res
            .status(200)
            .json(loc);
        }
      });
    }
  );
};
```

Updating a subdocument
```js
const reviewsUpdateOne = (req, res) => {
  //locatinid is id for document, and reviewid is id for its subdocument
  if (!req.params.locationid || !req.params.reviewid) {
    return res
      .status(404)
      .json({
        "message": "Not found, locationid and reviewid are both required"
      });
  }
  // first find the document
  Loc
    .findById(req.params.locationid)  
    .select('reviews')
    .exec((err, location) => {
    // in this context, location will be known as the document
    // error if location is not found
      if (!location) {
        return res
          .status(404)
          .json({
            "message": "Location not found"
           });
    // other errors
      } else if (err) {
        return res
          .status(400)
          .json(err);
      }
      // check if the document has the subdocument and it's not empty
      if (location.reviews && location.reviews.length > 0) {
      // retrieve the subdocument using the reviewid
        const thisReview = location.reviews.id(req.params.reviewid);  
        // make sure subdocument exists  
        if (!thisReview) {
          res
            .status(404)
            .json({
              "message": "Review not found"
            });
        } else {
        // update contents of subdocument
          thisReview.author = req.body.author;
          thisReview.rating = req.body.rating;
          thisReview.reviewText = req.body.reviewText;
          // make the changes to the location
          // location is just an object (json format) returned by .exec() 
          // location is in this context because we're still inside the Loc.findById(req.params.locationid).select('reviews').exec((err, location) => { ... function
          // save the changes
          // .save() funcion takes an an error argument and the document to save to
          location.save((err, location) => {
            if (err) {
              res
                .status(404)
                .json(err);
            } else {
            
              updateAverageRating(location._id);
              res
                .status(200)
                .json(thisReview);
            }
          });
        }
      } else {
        res
          .status(404)
          .json({
            "message": "No review to update"
          });
      }
    }
  );
};
```

# Delete
use the `.findByIdAndRemove()` method 

```js
const locationsDeleteOne = (req, res) =>  {
  const {locationid} = req.params;
  if (locationid) {
    Loc
      .findByIdAndRemove(locationid)
      .exec((err, location) =>  {
          if (err) {
            return res
              .status(404)
              .json(err);
          }
          res
            .status(204)
            .json(null);
        }
    );
  } else {
    res
      .status(404)
      .json({
        "message": "No Location"
      });
  }
};
```

```js
location.reviews.id(reviewid).remove();
```


# How to call an API in Express
```
$ npm install --save request
```

```
const request = require('request');
```
This module allows us to send requests (method and body) and handle response (parse body, interpret responses, etc.).

General use of request:
```js
request(options, callback);
```
`options` sets the info to make the API call, and callback function defines what to do with the response sent back.

Example:
```
options = {
	url: 'localhost:3000/api/path',
	method: 'GET', // not required, default is GET
	json: {}, // body of the request
	qs: {} // not required, query string parameters
}
request(options, (err, response, body) => {
	if (err) {
		console.log(err);
	}
	else if (response.statusCode == 200) {
		console.log(body);
	}
	else {
		console.log(response.statusCode);
	}
});
```


# Angular
## Startup
Install the Angular CLI. Run the following command to generate the skeleton of the application.
```
ng new your-app-name options
```
- `--skiGit`
- `--skipTests`
- `-defaults`
- `directory`

To start
```
ng serve
```
This makes the app run from memory. any changes made make the app to recompile. It is great for development.

For deployment, we use `ng build`. This compiles the app into the disk
```
ng build --prod --output-path build
```
`--prod` meaning this is a production build. You should also specify a path

creating a component
```
ng generate component home-list
```

## Strategy for transforming an express app to an SPA
First, recreate the main page of express app in angular as a static page by copying the html code over (if the html in the source code uses a template engine syntax, then render it on the browser and copy the html from inspecting the page). Similarly, copy over the stylesheets and other static files (like images). Then slowly transform the SPA to a smart app by replacing the hardcoded data 

## How to define and instantiate a class in typescript
```ts
class Location {
	_id: string;
	name: string;
	distance: number;
	address: string;
	rating: number;
	facilities: string[];
}

Location: location = {
	_id: 'a',
	name: 'Costy',
	...
	facilities: ['hot drinks', 'food', 'power']
};

//Instantiating an array of a custom class
locations: Location[] = [{},{}];
```
To use data in the .component.html file, use double curly braces:
```html
<p>{{location.address}}</p>
```

## Looping
Looping in .component.html using `*ngFor` directive from angular.
For example,
```html
<div class="facilities">
  <span *ngFor="let facility of location.facilities" class="badge-warning">{{facility}}</span>
</div>
```
expands to:
```html
<div class="facilities">
  <span class="badge-warning">hot drinks</span>
  <span class="badge-warning">food</span>
  <span class="badge-warning">power</span>
</div>
```

You can also perform simple operations like math and string concatenation within the curly braces,  ```
```html
<i class="fa{{ location.rating < 1 ? 'r' : 's' }} fa-star</i>
```

## TypeScript Functions
Defining functions in TypeScript
```ts
transform(value: any, args?: any): any {
    return null;
}
```
`any` is type
`args?` means the function can accept a variable number of arguments, including 0. And they could be of any type. 


## Pipes
Pipes are used in angular to format data. Angular has a few built in pipes, like:
```
{{ 'hi' | uppercase }}
// currency rounds the number to two decimal places
// true means show the unit of currency in the text
{{ 12.3485 | currency:'EUR':true }}
```

### Creating a custom pipe
First, use the cli to generate the necessary files. To clarify, it creates 2 files.
```
ng generate pipe distance
```
`distance` is the name of the pipe in this example

This code goes inside the 
```ts
import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'distance'
})
export class DistancePipe implements PipeTransform {
  transform(value: any, args?: any): any {
    return null;
  }
}
```


## Services
To request data from an API, we need to use a service. Services have many uses in Angular.
```
ng generate service service-name
```


Use Promises, not Observables
## CORS
Cross origin resource sharing
<center>
<iframe width="560" height="315" src="https://www.youtube.com/embed/4KHiSt0oLJ0?si=yPXfJs1kaHW08oat" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
</center>
Our SAP client is running on a different port (a different domain) than the API, which runs on an express application, hosted on port 3000. We need to configure the express application to allow resources to be shared with the SAP by adding the `Access-Control-Allow-Origin` header to the responses from the API
```js
app.use('/api', (req, res, next) => {
  res.header('Access-Control-Allow-Origin', 'http://localhost:4200');
  res.header('Access-Control-Allow-Headers', 'Origin, X-Requested-With, Content-Type, Accept');
  next();
});
```
