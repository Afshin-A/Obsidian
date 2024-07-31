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



development stages
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


# Handlebar
Handlebar is a template engine that works with Express. You can set a template engine when initializing an Express project. It allows you to create a template, so we can avoid having to rewrite for footers and headers, for example, for every webpage. 
You can eliminate using static content. Instead, you can create dynamic webpages that can be changed according to the logic of your application. Results could be different for each user. This is similar to jinga in flask.
CS465 uses handlebar 

## pug
This is another template engine that the book uses. 
# nodemon
Node.js applications need to be compiled before run.
Package wraps Node.js applications and restarts it whenever it detects changes. It's kinda like enabling debug mode in a flask application: you won't have manually restart the application everytime.