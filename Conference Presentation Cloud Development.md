 
Afshin E. Ahvazi
CS 470 (Full Stack Development 2)
October 26, 2024
Project 2: Conference Presentation--Cloud Development
Available at https://youtu.be/CG4JwYEpAro

# Narration Script
## Screen 2
Hello everyone, and welcome to this presentation for my Full Stack Development course (CS470). My name is Afshin. I am a student at SNHU. And in the following slides, we're going to discuss the process, benefits, and challenges of migrating and adapting a MEAN stack web application to the serverless architecture on the AWS (Amazon Web Services) cloud environment.

## 3
Migrating MEAN to Cloud
Let’s say that as a new developer, you have just joined a team that’s working on a complex project. Before you can start, you have to set up your environment, download software, install dependencies, and so on. A better and much faster way is to pre-package, or containerize, all the code, configurations, and dependencies into a Docker image. Then, all you just need to do is to install the docker engine on your environment and run the image. From the perspective of the running image, it is an isolated system: it has its own operating system, processes, file system, and so on. But of course, it’s drawing resources from the host machine. Overall, we make our code portable, scalable, and secure.

Containers make deploying applications onto the cloud very easy. In this case, we’re working with a MEAN stack application. Just to give a quick overview, MongoDB is the database, Express is the back-end server, and Angular is used for the front-end (For those curious, N stands for Node.js, which is the platform on which our Express server runs). We can containerize each component of the application and configure them to work together using Docker Compose, which we’ll get more in depth in the upcoming slides. From here, we have several options for cloud hosting:

- Infrastructure as a service (IaaS), where we rent a server from a cloud provider like AWS and configure and maintain it ourselves.
- ~~Containers as a service (CaaS), infrastructure that is already configured to support containers and orchestration.~~ ~~So~~~~,~~ ~~we simply upload container images instead of OS images, hence taking advantage of all the benefits of containerization.~~
- Platform as a Service (PaaS), where we’re given a platform for software development and hosting, and don’t have to worry about server management, but we still manage the environment and application runtime and scaling.
- Finally, we have serverless, the model used in this project and the focus of this presentation. ~~In a moment, we will get into more about this model~~

Necessary Tools for Containerization
Before we get to the serverless model, what are the tools we need for containerization?
- Container engine – it is the underlying kernel that manages image processes, containers, volumes, etc.
- Command line interface (CLI) – it allows us to communicate with the kernel using commands
- Alternatively, a desktop graphical user interface (GUI) is a high-level way of interacting with the kernel
- Orchestration tools – like Docker Swarm and Kubernetes, these are used for managing multiple containers in the production environments. They handle container networking, deployment, and scaling
- Container Registry – similar to version control for containers
- Code editor – we use visual studio code to edit and debug our application code.

Docker, the desktop app, is the most popular platform for containerization and provides all the necessary tools for this project.
## 4
Now that we’re familiar with containerization, let’s delve into orchestration.

We introduced Docker Compose in the previous slide. It is a tool within Docker that helps us define, run, and manage complex container-based systems.

As we discussed, one of the benefits of using containers is that they’re autonomous; that means that by default, they’re not aware of other containers or the host system. This makes them more secure. But, how do we make them work together in our MEAN stack application? For example, our Express server has a dependency on the MongoDB database. Of course, you and other software engineers can manually enter the appropriate commands into the terminal, in order, every time you want to start the application. But imagine if there were dozens or even hundreds of components. It would turn into a real nightmare real fast. To solve that, we use a YAML file to store and organizing all the instructions and commands to start up the application. It is basically an instruction sheet that tells Docker how to start the application. You can define dependencies, versions, you can create networks and assign them to containers. ~~Network ports, images and image version.~~ And This file can be shipped with the software and distributed to the users. So the value of Docker compose is that we can start a complex application with just one command.

## 5
Unlike the other cloud computing models we discussed, in the serverless model, the cloud provider abstracts low level details like managing hardware infrastructure, resource allocation, the platform, as well as the runtime environment. Instead, we are given access to turnkey services that we will be using in lieu of deploying our own components. In this model, we’re only responsible for configuring the service and writing the code to interact with it. The provider will manage runtime, handle back ups, and automatically scale the application. All of these factors make the serverless model excellent for dynamic applications, where scaling, availability, and cost optimization are critical.

For this project, we use Amazon Web Services (AWS). It is an ecosystem with a variety of cloud computing services with security and access management features and a pay-as-you-go payment plan, which, as we will see, is a very cost effective option for our application.

One of AWS services our project uses is Simple Storage Service, or S3, for storing application files: things like static angular files for the front-end component of our application, or log files. Maintaining our own data center is expensive and resource intensive: Consider the cost of the necessary hardware, power, and housing. We would also need to hire a team dedicated to physically maintaining the data center by replacing failed drives, for example, or responding to malicious attacks.

Using S3, on the other hand, we can safely store encrypted data and easily access it over a network connection anytime as needed. We no longer are concerned about maintaining or scaling the data center. It is also cheaper to use S3 because we only pay for the storage we use. Another unique feature of S3 is that it automatically creates backups throughout different facilities spread all around the world, so we no longer need to worry about losing important data. Lastly, S3 makes it possible to easily share your data. For example, security policies make it possible to define roles within an organization to read and write files.

## 6
Okay. So we’ve talked about hosting the front-end of our application on S3. Moving on, We use the two AWS services, API Gateway and Lambda, to power our server.

The main purpose of the API Gateway is to act as an interface that gives users controlled access to the back-end. It processes RESTful API requests, forwards them to the correct Lambda functions, and handles returning the result. It also acts as a security barrier between the outside world and our Lambdas, rejecting invalid requests or even malicious attacks. To summarize, the API Gateway is a secure entry point into our API. It offers features like request validation, routing, and load balancing to handle traffic efficiently.

Next, Lambdas are basically functions that implement the application logic. There are 3 things that we need to configure for a Lambda to work: the runtime environment, the code to run, and when to run it. Each Lambda exports a handler function that tells the API what code to execute. Also, Lambda functions are executed only when they’re triggered by an API call. This is referred to as event driven programming. They intake a request, process the headers and the body, and create and return a response back to the API. So, If Lambda knows the language runtime, when to start, and how to start, then we have a working back-end.

~~Connecting the front end to the back-end is easy. The client will need to establish a secure connection using the API key and send requests to the API URI~~

~~Notice again the benefits of the serverless architecture.~~

## 7
The general workflow goes for the serverless architecture goes like this:

1. User Interaction: First, a user interacts with the Angular front-end hosted on S3.
2. API Requests: When the user performs an action (e.g., creating a new record), Angular sends an HTTP request via API Gateway.
3. Lambda Execution: The API Gateway triggers the appropriate Lambda function based on the HTTP method (e.g., GET, POST, PUT, DELETE).
4. Database Interaction: Then, Lambda functions communicate with the database to store or retrieve data. (We will talk about DynamoDB in the upcoming slide)
5. Response: Finally, the Lambda function returns the appropriate response to the API Gateway, which then forwards it to the frontend to be displayed on the user’s screen.

## 8
The final component of our application is the database. Traditionally the MEAN stack uses MongoDB. However, as we’re adapting the serverless model, it becomes very easy to pair the AWS DynamoDB with other AWS services that we’re already using.

MongoDB is a popular choice because of its flexibility. It is a cross-platform database that can be deployed anywhere, even on cloud services. It is schema-less and doesn’t impose much restrictions on how we design the database. This means that overtime, our data model can evolve with the application. Also, MongoDB has built-in checks that can reject incorrect data. Another area that Mongo shines is querying data. It supports multi-key indexing, allowing us to query based on multiple fields and sort the results in a certain order using the aggregate pipeline. MongoDB, while scalable, requires careful planning upfront to account for horizontal scaling of servers and efficient indexing of the database. So, it’s flexible but needs preparations and maintenance.

DynamoDB, on the other hand, has more limited querying capabilities since it uses a primary key (and sometimes a secondary key) for item look-up. Compared to Mongo, it only supports a handful of data types and relies more on the application to interpret the data and verify its integrity. However, Dynamo is highly available and durable. Just like with S3, it automatically takes care of maintenance, backups, and scaling. It offers the same level of protection as AWS S3 since it automatically replicates data across different availability zones. It’s ideal for applications with unpredictable workloads because it doesn’t impose any limits on storage.

# 9
There is a lot of competition in this line of business. And people are impatient. A small delay is all it takes to lose a customer forever. And with the holiday season coming up, we want to be prepared while at the same time efficient with our resources. As we’ve seen so far, the serverless model is elastic, meaning that resources will automatically scale up or down in response to how much we use AWS services. For example, Lambda and DynamoDB automatically handle workload fluctuations. If our application suddenly sees an increase in traffic, AWS will handle it by dynamically assigning more resources to match the demand.

This synergizes well with the pay-as-you-go model because we only pay for the actual resources the application uses. There are no upfront or idle fees. For example, when we use the Lambda service, we pay for the duration the code runs. It’s measured in milliseconds. Same thing goes for API Gateway. We’re only billed based on the number of API calls made. 

## 10
The last thing I’d like to talk about is security.

Suppose we are working at a large company with hundreds of employees. Within any organization, there is a hierarchy of roles: you have the employees, managers, the CEO, etc.. For each role, we would want to specify the access privileges. Identity and Access Management (or IAM in short) is an amazon service that allows us to define roles and policies that dictate what AWS resources those roles can access. We obviously don't want to give everyone access to crucial data and configurations. For security purposes, we want to give each user the minimum access they need to perform their work, something that’s known as the least privilege principle. IAM roles aren't restricted to human users. They can also be assigned to other AWS resources. For example, you can allow a server to access data from certain S3 buckets.
