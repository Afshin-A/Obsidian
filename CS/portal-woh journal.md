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

Node.js doesn't work with TS; it works with JS. Normally, we'd have to first convert the TS files to JS then start the node application. So, **during development**, we use a tool named `ts-node` to automate this process. It compiles the TS code into memory, which is then directly piped into Node.js. It does this every time we want to test a change, which is convenient (but slow) during development. It does it *just in time* (JIT).
The difference is that a traditional compiler will compile the code once and store it in memory, so every subsequent program run will be faster. This is great for production. 

As I found later, and we'll cover this shortly, if we want to use the ESM module system, we can't directly run `ts-node` because it causes errors. 


JS/TS has different module systems, i.e. different ways of organizing modules and global variables. We need to configure these in the `package.json` and `tsconfig.json` the first time we run our application. 
- CommonJS - this is an older system but it is still used primarily in Node.js applications. It uses the `require()` function for importing modules and they export like `module.exports = { module1, module2, ....}`
- ECMAScript Modules (ES Modules/ESM) - officially introduced in Javascript 2015, also known as ES6 and ECMAScript 2015, and it is considered the standard.

ECMAScript is the name of the standard that JS implements. It's the blueprint for the JS language.


What does it mean to target ES modules?
When compiling TS to JS, we tell the compiler to what module system to use in the output code.


## Compiler settings for using ES module system in production 
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

The solution was using an ESM loader:
```shell
nodemon --watch 'src/**/*.ts' --exec node --loader ts-node/esm ./src/server.ts
```
An ESM loader is a Node.js mechanism that allows us to customize the module loading process. In this case, the `ts-node/esm` loader compiles.

We're not running `ts-node` directly here. We're running the `node` binary and passing `ts-node/esm`, which is a loader that comes with the `ts-node` package  
## Object Destructing
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


# Scopes in `npm`
You might notice a package name like `@types/express` or `@angular/common`. `@types` or `@angular` are called <u>scope names</u>. A big company might want to publish multiple packages under their name. Scope names are basically the name of the organization, and a way to organize packages and avoid confusion when different packages by different people have the same name.\

# Type assertion with `as` keyword
You can force the typescript compiler to treat a variable type as a specific type:
```ts
const req = {} as Request;
```




# IaC (Infrastructure as code)

A tool that allows us to programmatically manage the cloud services--the Infrastructure--of our projects. Amazon, for example, has their own service named CloudFormation. Another popular tool that is used for all platforms, including Google Cloud and Microsoft Azure, is **Terraform**. 
 
# ORM - Object Relational Mapper
used for mapping objects in a programming language to data in a database. it also provides the tools to abstract database operations. 

## Prisma 
Prisma is an ORM for JS/TS
It also includes a tool to migrate from development 



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

## What is database migration? 
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

