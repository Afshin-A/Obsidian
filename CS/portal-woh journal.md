https://blog.logrocket.com/express-typescript-node/


```
npm init
```
Unlike Python projects, you don't need to create a virtual environment for Node.js projects. npm installs packages locally by default, unless we use the `-g` option.

```
npm init -y
```
quick start a project with default values 

```
npm install -D typescript
```
we can optionally install node packages used only for development, not deployment

```
npx tsc --init 
```
is a command line utility used to run some node packages we install using `npm`

We're developing the back-end API with TypeScript to take advantage of type safety, easier debugging, better VS Code features, etc..
There are complementary packages that provide type information for Node and Express, since these are written in JavaScript and do not have types.
```
@types/node
@types/express
```

Node.js doesn't work with TS; it works with JS. So, during development, we use a tool named `ts-node` to automate the process of converting TS to JS. `ts-node` compiles the TS code in memory, which is then directly executed by Node.js. It does this every time we run our application, which is a key part of its convenience during the development phase. It handles this compilation **just-in-time** (JIT).
The difference between this JIT process and a traditional compiler is that a traditional compiler, like `tsc`, compiles the code once and saves it to a `.js` file on disk. This pre-compiled `.js` file can be used for every subsequent program run, making it ideal for a production environment where startup speed and performance are critical.
`ts-node` compiles only the relevant parts of the typescript code that are actually needed for the program to run, saves them in memory, and loads them into node.js. Hence it's good for constantly re-running in a testing environment, but not so much in production where we run the entire application just once.

As I found later, and we'll cover this shortly, if we want to use the ESM module system, we can't directly run `ts-node` because it causes errors. 


JS/TS has different module systems, i.e. different ways of organizing modules and global variables. We need to configure these in the `package.json` and `tsconfig.json` the first time we run our application. 
- CommonJS - this is an older system but it is still used primarily in Node.js applications. It uses the `require()` function for importing modules and they export like `module.exports = { module1, module2, ....}`
- ECMAScript Modules (ES Modules/ESM) - officially introduced in Javascript 2015, also known as ES6 and ECMAScript 2015, and it is considered the standard.

ECMAScript is the name of the standard that JS implements. It's the blueprint for the JS language.


What does it mean to target ES modules?
When compiling TS to JS, we tell the compiler to what module system to use in the output code.


# Compiler settings for using ES module system in production 
### The Problem:
When we're developing with TS using `ts-node`, there are no compiled JS files for each TS file, that's why importing from a JS file will throw a module not found error because such file does not exist on disk.

### The Solution:
We have the following in our `tsconfig.json` file 
```json
"compilerOptions": {
    "target": "ES2020", // emit modern JS features
    "module": "Node16", // tell TS to behave like Node’s ESM world
    "moduleResolution": "Node16", // use Node’s ESM resolver rules
    ...
}
```

The solution was using an ESM (**E**CMA**S**cript **M**odules) loader:
```shell
nodemon --watch 'src/**/*.ts' --exec node --loader ts-node/esm ./src/server.ts
```
An ESM loader is a Node.js mechanism that allows us to customize the module loading process. In this case, the `ts-node/esm` loader compiles.

We're not running `ts-node` directly here. We're running the `node` binary and passing `ts-node/esm`, which is a loader that comes with the `ts-node` package  


# Scopes in `npm`
You might notice a package name like `@types/express` or `@angular/common`. `@types` or `@angular` are called <u>scope names</u>. A big company might want to publish multiple packages under their name. Scope names are basically the name of the organization, and a way to organize packages and avoid confusion when different packages by different people have the same name.\



# IaC (Infrastructure as code)

A tool that allows us to programmatically manage the cloud services--the Infrastructure--of our projects. Amazon, for example, has their own service named CloudFormation. Another popular tool that is used for all platforms, including Google Cloud and Microsoft Azure, is **Terraform**. 
 
# ORM - Object Relational Mapper
used for mapping objects in a programming language to data in a database. it also provides the tools to abstract database operations. 

## Prisma 
Prisma is an ORM for JS/TS
It also includes a tool to migrate from development 

We're pairing this with a local installment of PostgreSQL and pgAdmin4, which is a user interface for managing PostgreSQL databases.

Migration is like Git for our database. As development progresses, the data also changes.
We make changes to the data schema in the `schema.prisma` file and run the following command that generates SQL instructions for updating the database
```bash
npx prisma generate
```
We then apply the changes using the `prisma migrate` command
```
npx prisma migrate dev --name init
```

```
npx prisma studio
```

Formats the files and can apply corrections, especially for 
```
npx prisma format
```

### Prisma relationships
```ts
model DocumentAssignment {
  id         String      @id @default(uuid())
  ...
  // one-to-one
  // each DocumentAssignment has one document template. Or they may not have one. ? means optional
  documentTemplate DocumentTemplate?
}

model DocumentTemplate {
  id          String     @id @default(uuid())
  name        String
  ...
  documentAssignmentId String @unique
  documentAssignment DocumentAssignment @relation(fields: [documentAssignmentId], references: [id])
}
```
The child defines the relationship. In pure English, it translates to connect `DocumentTemplate.documentAssignmentId` (foreign key) to `DocumentAssignment.id` (Primary key)
The `@unique` constraint on `documentAssignmentId` means that this is a 1-to-1 relationship. No two `DocumentTemplate` rows can have the same `documentAssignmentId`.


# CI/CD

## GitHub Actions

**Event** triggers (e.g. pull request, pushed commit, etc.) start a workflow. A **workflow** is a set of jobs. It gets its own designated virtual machine that can run jobs, either in sequence or in parallel.
**Jobs** are either scripts or actions.
Each Job is consisted of a series of steps that run sequentially. Think of them like a pipe that can pass data from one step to the next.
Jobs can depend on each other, i.e. take each other as a dependency.

CI - Continuous Integration 
It means frequently committing code in order to detect bugs and errors early.  
The next step is Continuous Deployment, which is deploying the code onto the cloud platform.

Each workflow is defined in a YAML file, put in the `.github/workflows` directory

# OpenID Connect (OIDC) / OAuth 
OpenID connect is a protocol that uses the OAuth framework. (they're the same shit)
Login through google -> user enters their password -> google sends a token to the site -> site generates JWT and sends it to user


# Pull Request, Push, and Merge Request
When you push your code onto the online repository, you're merging your local repository and online repository together. 
If you push your code to someone else's repository, you are actually sending a request to the owner to pull your changes onto their repository. That's why it's called a pull request.
Another name for a pull request is a merge request. 
# How CI/CD Works
A CI/CD pipeline is just a series of tasks that run every time we push code.
For this project (and in general) we have 1 pipeline that covers 3 branches: development, staging, and production. There are jobs waiting to be run depending on which branch is updated. For each branch, we have a live environment, for different reasons.
Each environment has its own database

In Continuous Integration (CI), we make sure everything integrates:
- Run unit tests
- Run integration tests (Express + Postgres)
- Lint / static analysis (catch bad code patterns)
- Build Angular frontend
- Package backend code (zip for Lambda, or Docker image for ECS)

In Continuous Deployment (CD), we make sure everything deploys:
- Run **database migrations** (Prisma → Postgres)
- Deploy backend (Lambda or ECS)
- Deploy frontend (upload Angular build to S3, refresh CloudFront cache)
- Smoke test (simple automated checks that app is responding)

# What is database migration? 
We're using Prisma for database migration. When the database schema inevitably changes during development, the schema for staging and production databases also need to evolve. We run a script that updates the database. This is called **database migration**. 

## Prepping for migration using Prisma
We need to configure Prisma in the `prisma/schema.prisma` file:
```js
generator client {
  provider = "prisma-client-js"
  output   = "../src/generated/prisma"
}

datasource db {
  provider = "postgresql"
  url      = env("DATABASE_URL")
}

model User {
  id        Int      @id @default(autoincrement())
  username  String   @unique
  password  String
  createdAt DateTime @default(now())
}
```

URI for local postgres db has the following format:
```
postgresql://username:password@localhost/dev
```
Use the username and password set up when you installed postgres on your machine.

Create a migration:
```bash
npx prisma migrate dev --name init
```

This will create a migration file under the `prisma/migrations/` directory, which contains the step by step directions on how to recreate the database schema later when we migrate from dev to staging and production environments
It will also create and update a table named `_prisma_migrations_` in the database, which is responsible for keeping track of these migrations
It will apply the changes to the schema to the database

To apply the migration in `staging`/`production`, we use the following command:
```
npx prisma migrate deploy
```
This could be used in our CI/CD pipeline when we push code in between the environments

# Why do we need Staging?
What's the point of the staging area if we already have dev and prod environments/branches? 

Often times small teams can just skip staging. This is supposed to be a stable branch of all the merges by different developers. It uses a stable real database that is close to the one used in production. In contrast, the `dev` branch would use a docker image with dummy, unimportant data. 
We do integration tests on completed features that have made it from the `dev` branch to `staging` here, before pushing it to production. 
The dev branch is often messy and keeps getting pushed to by different developers. It is not stable, and therefore can't be showcased to stakeholders or share holders. Just imagine a service goes out mid presentation because a developer's push has bugs uncaught by the CI/CD pipeline.


# Versioning
`Vmajor.minor.patch`
A patch or hotfix is a quick update applied to the live application in `production`. Sometimes we can't wait until the next big update is pushed to fix an issue like a security flaw or a bug that needs immediate attention. 
`Major` updates, as the name suggests, is when we do major overhaul of the application, like redesigning API endpoints. That could make the client SPA 
`Minor` updates include new, backward compatible features


# Frontend

How to use Angular CLI to create a service at a specific location:
```bash
npx ng generate service core/auth
```
This will create a service file `auth.service.ts` in the directory `src/app/core`.

## Routes In angular
The phrase "**activated route**" means the route that has been navigated to.
Routes in angular are represented by a tree. At the top we have the base `/`. Similarly, `/documents` and `/users` would be the children of the parent path `/` 
`RouterStateSnapshot` class is used to represent the entire tree.
Each tree nodes is is an instance of the `ActivatedRouteSnapshot`class. It contains the current state of the activated route, including its parameters and query parameters. The router creates this after a successful navigation.

Angular internally uses `UrlTree` type objects to represent paths. This a is parsed, immutable object that. Think of it as augmented version of a simple string path like `/documents/pending`
```ts
if authService.isLoggedIn() {
	return true;
}
else {
	return this.router.createUrlTree(['/login'], { queryParams: { returnUrl: this.router.url } });
}
```

# How to handle JWT
- User enters username and password to login
- We hash password and check it against our db. If they match, user logs in. Make sure we use salt and a long algorithm like bycrypt 
- ~~We retrieve user role, create JWT, and put it in a cookie. We send the cookie back.
- We retrieve user role, create JWT, and send it back to the client in the HTTP response. The client saves it in a variable in memory (not in `localStorage`).
- We also create a long-lasting refresh token, store it in db (or in server cache), and send it back to the client. 
- Later, the user sends a request. The cookie is automatically sent along. We validate cookie the JWT server side and only if it's valid, we process the request
- ~~We also send in a CSRF token to make sure the request came in from the application, not a third party site, preventing CSRF attacks
- We're not storing JWT in a cookie, so we're safe from CSRF attacks.
- To access some routes, the user needs admin privileges. We use a guard, which is a service that checks if the user role is admin. The router calls this service when the user tries to access a role protected by that guard. This is client side. We also need to perform server side checks.
- We need to refresh the JWT every 10 minutes. The server needs a `/auth/refresh` endpoint
- When a refresh token is revoked or expired, store it in the database. If we ever receive a request with a previously used refresh token, consider it an attack and immediately revoke all of the user's tokens

~~The problem with CSRF tokens is that we would have them embedded in every page. That's not really an issue with Angular because we can just put the token in the root component. But the problem is that we would have to start managing CSRF tokens, their expiry and renewals. We need both valid CSRF and JWT tokens for a successful request. ~~


How do we validate JWT? Does the server need to store it?
No. JWT is cryptographically signed. The server independently calculates the signature and matches it with what was received
Do we asynchronously keep track of when the JWT expires? No. When JWT expires the user can no longer make requests. When they logout, we send a request to the backend to temporarily blacklist both their refresh token and their JWT. We remove the tokens from the user's browser.  from their browser and temporarily add it to an auth guard service checks if there is a JWT 


# JWT Reserved claims
Each JWT token may have these seven reserved tokens. They're not required and can be omitted, but they are recommended to include.
- `iss` (issuer): Issuer of the JWT
- `sub` (subject): Subject of the JWT (the user) - *Who the token is* **about**
- `aud` (audience): Recipient for which the JWT is intended - *Who the token is* **for**
- `exp` (expiration time): Time (in seconds) after which the JWT expires
- `nbf` (not before time): Time before which the JWT must not be accepted for processing
- `iat` (issued at time): Time at which the JWT was issued; can be used to determine age of the JWT
- `jti` (JWT ID): Unique identifier; can be used to prevent the JWT from being replayed (allows a token to be used only once)
[source](https://auth0.com/docs/secure/tokens/json-web-tokens/json-web-token-claims)

# Some security headers to consider using
`Strict-Transport-Security` means the server only responds to https requests
`X-Frame-Options: DENY` disables the website from loading in iframes in order to prevent clickjacking attacks
`X-Content-Type-Options: nosniff`-- not entirely sure what this does, but, apparently, it tells browsers not to "sniff" files (browsers  go through the files to determine their type?). This prevents a form of XSS attacks where an attacker might break into the server and send in script hidden in an image or document.

# Cookies
A website can have as many cookies as allowed by the browser (typically hundreds). 
A cookie is a file
A cookie has a domain attribute, so the browser sends them to every call to that domain
Cookies can also have a path attribute so that they're only send to a specific path of a domain


# Angular: Traditional vs. Standalone
## Traditional
Traditionally, Angular components must be defined in the scope of a module. Modules group together related components, services, pipes etc.. The module has a `declarations` array (as *metadata*) that lists these components, which are compiled together as a unit. For instance, routing has its own module. 
You have a main module that imports other modules, creating a module hierarchy. Modules define dependencies and exports. 
This method is fine, but it creates a lot of boilerplate code. When you import a module, you import everything in it, even if you need just a single component. You end up with ng modules everywhere. 
```ts
// features/options/options.module.ts
import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ColorPickerComponent } from './color-picker/color-picker.component';
@NgModule({
  declarations: [ColorPickerComponent], // Declared in the module
  imports: [CommonModule],
  exports: [ColorPickerComponent], // Exported to be used elsewhere
})
export class OptionsModule {}

// features/options/color-picker/color-picker.component.ts
import { Component } from '@angular/core';
@Component({
  selector: 'app-color-picker',
  templateUrl: './color-picker.component.html',
  styleUrls: ['./color-picker.component.css'],
})
export class ColorPickerComponent {}
```


## Pure Standalone
New Angular versions introduce standalone components that define their own imports and exports. You don't need to import an entire module. You can just import the component you need. This is supposedly the recommended way: it's more efficient and reduces application size and performance. 
Routes are now defined in a file, `app.routes.ts` 

As such, *standalone components don't have a `declarations` array*. They list all their dependencies, including other components, directives, pipes, etc., in an *imports* array:
```ts
import { CommonModule } from '@angular/common';
import { Component, OnInit } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { DynamicFontSizeDirective } from '../../dynamic-font-size' // This is a custom directive
@Component({
  selector: 'app-login',
  standalone: true,
  imports: [CommonModule, FormsModule, DynamicFontSizeDirective],
  templateUrl: './login.html',
  styleUrls: ['./login.css'],
})
export class Login implements OnInit {
  ...
}
```

## Hybrid 
For this project, we use modules as a way to group related angular elements together.
We create standalone components and add them to the `exports` array of the module. An external component can then import this module and use the components. However, Angular will only import the components that are being used, not the entirety of the module.
```ts
// features/options/color-picker/color-picker.component.ts
import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-color-picker',
  standalone: true,
  imports: [CommonModule], // Manages its own imports
  templateUrl: './color-picker.component.html',
  styleUrls: ['./color-picker.component.css'],
})
export class ColorPickerComponent { ... }

// features/options/font-size-change/font-size-change.component.ts
@Component({
  selector: 'app-font-size-change',
  standalone: true,
  ...
})
export class FontSizeChangeComponent { ... }

// options.module.ts
import { NgModule } from '@angular/core';
import { ColorPickerComponent } from './color-picker/color-picker.component';

@NgModule({
  // components don't need to be declared in the module, they're standalone
  imports: [ColorPickerComponent, FontSizeChangeComponent], // Imported here so it can be exported
  exports: [ColorPickerComponent, FontSizeChangeComponent] // Exported to be used elsewhere
})
export class OptionsModule {}
```

We can import the `OptionsModule` above in another standalone component. This allows us to use all components `OptionsModule` exports. However, behind the scenes, Angular will only import the components actually used from the module. For example, in the code below, only the `ColorPickerComponent` is being imported.
```ts
// app.component.ts

import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterOutlet } from '@angular/router';
import { OptionsModule } from './features/options/options.module'; // Import the hybrid module

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [CommonModule, RouterOutlet, OptionsModule], // The module is imported here
  template: `
    <h1>Hello, I am the app component!</h1>
    <app-color-picker></app-color-picker> <router-outlet></router-outlet>
  `,
  styleUrls: ['./app.component.css'],
})
export class AppComponent {}
```

Examples of commands used in this project to create these modules and components:
```sh
ng generate module features/options

ng generate component features/options/color-picker --standalone
```



# Why are Angular HTTP requests returned as Observables?

Despite observables subscription and cold stream mental model (where observers subscribe to an observable and keep receiving updates), observables have other features that Angular uses them wrap around async values, like the results of HTTP requests. 
An observable can technically just emit one value, like an HTTP response. 
Observables give fine-tuned control over HTTP requests. You can manipulate the results via a pipe using operators, you can combine multiple streams (?), and you can cancel the requests, even.

# Angular is not a node.js app
Even though angular uses npm for managing its packages, it's not a node.js application, therefore we can't directly use packages like server-side packages like `dotenv`. This requires node.js to run, but angular is not a node.js app.

Instead we use components to store environmental variables used for each stage of development (dev, staging, production)

`jwt-decode` for example, is a client-side package that can run on a browser. 

# What is a TypeScript Preprocessor? 
`ts-jest`
A typescript compiler is necessary 

Since jest doesn't understand test files written in typescript, a *transformer* like `ts-jest` is necessary. `ts-jest` detects and intercepts typescript files fed to jest; it transforms them to javascript in memory and feeds them to jest. This is called *on-the-fly*, also known as *just-in-time*: the fact that files are compiled as they're needed.
We don't need to compile the whole program into .js files and then run the tests. No, that's too slow. Running tests should be fast.

In contract, *precompiling* is compiling the entire project into javascript before running.

A great analogy is cooking:
- **Precompiling** -- meal-prepping. You cook everything in advance, then just reheat/eat.
- **On-the-fly compilation** -- cooking as you go, every time you’re hungry.
Both give you food, but precompiling makes eating faster, while on-the-fly makes experimenting faster.


# TypeScript Notes
### Object Destructing
In JS/TS, you can do what's called object destructing. You can save a specific value from a dictionary into a variable.
```
const { name } = req.body;
```
This extracts `req.body.name` into the variable `name`. 
You can use a different variable name or define a default value incase there is no such value in the dict.
```
const { name: userName = 'afshin` }
```

So tired of having to manually add semicolons to every line. VS Code apparently doesn't have a shortcut, so I found an extension named "Colonize".
### Type assertion with `as` keyword
You can force the typescript compiler to treat a variable type as a specific type:
```ts
const req = {} as Request;
```

###  `null` vs `undefined`
When we declare a variable but don't assign a value, Java/Type Script automatically assigns `undefined` to it.
It means the value is missing and is not yet defined.

`null` means nothing. There is no ambiguity. It means a developer explicitly set the value to be nothing. This can be used to remove values from a variable.

`null == undefined` returns *true* while `null === undefined` (deep comparison) returns *false*


### `Number` vs `number`
In TypeScript, these are two different types.
`number` is a primitive type used for integers and floats.
`Number` (notice it's capitalized) is a wrapper that wraps primitives and provides operations like `Number.isInteger()` or `Number.parseFloat()`.

### `??`
If the left hand var is null or undefined, you can return a default value using the `??` operator as follows:
```ts
let actualCount = count ?? 0;
```

### `?`
It means a value is optional and may be `undefined` or `null`

```ts
if (pdfData.info?.Form?.Fields) {
    return pdfData.info.Form.Fields;
}
    
```
###  `!!` 
This is called the *double bang*, and it's used to explicitly convert values into a Boolean form.
For instance, 
```js
const myString: string | null = "hello";
const isStringPresent: boolean = !!myString //true
```

### Globbing for File Paths
This is usually used in config files to denote *recursive* searching in a path. For example,
```
"src/**/*.ts"
```
matches all `.ts` files inside the `src` directory, and all sub-directories of `src`, and their subdirectories, and so on. 

`.gitignore` also uses it to search for files/directories to ignore

### `!`
When used at the end of a variable, it assures Typescript that the variable is not null



### Other notes
`path` is a node module
```ts
import {join} from path;
join
```
Paths are denoted differently depending on the OS and platform. The `join` method works independently of platform.
It also resolves relative segments like the user of `./` for current dir and `../` for the parent dir.
**Do not manually concatenate strings.** Use `join`

`__dirname` global node variable. A string that stores the dir name of the current module

This is a named import
```ts
import { readFileSync } from 'fs';
```
This is a default import 
```ts
import { join } from 'path';
```
You can do both types of imports from a module that has both
```ts
import path, { join } from 'path';
```
You can give imports an alias:
```ts
import { v4 as uuidv4 } from 'uuid';
```

`.map()`
This method can be called on an array. It takes in a lambda function and  

`JSON.parse()` This method converts a string into an object
`JSON.stringfy()` This is the opposite of the `parse` method. It converts a JSON object into a string

`as`
This is one way we can do typescript does type assertion during compile time. Normally, the compiler would infer the type of an object, however we can also force the compiler to treat a variable as a certain type. 
```ts
return manifestData as Manifest
```
In this example, `manifestData` is an object that was created without a type. We want TypeScript to treat it as a `Manifest` object.


# Using nonce to prevent replay attacks
An attacker manages to intercept a message, saves it, and resends it at a later time. They don't need to decrypt or alter the message.
For example, suppose a user has an IoT, smart lock for their house. Attackers can save the encrypted message and send it at a later time to unlock the door.
In a similar way, we need to prevent replay attacks for submitted documents. We don't want duplicated or potentially altered documents to be passed as legitimate. 

The receiving server needs to be able to recognize duplicate requests, or when a request is received outside of the permitted window. 

Replay attacks 

# Designing system for Signing documents
So we first send the manifest and a static, read-only version of the PDF template to the user. We use the manifest (which includes positional metadata like x, y, width, height, page, font size for each field) and the static template to create a view for the user: the client renders the PDF as a background using something like pdf.js, then overlays interactive HTML input fields aligned exactly on top based on the manifest. This lets the user read the full document context while filling in data, and if needed, we can capture a hand-drawn signature via a canvas element in the form (sent as base64 in the JSON). The validations from the manifest (like data types, required fields, ranges) are applied client-side for better UX, but they're just advisory since the real enforcement happens server-side.

Then, the client sends the user entries (including any signature image) as JSON back to the server. The server validates the data again using its own copy of the manifest, plus extra checks like HMAC or nonce to prevent tampering. Then, if everything is right, it creates a PDF preview by loading its secure, original template and filling in the data (and embedding the visual signature if applicable). The server sends the document preview (as a non-editable PDF view or temporary URL) and its hash back to the client. We also send the hash of the metadata combined with the PDF—metadata is stuff like `{userId: "123", timestamp: "2025-09-22T10:00:00Z", docType: "contract", version: "1.0", nonce: "unique-session-id"}`. We include this to bind the signature to specific context, preventing things like replay attacks where someone reuses a valid signature on a different doc or at the wrong time; it ensures the hash covers not just the content but who, when, and what is being signed.

The client then calculates the hash of the preview (plus the metadata, which the server also sends) and matches it with what was sent to verify against man-in-the-middle attacks or transit corruption—if it doesn't match, we reject and alert.

The user then reviews the exact preview (scrolling through all pages if it's long), confirms everything is right (with an option to go back to edit mode if needed, which loops to re-submit data and get a new preview). They click a finalize button. The client then signs the combined hash (of the preview document + metadata) with their private key—using the in-house key system where the client generates and stores the key pair securely (e.g., via Web Crypto API and IndexedDB), and we've already sent just the public key to the server during onboarding. It sends the signature (as base64) back.

The server verifies the signature with the user's public key by recomputing the hash from its draft PDF + metadata and checking if it matches what was signed—if valid, it embeds the signature into the PDF for cryptographic integrity, makes it immutable, stores the final version with audit logs, and handles key rotation periodically (e.g., every 6-12 months, keeping old publics for historical verification).

# Non-repudiation
It is a product of integrity and authentication.

# Base64 encoding
## Why it's done
Base64 includes `^[A-Za-z0-9+/]*=?=?$`
Basically has characters A-Za-z0-8+/
It may end with 1 equals sign or 2, depending on the divisibility of the bits of the string by 6. 

The base64 range of characters is `A-Z, a-z, 0-9, +, /`, and `=`. When when binary data is converted to ASCII, the result can be a wide variety of characters outside of this scope. Applications like text editors and pdf viewers and such may misinterpret these characters as commands or just not understand them. Therefore, so keep data compatible across different applications and platforms, data is converted to a safe range of characters.
## How it's done
<iframe width="560" height="315" src="https://www.youtube.com/embed/aUdKd0IFl34?si=qmziqXgjKNEVyt6J" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>


# Where do `req` and `res` come from? 
The typical Express controller function has a header like this:
```ts
import type { Request, Response, NextFunction } from 'express';

export async function functionName(req: Request, res: Response, next: NextFunction) 
```

Node.js handles http communication to the server and creates objects that represent requests and responses.
Express wraps these objects and provides methods like `.status()` and `.json()`

# Errors
`Cannot set headers after they are sent`
This happened because I accidentally wrote:
```ts
res.json(401).json({error:'No token'});
```
It should instead be 
```ts
res.status(401).json({error:'No token'});
```
Otherwise the server will attempt to send two responses,  401 and {error: No token}. Express complains what it can't set the headers for the second request 

- 200 - OK!
- 400 - bad request - wrong syntax
- 401 - invalid credentials
- 403 - forbidden - no sufficient access privilege
- 404 - could not find requested resource
- 500 - server error


# Configuring Jest to work with ESM
Although I've configured the `jest.config.ts` to be compatible with ESM, it keeps throwing syntax errors inside the `setup.ts` file where we define global variables. The solution was to install the *cross-env* package and run jest from inside `package.json` like this:
```json
    "test": "cross-env NODE_OPTIONS=--experimental-vm-modules jest",
```
ESM support for Jest is apparently highly experimental. Being on Windows has something to add to the issue because we had to use cross-env, which is a package for setting environmental variables compatible with different operating systems,

# AWS System Manager (SSM) Parameter store VS AWS Secret Manager
A service for storing less sensitive parameters, although it does have versioning and encryption.

It's ideal for storing less sensitive data, like application configurations that need to be shared across different components of a system (e.g. sharing aws region between Terraform and Node/Express application). 

## AWS Secret Manager 
Secret Manager is great for sensitive data like passwords and secret keys. It has advanced security features like auto rotation, but it's also more expensive.


# Paths in node
`__filename` is not defined in the ES module system
`import.meta`, it is a built-in object that is automatically available inside every ECMAScript module, giving us access to a module's specific metadata.
`import.meta.url` gives us access to the absolute URL (`file://`) of the current file. We can convert this URL to a system path format as follows:
```ts
import path from "node:path"
import { fileURLToPath } from 'node:url';
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);
const infraOutputsPath = path.join(__dirname, '../infra-outputs.json');
const infraOutputs = JSON.parse(readFileSync(infraOutputsPath, 'utf-8'));

```

In node, relative paths are with respect to where the application is being run. If you call `npm run dev` while current directory is `root`, then `../` would refer to the parent of `root`

# Windows PowerShell version 5 outputs UTF16 encoding
```shell
terraform output -json > ../src/infra-outputs.json
```
This command was outputting a UTF16 encoded file, which could not be parsed with the `JSON.parse()` function. Files need to be UTF-8 encoded. There are ways around this, like piping the output through a , or setting the parameter values inside the `$PSPROFILE` file, but first of all, they don't work (the profile editing method outputs UTF8 BOM), and secondly, we need our application to be platform independent. While we're developing it in Windows, we need it to be Linux compatible since Github CI/CD and AWS resources need Linux.
So I installed PowerShell version 7, which is more cross-platform compatible. 

# Determining font size
$$
\begin{align} \\
S_{\text{min}}= \lceil{\text{box\_width}\over N_{\text{max}}}\rceil\\ \\

S_{\text{default}}=12  \ \text{pt} \\ \\

\min \Big(S_{\text{default}}, \max \big( S_{\text{min}}, \  \frac{\text{box\_width}}{\text{current\_width\_at\_default\_size}}  \big) \Big)
\end{align}

$$

# Organizing the Angular Project



# Monorepo Architecture
This project uses a mono repo architecture: one github repository houses multiple independent projects.
Other architectures are monlith, where there is only one repository and the independent projects are modules in the project.
Multi repo is when each project gets its own separate repository
https://medium.com/@magenta2127/monorepo-vs-multi-repo-vs-monolith-7c4a5f476009

```ts
{
  "compilerOptions": {
    "baseUrl": ".",
    "paths": {
      "@utils/*": ["utils/*"]
    }
  }
}
```

- **Relative imports (`./thing` or `../thing`)** → unchanged, still resolved relative to the file.
- **Non-relative imports (`foo/bar`)** → first checked against `paths`. If no match, then looked up starting from `baseUrl`.
- **Node modules (`@angular/core`, `rxjs`)** → unchanged, resolved from `node_modules`.

https://medium.com/@magenta2127/monorepo-vs-multi-repo-vs-monolith-7c4a5f476009
# Solving the problem of ugly component imports
```
src/
	app/
		core/
		features/
			documents/
				form-field-component/
					
				form-overlay-component/
		shared/
			directives/
			pipes/
			UI/
```
If you want to import a directive in the `form-field-component` from the shared dir, you would normally have to use relative imports like this:
```ts
import { directive } from '../../../shared/directives/directive'  
```
This is ugly, tedious, and can very easily turn into a mess.
So instead, we can give an alias to the shared dir in the compiler options like this:
```
{
  "compilerOptions": {
    "baseUrl": "src",
    "paths": {
      "@shared/*": ["app/shared/*"],
      "@features/*": ["app/features/*"],
      "@utils/*": ["../utils/*"]
    }
  }
}

```

# If a file is already being tracked by Git, adding it to `.gitignore` does not ignore it
You have to remove it from the Git index first:
```bash
git rm --cache path/to/file
```


# WORM model in AWS S3
Worm, *Write once, read many* , is a feature in S3 that allows creating immutable, tamper proof storage for sensitive files
must enable versioning to use object lock
you can apply different settings to different versions. For instance, 

Bucket versions are created when we upload a file with the same name multiple times
When you delete a version of an object, S3 creates a *delete marker* for that specific object version. It won't actually delete the object to protect it from accidental deletes. However, that object version will not appear in searches or be returned by requests until it is restored. It can also be permanently removed.

Retention modes are 
- **Governance mode**: users with enough permissions can bypass the retention and remove the object and bucket
- **Compliance mode**: no one can remove the object until the retention period wears off. 
Legal hold is an endless retention, until it is turned off
<iframe width="560" height="315" src="https://www.youtube.com/embed/XQVm0ebdz3E?si=68QBIwMKxHSWmzxA" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>


# AWS CloudTrail
It's used for *security auditing* by tracking how AWS users (including the root user), IAM roles, services, etc.. interact with AWS. Every time someone creates, updates, or deletes something, it gets recorded. 

CloudTrail logs can optionally be saved to S3 or CloudWatch, especially if they need to be saved longer than 90 days

CloudTrail is automatically enabled. 

A service that generates logs for other AWS services, like API calls in Lambda, and pushes them into S3. It can be configured to encrypt the logs.


# AWS CloudWatch
AWS CloudWatch is used for monitoring things like network traffic, utilization of computing resources, and for measuring system performance in general. 
It allows us to collect, organize, and query logs from AWS (such as AWS components) as well as non-AWS sources (such as logs from within the application e.g. Pino)
We can set up alarms/notifications for various custom events—when CPU utilization hits 90% for example.

**Metrics** are graphs that represent resource usage against time. 
They are stored under a *namespace*. By default, they claim the names of the AWS services that generated the logs, but we can also create custom name spaces
Metrics are region specific. The metric of the same service that's hosted on different regions will appear separately. 


**Basic** vs **Detailed monitoring**
This defines how often the metric data is updated. How often data is sent to the CloudWatch console.
- *Basic* is every 5 minutes, it's widely available, and is free
- *Detailed* is every 1 minute, it is only available for some services, and it incurs additional charges. 
For example, maybe we don't want to wait 5 minutes to get an update on the CPU utilization when testing software running on an EC2 instance

**Metric resolution** is the period for data collection.
How fast should data be collected? It basically defines the units of measurement on the time-axis in the metric graph.
- *Standard resolution* is 1 minute,
- *High resolution* is every 1 second

<iframe width="560" height="315" src="https://www.youtube.com/embed/Yxl7e88cTAQ?si=kSWZM80iJpIlXEFs" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
# CloudTrail Vs CloudWatch

CloudWatch is for monitoring resource uses while CloudTrail is for auditing AWS account activities


<iframe width="560" height="315" src="https://www.youtube.com/embed/W1zGjrH3BJI?si=QTq748LjJ5PJpCMO" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
# Is Lazy Loading Efficient?
Yes. Not only it reduces initial application load time, but it's also faster on the backend: less processing time, less resource intensive.  It's also easier on the database, as loading everything together will likely require multiple joins and chain operations.

In terms of cloud costs and efficiency, is it better to make two small fetch requests, or one big request that brings everything all at once?
It's true that we would have to make 2 requests, but the cost of each request is fractions of a cent and is negligible. And EC2 (that we're using to run PostgreSQL) instance will cost more

So we need two requests
First request is going to fetch all pending assignments for the user
Next, we will use the assignment id to fetch a specific document template and manifest. We should decouple these two in case we need each one separately for something else in the future



# Notes on Typescript errors that occurred and how I resolved them when I converted utils into its own organization (work in progress)
Every architecture has its advantages and disadvantages. For my project,  Monorepo Architecture was the best option because I can have all my packages in one code base, where its easy easy to share resources e.g. one package depends on another, and they're scalable. 
Refer to [this post on Medium](https://medium.com/@magenta2127/monorepo-vs-multi-repo-vs-monolith-7c4a5f476009) for more about the Monorepo Architecture. 


We need a way to connect all our packages together 
Node provides a way to do this
You can specify the child package directories inside `package.json` as follows:
```json
{
	... 
	"version": "1.0.0",
	"private": true,
	"workspaces": [
		"frontend",
		"backend",
		"utils",
	]
}
```
A big project that is consisted of individual projects. 

Each package gets its own `package.json` file and defines things like
```json
{
  "type": "module", <-- enables ESM, which enables import
  "name": "@woh/backend",
  "version": "1.0.0",
  "description": "",
  "author": "Afshin-A",
  "main": "server.ts",
  "scripts": {
	"build": "tsc",
    "start": "node dist/server.js",
    ...
  },
  },
  "dependencies: {
	@my-project/utils: "^1.0.0",
	...
  }
  
```
When we run `npm install` at the root, node will install all dependencies at the root. We can avoid repeats 

![[Pasted image 20251009154759.png]]
That little arrow on the right means these are symbolic links (pointers to the actual packages in the file system)

The first problem you could run into is attempting to import code from outside of  `rootDir` which we define in the compiler options 
"File is not under 'rootDir' 'src'. 'rootDir' is expected to contain all source files."

You must import files with the .js extension in ESM module resolution 

In my next post, I'm going to talk about how we can overcome some of the disadvantages of the mono repo architecture using a build system like Nx

# How importing a node module is resolved
```json
{
  "name": "@woh/utils",
  ...
  "exports": {
    "./URLs": {
      "import": "./dist/URLs/index.js",
      "require": "./dist/URLs/index.js",
      "types": "./dist/URLs/index.d.ts"
    },
```

When an external package imports `@woh/utils/URLs`, the compiler will look for the module in `node_packages` and load the file that's defined in the `exports` for that module. In this case, it's `./dist/URLs/index.js`, which exports all the functions and variables in that function.


# Justification for using AWS SQS as middle layer between the application layer and the S3 storage layer (handling audit logs)
We could ship the audit logs directly form our backend to S3 every N minutes using an asynchronous process.
But while that is simple to implement, it is not an industry standard pattern because it is slow and not scalable.  
We have to implement complex logic in our backend to temporarily store the logs in memory, as well as retry logic if S3 save requests fails. For example, we'd have to add the unsuccessful logs on top the newly generated logs, wait until it's time to try again, and send a bigger blob. If the request keeps failing, that log blob would get bigger and bigger.

So instead we're shifting into a fire and forget mentality. Separation of concerns. Our server should be focused on serving the customers, not get clogged up by failed audit logs. But these audit logs are still a very important part of the system for non-repudiation purposes. So, we need to use a scalable, highly available, middleman queue to store the audit logs blobs. BTW by blob I mean collection of individual log items (instances of a log data type). 

Logs get added to the queue, a lambda worker pops a log blob, and adds them to an append-only S3 bucket. 

When the worker pops the log blob, it doesn't get removed from the queue. SQS just puts it on the side so that other processes can't access it. So it's thread safe. A timer starts. The process that popped the item must signal SQS that the operation (in this case, saving to S3) was successful before the timer runs out, or else SQS will put that item back into the queue. So AWS greatly simplifies the retry logic for us. 

Advantages of this model:
- different rates for shipping logs and processing them. the backend might be too busy and ship logs to the queue every 10 minutes. 
- fire and forget. backend no longer has to worry about processing S3 storage
- eventual guaranteed processing. the lambda will eventually get to processing (saving them into S3) all the logs
- Application decoupling. 
	- The services don't know about each other. 
	- If one service goes down, it doesn't affect the other services. 
	- The less dependent different services are, the better the architecture is.
	- Debugging is easier. If all the services were entangled with each other, good luck tracking down bugs and debugging code in dozens of different parts of the application. 
Define a backend service to capture the logs. If there's a problem in capturing the logs, we go there to debug. Define a service in the backend to ship the log blobs. Again, if there is a problem in that process, i.e. logs aren't being sent to the queue, we go to this service to debug. Define an external lambda to process the logs from the queue. **Separation of concerns. Decoupling.**

SQS is the only weakpoint of this design, because if it goes down, data will be lost and the services can't do their job. But the good new is that SQS is highly scalable and reliable, so it almost never goes down.

https://youtu.be/CyYZ3adwboc
https://youtu.be/fluDEkA1h6w
https://youtu.be/I2mWnh66Bkg
canonical logging pino



# `Record`
It's a utility that incredibly useful for dictionary-like objects or maps where you want to enforce a specific structure for both the property names and the values.
```ts
Record<keyType, valuesType>
```
`keys` is typically a union of strings.
```ts
type UserRole = 'admin' | 'editor' | 'guest';
type RoleStatus = Record<UserRole, boolean>;
const status: RoleStatus {
	admin: true,
	editor: false,
	guest: true
}
```
An object of type `RoleStatus` must have all the keys


# Using Zod to ensure a reliable single source of truth in our audit trails
We need to make sure no log entry is ever saved with a missing required field, an improperly formatted ID, or an incorrect data type.

Zod performs runtime type check. Suppose we have a complex type with hundreds of fields. We don't want to have to sit and manually check every single field conforms to our expectations (i.e. not null, matches a pattern, etc.)
Enter Zod.


#  IAM
User
Group
Role
Policy
<iframe width="560" height="315" src="https://www.youtube.com/embed/hAk-7ImN6iM?si=n_Ca9sIOgf_4Cm4H&amp;start=1092" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>



Use a DLQ for poison messages.
SQS Consumer lambda

- Producer only: `sqs:SendMessage` (and maybe `sqs:GetQueueAttributes` if needed).
- Consumer (Lambda): `sqs:ReceiveMessage`, `sqs:DeleteMessage`, `sqs:GetQueueAttributes`, `sqs:ChangeMessageVisibility`, s3:putobject




# AWS Fargate
Serverless service that runs docker containers
